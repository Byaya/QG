#include "GameApp.h"
#include "d3dUtil.h"
#include "DXTrace.h"
using namespace DirectX;
using namespace std::experimental;

GameApp::GameApp(HINSTANCE hInstance)
	: D3DApp(hInstance)
{
}

GameApp::~GameApp()
{
}

//初始化
bool GameApp::Init()
{
	if (!D3DApp::Init())
		return false;

	// 务必先初始化所有渲染状态，以供下面的特效使用
	RenderStates::InitAll(m_pd3dDevice);

	if (!m_BasicEffect.InitAll(m_pd3dDevice))
		return false;

	if (!m_SkyEffect.InitAll(m_pd3dDevice))
		return false;

	if (!InitResource())
		return false;

	// 初始化鼠标，键盘不需要
	m_pMouse->SetWindow(m_hMainWnd);
	m_pMouse->SetMode(DirectX::Mouse::MODE_RELATIVE);

	return true;
}

void GameApp::OnResize()
{
	assert(m_pd2dFactory);
	assert(m_pdwriteFactory);
	// 释放D2D的相关资源
	m_pColorBrush.Reset();
	m_pd2dRenderTarget.Reset();

	D3DApp::OnResize();

	// 为D2D创建DXGI表面渲染目标
	ComPtr<IDXGISurface> surface;
	HR(m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface), reinterpret_cast<void**>(surface.GetAddressOf())));
	D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
		D2D1_RENDER_TARGET_TYPE_DEFAULT,
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED));
	HRESULT hr = m_pd2dFactory->CreateDxgiSurfaceRenderTarget(surface.Get(), &props, m_pd2dRenderTarget.GetAddressOf());
	surface.Reset();

	if (hr == E_NOINTERFACE)
	{
		OutputDebugString(L"\n警告：Direct2D与Direct3D互操作性功能受限，你将无法看到文本信息。现提供下述可选方法：\n"
			"1. 对于Win7系统，需要更新至Win7 SP1，并安装KB2670838补丁以支持Direct2D显示。\n"
			"2. 自行完成Direct3D 10.1与Direct2D的交互。详情参阅："
			"https://docs.microsoft.com/zh-cn/windows/desktop/Direct2D/direct2d-and-direct3d-interoperation-overview""\n"
			"3. 使用别的字体库，比如FreeType。\n\n");
	}
	else if (hr == S_OK)
	{
		// 创建固定颜色刷和文本格式
		HR(m_pd2dRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::White),
			m_pColorBrush.GetAddressOf()));
		HR(m_pdwriteFactory->CreateTextFormat(L"宋体", nullptr, DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 15, L"zh-cn",
			m_pTextFormat.GetAddressOf()));
	}
	else
	{
		// 报告异常问题
		assert(m_pd2dRenderTarget);
	}

	// 摄像机变更显示
	if (m_pCamera != nullptr)
	{
		m_pCamera->SetFrustum(XM_PI / 3, AspectRatio(), 1.0f, 1000.0f);
		m_pCamera->SetViewPort(0.0f, 0.0f, (float)m_ClientWidth, (float)m_ClientHeight);
		m_BasicEffect.SetProjMatrix(m_pCamera->GetProjXM());
	}
}


static std::wstring hitText = L"当前拾取物体：";
static int hitNum = 0;
static bool isKeep = false;
void GameApp::UpdateScene(float dt)
{

	// 更新鼠标事件，获取相对偏移量
	Mouse::State mouseState = m_pMouse->GetState();
	Mouse::State lastMouseState = m_MouseTracker.GetLastState();
	m_MouseTracker.Update(mouseState);

	Keyboard::State keyState = m_pKeyboard->GetState();
	m_KeyboardTracker.Update(keyState);

	auto cam1st = std::dynamic_pointer_cast<FirstPersonCamera>(m_pCamera);

	// ********************
	// 自由摄像机的操作
	//

	// 方向移动
	if (keyState.IsKeyDown(Keyboard::W))
		cam1st->Walk(dt * 5.0f);
	if (keyState.IsKeyDown(Keyboard::S))
		cam1st->Walk(dt * -5.0f);
	if (keyState.IsKeyDown(Keyboard::A))
		cam1st->Strafe(dt * -5.0f);
	if (keyState.IsKeyDown(Keyboard::D))
		cam1st->Strafe(dt * 5.0f);

	// 将位置限制在[-8.9f, 8.9f]的区域内
	// 不允许穿地
	XMFLOAT3 adjustedPos;
	XMStoreFloat3(&adjustedPos, XMVectorClamp(cam1st->GetPositionXM(), XMVectorSet(-8.9f, -1.0f, -8.9f, 0.0f), XMVectorReplicate(8.9f)));
	cam1st->SetPosition(adjustedPos);

	// 视野旋转，防止开始的差值过大导致的突然旋转
	cam1st->Pitch(mouseState.y * dt * 1.25f);
	cam1st->RotateY(mouseState.x * dt * 1.25f);

	// 更新观察矩阵
	m_pCamera->UpdateViewMatrix();
	m_BasicEffect.SetViewMatrix(m_pCamera->GetViewXM());
	m_BasicEffect.SetEyePos(m_pCamera->GetPositionXM());

	// 重置滚轮值
	m_pMouse->ResetScrollWheelValue();

	// 选择天空盒
	if (m_KeyboardTracker.IsKeyPressed(Keyboard::D1))
	{
		m_SkyBoxMode = SkyBoxMode::Daylight;
		m_BasicEffect.SetTextureCube(m_pDaylight->GetTextureCube());
	}
	if (m_KeyboardTracker.IsKeyPressed(Keyboard::D2))
	{
		m_SkyBoxMode = SkyBoxMode::Sunset;
		m_BasicEffect.SetTextureCube(m_pSunset->GetTextureCube());
	}
	if (m_KeyboardTracker.IsKeyPressed(Keyboard::D3))
	{
		m_SkyBoxMode = SkyBoxMode::Desert;
		m_BasicEffect.SetTextureCube(m_pDesert->GetTextureCube());
	}

	//拾取检测
	m_boundingSphere.Center = XMFLOAT3(m_Sphere.GetPosition());
	
	Ray ray = Ray::ScreenToRay(*m_pCamera, (float)(GameApp::m_ClientWidth / 2), (float)(GameApp::m_ClientHeight / 2));
	
	
	if (!ray.Hit(m_boundingSphere))
	{
		hitText = L"当前拾取物体：";
	}
	
	for (int i = 0; i < m_Cylinder.size(); i++)
	{
		if (m_boundingSphere.Contains(m_Cylinder[i].GetBoundingOrientedBox()))
		{
			m_Sphere.isView = false;
			m_Cylinder[i].isView = false;
			m_Sphere.SetWorldMatrix(XMMatrixTranslation(100.0f, 100.0f, 100.0f));
			m_Cylinder[i].SetWorldMatrix(XMMatrixTranslation(100.0f, 100.0f, 100.0f));
		}
	}

	if (isKeep&&m_Sphere.isView)
	{
		hitNum = 2;
		m_Sphere.SetWorldMatrix(XMMatrixTranslation(adjustedPos.x, adjustedPos.y, adjustedPos.z) * 
			XMMatrixTranslationFromVector(m_pCamera->GetLookXM()*2.0f));
	}
	if (hitNum==0 && ray.Hit(m_boundingSphere) && 
		m_MouseTracker.leftButton == Mouse::ButtonStateTracker::PRESSED)
	{
		hitNum = 1;
		isKeep = true;
		hitText += L"球体";
	}
	if (isKeep&&hitNum == 2 && m_MouseTracker.leftButton == Mouse::ButtonStateTracker::PRESSED)
	{
		isKeep = false;
		hitNum = 3;
	}
	if (hitNum == 3 && m_Sphere.isView)
	{
		/*m_Sphere.SetWorldMatrix(XMMatrixTranslation(
			m_Sphere.GetPosition().x,
			m_Sphere.GetPosition().y - dt * 0.98f,
			m_Sphere.GetPosition().z + dt * 10.0f));*/
		m_Sphere.SetWorldMatrix(
			
			XMMatrixTranslation(m_Sphere.GetPosition().x, m_Sphere.GetPosition().y, m_Sphere.GetPosition().z) *
			XMMatrixTranslationFromVector(XMVector3Normalize(m_pCamera->GetLookXM())*5.0f*dt)
			*XMMatrixTranslationFromVector(g_XMNegIdentityR1*dt *2.0f)
		);
		if (m_Sphere.GetPosition().y <= -2.48)
		{
			hitNum = 0;
		}
	}

	// 退出程序，这里应向窗口发送销毁信息
	if (m_KeyboardTracker.IsKeyPressed(Keyboard::Escape))
		SendMessage(MainWnd(), WM_DESTROY, 0, 0);
}

void GameApp::DrawScene()
{
	assert(m_pd3dImmediateContext);
	assert(m_pSwapChain);

	// ******************
	// 绘制Direct3D部分
	//
	m_pd3dImmediateContext->ClearRenderTargetView(m_pRenderTargetView.Get(), reinterpret_cast<const float*>(&Colors::Black));
	m_pd3dImmediateContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// 绘制模型
	m_BasicEffect.SetRenderDefault(m_pd3dImmediateContext, BasicEffect::RenderObject);
	m_BasicEffect.SetReflectionEnabled(false);
	m_BasicEffect.SetTextureUsed(true);
	if (m_Sphere.isView)
	{
		m_Sphere.Draw(m_pd3dImmediateContext, m_BasicEffect);
	}


	// 绘制五个圆柱
	// 需要固定位置
	m_BasicEffect.SetReflectionEnabled(false);
	m_BasicEffect.SetTextureUsed(true);
	m_BasicEffect.SetRenderDefault(m_pd3dImmediateContext, BasicEffect::RenderObject);
	for (int i = 0; i < m_Cylinder.size(); i++)
	{
		if (m_Cylinder[i].isView)
		{
			m_Cylinder[i].Draw(m_pd3dImmediateContext, m_BasicEffect);
		}
	}

	//绘制地面
	m_BasicEffect.SetRenderDefault(m_pd3dImmediateContext, BasicEffect::RenderObject);
	m_Ground.Draw(m_pd3dImmediateContext, m_BasicEffect);


	// 绘制天空盒
	m_SkyEffect.SetRenderDefault(m_pd3dImmediateContext);
	switch (m_SkyBoxMode)
	{
	case SkyBoxMode::Daylight: m_pDaylight->Draw(m_pd3dImmediateContext, m_SkyEffect, *m_pCamera); break;
	case SkyBoxMode::Sunset: m_pSunset->Draw(m_pd3dImmediateContext, m_SkyEffect, *m_pCamera); break;
	case SkyBoxMode::Desert: m_pDesert->Draw(m_pd3dImmediateContext, m_SkyEffect, *m_pCamera); break;
	}
	


	// ******************
	// 绘制Direct2D部分
	//
	if (m_pd2dRenderTarget != nullptr)
	{
		m_pd2dRenderTarget->BeginDraw();
		std::wstring text = L"当前摄像机模式: 第一人称视角  Esc退出\n"
			"鼠标移动控制视野 W/S/A/D移动\n"
			"切换天空盒: 1-白天 2-日落 3-沙漠\n"
			"当前天空盒: ";

		std::wstring center = L"十";

		switch (m_SkyBoxMode)
		{
		case SkyBoxMode::Daylight: text += L"白天"; break;
		case SkyBoxMode::Sunset: text += L"日落"; break;
		case SkyBoxMode::Desert: text += L"沙漠"; break;
		}


		m_pd2dRenderTarget->DrawTextW(text.c_str(), (UINT32)text.length(), m_pTextFormat.Get(),
			D2D1_RECT_F{ 0.0f, 0.0f, 600.0f, 200.0f }, m_pColorBrush.Get());
		m_pd2dRenderTarget->DrawTextW(center.c_str(), (UINT32)center.length(), m_pTextFormat.Get(),
			D2D1_RECT_F{ (float)(GameApp::m_ClientWidth/2), (float)(GameApp::m_ClientHeight / 2), 500.0,500.0f  }, m_pColorBrush.Get());
		m_pd2dRenderTarget->DrawTextW(hitText.c_str(), (UINT32)hitText.length(), m_pTextFormat.Get(),
			D2D1_RECT_F{ 0.0f, 100.0f, 800.0f, 600.0f }, m_pColorBrush.Get());
		HR(m_pd2dRenderTarget->EndDraw());
	}

	HR(m_pSwapChain->Present(0, 0));
}



bool GameApp::InitResource()
{
	// ******************
	// 初始化天空盒相关

	//白天
	m_pDaylight = std::make_unique<SkyRender>(
		m_pd3dDevice, m_pd3dImmediateContext, 
		L"Texture\\daylight.jpg", 
		5000.0f);

	//日落
	m_pSunset = std::make_unique<SkyRender>(
		m_pd3dDevice, m_pd3dImmediateContext,
		std::vector<std::wstring>{
		L"Texture\\sunset_posX.bmp", L"Texture\\sunset_negX.bmp",
		L"Texture\\sunset_posY.bmp", L"Texture\\sunset_negY.bmp", 
		L"Texture\\sunset_posZ.bmp", L"Texture\\sunset_negZ.bmp", },
		5000.0f);

	//沙漠
	m_pDesert = std::make_unique<SkyRender>(
		m_pd3dDevice, m_pd3dImmediateContext,
		L"Texture\\desertcube1024.dds",
		5000.0f);

	//默认为白天
	m_SkyBoxMode = SkyBoxMode::Daylight;
	m_BasicEffect.SetTextureCube(m_pDaylight->GetTextureCube());
	// ******************
	// 初始化游戏对象
	//
	
	Model model;
	// 球体
	model.SetMesh(m_pd3dDevice, Geometry::CreateSphere(0.5f, 30, 30));
	model.modelParts[0].material.Ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	model.modelParts[0].material.Diffuse = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	model.modelParts[0].material.Specular = XMFLOAT4(0.8f, 0.8f, 0.8f, 16.0f);
	model.modelParts[0].material.Reflect = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	HR(CreateDDSTextureFromFile(m_pd3dDevice.Get(), 
		L"Texture\\stone.dds", 
		nullptr, 
		model.modelParts[0].texDiffuse.GetAddressOf()));
	m_Sphere.SetModel(std::move(model));
	m_Sphere.SetWorldMatrix(XMMatrixTranslation(0.0f, -2.49f, 0.0f));

	//设置球的包围盒
	m_boundingSphere.Center = XMFLOAT3(m_Sphere.GetPosition());
	m_boundingSphere.Radius = 0.5f;

	// 地面
	model.SetMesh(m_pd3dDevice, 
		Geometry::CreatePlane(XMFLOAT3(0.0f, -3.0f, 0.0f), XMFLOAT2(20.0f, 20.0f), XMFLOAT2(5.0f, 5.0f)));
	model.modelParts[0].material.Ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	model.modelParts[0].material.Diffuse = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	model.modelParts[0].material.Specular = XMFLOAT4(0.2f, 0.2f, 0.2f, 16.0f); 
	model.modelParts[0].material.Reflect = XMFLOAT4();
	HR(CreateDDSTextureFromFile(m_pd3dDevice.Get(),
		L"Texture\\floor.dds",
		nullptr,
		model.modelParts[0].texDiffuse.GetAddressOf()));
	m_Ground.SetModel(std::move(model));

	// 柱体(6个柱体)
	m_Cylinder.resize(6);
	model.SetMesh(m_pd3dDevice,
		Geometry::CreateCylinder(0.5f, 5.0f));
	model.modelParts[0].material.Ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	model.modelParts[0].material.Diffuse = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	model.modelParts[0].material.Specular = XMFLOAT4(0.2f, 0.2f, 0.2f, 16.0f);
	model.modelParts[0].material.Reflect = XMFLOAT4();
	HR(CreateDDSTextureFromFile(m_pd3dDevice.Get(),
		L"Texture\\bricks.dds",
		nullptr,
		model.modelParts[0].texDiffuse.GetAddressOf()));
	static std::vector<XMMATRIX> cyliderWorlds = {
		XMMatrixTranslation(5.0f, -1.99f, 0.0f),
		XMMatrixTranslation(5.0f, -1.99f, -5.0f),
		XMMatrixTranslation(5.0f, -1.99f, 5.0f),
		XMMatrixTranslation(-5.0f, -1.99f, 0.0f),
		XMMatrixTranslation(-5.0f, -1.99f, 5.0f),
		XMMatrixTranslation(-5.0f, -1.99f, -5.0f)
	};
	for (int i = 0; i < m_Cylinder.size(); i++)
	{
		model.SetMesh(m_pd3dDevice,
			Geometry::CreateCylinder(0.5f, 5.0f));
		model.modelParts[0].material.Ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
		model.modelParts[0].material.Diffuse = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
		model.modelParts[0].material.Specular = XMFLOAT4(0.2f, 0.2f, 0.2f, 16.0f);
		model.modelParts[0].material.Reflect = XMFLOAT4();
		HR(CreateDDSTextureFromFile(m_pd3dDevice.Get(),
			L"Texture\\bricks.dds",
			nullptr,
			model.modelParts[0].texDiffuse.GetAddressOf()));
		m_Cylinder[i].SetModel(std::move(model));
		m_Cylinder[i].SetWorldMatrix(cyliderWorlds[i]);
	}

	// ******************
	// 初始化摄像机
	//
	m_CameraMode = CameraMode::Free;
	auto camera = std::shared_ptr<FirstPersonCamera>(new FirstPersonCamera);
	m_pCamera = camera;
	camera->SetViewPort(0.0f, 0.0f, (float)m_ClientWidth, (float)m_ClientHeight);
	camera->SetFrustum(XM_PI / 3, AspectRatio(), 1.0f, 1000.0f);
	camera->LookTo(
		//XMVectorSet(0.0f, 0.0f, -10.0f, 1.0f),
		XMVectorSet(0.0f, -3.0f, -10.0f, 1.0f),
		XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f),
		XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
	// 初始化并更新观察矩阵、投影矩阵(摄像机将被固定)
	camera->UpdateViewMatrix();
	m_BasicEffect.SetViewMatrix(camera->GetViewXM());
	m_BasicEffect.SetProjMatrix(camera->GetProjXM());


	// ******************
	// 初始化不会变化的值
	//

	// 方向光
	DirectionalLight dirLight[4];
	dirLight[0].Ambient = XMFLOAT4(0.15f, 0.15f, 0.15f, 1.0f);		//环境
	dirLight[0].Diffuse = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);			//传播
	dirLight[0].Specular = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);		//镜像
	dirLight[0].Direction = XMFLOAT3(-0.577f, -0.577f, 0.577f);		//方向
	dirLight[1] = dirLight[0];
	dirLight[1].Direction = XMFLOAT3(0.577f, -0.577f, 0.577f);
	dirLight[2] = dirLight[0];
	dirLight[2].Direction = XMFLOAT3(0.577f, -0.577f, -0.577f);
	dirLight[3] = dirLight[0];
	dirLight[3].Direction = XMFLOAT3(-0.577f, -0.577f, -0.577f);
	for (int i = 0; i < 4; ++i)
		m_BasicEffect.SetDirLight(i, dirLight[i]);

	return true;
}

