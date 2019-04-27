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

//��ʼ��
bool GameApp::Init()
{
	if (!D3DApp::Init())
		return false;

	// ����ȳ�ʼ��������Ⱦ״̬���Թ��������Чʹ��
	RenderStates::InitAll(m_pd3dDevice);

	if (!m_BasicEffect.InitAll(m_pd3dDevice))
		return false;

	if (!m_SkyEffect.InitAll(m_pd3dDevice))
		return false;

	if (!InitResource())
		return false;

	// ��ʼ����꣬���̲���Ҫ
	m_pMouse->SetWindow(m_hMainWnd);
	m_pMouse->SetMode(DirectX::Mouse::MODE_RELATIVE);

	return true;
}

void GameApp::OnResize()
{
	assert(m_pd2dFactory);
	assert(m_pdwriteFactory);
	// �ͷ�D2D�������Դ
	m_pColorBrush.Reset();
	m_pd2dRenderTarget.Reset();

	D3DApp::OnResize();

	// ΪD2D����DXGI������ȾĿ��
	ComPtr<IDXGISurface> surface;
	HR(m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface), reinterpret_cast<void**>(surface.GetAddressOf())));
	D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
		D2D1_RENDER_TARGET_TYPE_DEFAULT,
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED));
	HRESULT hr = m_pd2dFactory->CreateDxgiSurfaceRenderTarget(surface.Get(), &props, m_pd2dRenderTarget.GetAddressOf());
	surface.Reset();

	if (hr == E_NOINTERFACE)
	{
		OutputDebugString(L"\n���棺Direct2D��Direct3D�������Թ������ޣ��㽫�޷������ı���Ϣ�����ṩ������ѡ������\n"
			"1. ����Win7ϵͳ����Ҫ������Win7 SP1������װKB2670838������֧��Direct2D��ʾ��\n"
			"2. �������Direct3D 10.1��Direct2D�Ľ�����������ģ�"
			"https://docs.microsoft.com/zh-cn/windows/desktop/Direct2D/direct2d-and-direct3d-interoperation-overview""\n"
			"3. ʹ�ñ������⣬����FreeType��\n\n");
	}
	else if (hr == S_OK)
	{
		// �����̶���ɫˢ���ı���ʽ
		HR(m_pd2dRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::White),
			m_pColorBrush.GetAddressOf()));
		HR(m_pdwriteFactory->CreateTextFormat(L"����", nullptr, DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 15, L"zh-cn",
			m_pTextFormat.GetAddressOf()));
	}
	else
	{
		// �����쳣����
		assert(m_pd2dRenderTarget);
	}

	// ����������ʾ
	if (m_pCamera != nullptr)
	{
		m_pCamera->SetFrustum(XM_PI / 3, AspectRatio(), 1.0f, 1000.0f);
		m_pCamera->SetViewPort(0.0f, 0.0f, (float)m_ClientWidth, (float)m_ClientHeight);
		m_BasicEffect.SetProjMatrix(m_pCamera->GetProjXM());
	}
}


static std::wstring hitText = L"��ǰʰȡ���壺";
static int hitNum = 0;
static bool isKeep = false;
void GameApp::UpdateScene(float dt)
{

	// ��������¼�����ȡ���ƫ����
	Mouse::State mouseState = m_pMouse->GetState();
	Mouse::State lastMouseState = m_MouseTracker.GetLastState();
	m_MouseTracker.Update(mouseState);

	Keyboard::State keyState = m_pKeyboard->GetState();
	m_KeyboardTracker.Update(keyState);

	auto cam1st = std::dynamic_pointer_cast<FirstPersonCamera>(m_pCamera);

	// ********************
	// ����������Ĳ���
	//

	// �����ƶ�
	if (keyState.IsKeyDown(Keyboard::W))
		cam1st->Walk(dt * 5.0f);
	if (keyState.IsKeyDown(Keyboard::S))
		cam1st->Walk(dt * -5.0f);
	if (keyState.IsKeyDown(Keyboard::A))
		cam1st->Strafe(dt * -5.0f);
	if (keyState.IsKeyDown(Keyboard::D))
		cam1st->Strafe(dt * 5.0f);

	// ��λ��������[-8.9f, 8.9f]��������
	// ��������
	XMFLOAT3 adjustedPos;
	XMStoreFloat3(&adjustedPos, XMVectorClamp(cam1st->GetPositionXM(), XMVectorSet(-8.9f, -1.0f, -8.9f, 0.0f), XMVectorReplicate(8.9f)));
	cam1st->SetPosition(adjustedPos);

	// ��Ұ��ת����ֹ��ʼ�Ĳ�ֵ�����µ�ͻȻ��ת
	cam1st->Pitch(mouseState.y * dt * 1.25f);
	cam1st->RotateY(mouseState.x * dt * 1.25f);

	// ���¹۲����
	m_pCamera->UpdateViewMatrix();
	m_BasicEffect.SetViewMatrix(m_pCamera->GetViewXM());
	m_BasicEffect.SetEyePos(m_pCamera->GetPositionXM());

	// ���ù���ֵ
	m_pMouse->ResetScrollWheelValue();

	// ѡ����պ�
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

	//ʰȡ���
	m_boundingSphere.Center = XMFLOAT3(m_Sphere.GetPosition());
	
	Ray ray = Ray::ScreenToRay(*m_pCamera, (float)(GameApp::m_ClientWidth / 2), (float)(GameApp::m_ClientHeight / 2));
	
	
	if (!ray.Hit(m_boundingSphere))
	{
		hitText = L"��ǰʰȡ���壺";
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
		hitText += L"����";
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

	// �˳���������Ӧ�򴰿ڷ���������Ϣ
	if (m_KeyboardTracker.IsKeyPressed(Keyboard::Escape))
		SendMessage(MainWnd(), WM_DESTROY, 0, 0);
}

void GameApp::DrawScene()
{
	assert(m_pd3dImmediateContext);
	assert(m_pSwapChain);

	// ******************
	// ����Direct3D����
	//
	m_pd3dImmediateContext->ClearRenderTargetView(m_pRenderTargetView.Get(), reinterpret_cast<const float*>(&Colors::Black));
	m_pd3dImmediateContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// ����ģ��
	m_BasicEffect.SetRenderDefault(m_pd3dImmediateContext, BasicEffect::RenderObject);
	m_BasicEffect.SetReflectionEnabled(false);
	m_BasicEffect.SetTextureUsed(true);
	if (m_Sphere.isView)
	{
		m_Sphere.Draw(m_pd3dImmediateContext, m_BasicEffect);
	}


	// �������Բ��
	// ��Ҫ�̶�λ��
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

	//���Ƶ���
	m_BasicEffect.SetRenderDefault(m_pd3dImmediateContext, BasicEffect::RenderObject);
	m_Ground.Draw(m_pd3dImmediateContext, m_BasicEffect);


	// ������պ�
	m_SkyEffect.SetRenderDefault(m_pd3dImmediateContext);
	switch (m_SkyBoxMode)
	{
	case SkyBoxMode::Daylight: m_pDaylight->Draw(m_pd3dImmediateContext, m_SkyEffect, *m_pCamera); break;
	case SkyBoxMode::Sunset: m_pSunset->Draw(m_pd3dImmediateContext, m_SkyEffect, *m_pCamera); break;
	case SkyBoxMode::Desert: m_pDesert->Draw(m_pd3dImmediateContext, m_SkyEffect, *m_pCamera); break;
	}
	


	// ******************
	// ����Direct2D����
	//
	if (m_pd2dRenderTarget != nullptr)
	{
		m_pd2dRenderTarget->BeginDraw();
		std::wstring text = L"��ǰ�����ģʽ: ��һ�˳��ӽ�  Esc�˳�\n"
			"����ƶ�������Ұ W/S/A/D�ƶ�\n"
			"�л���պ�: 1-���� 2-���� 3-ɳĮ\n"
			"��ǰ��պ�: ";

		std::wstring center = L"ʮ";

		switch (m_SkyBoxMode)
		{
		case SkyBoxMode::Daylight: text += L"����"; break;
		case SkyBoxMode::Sunset: text += L"����"; break;
		case SkyBoxMode::Desert: text += L"ɳĮ"; break;
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
	// ��ʼ����պ����

	//����
	m_pDaylight = std::make_unique<SkyRender>(
		m_pd3dDevice, m_pd3dImmediateContext, 
		L"Texture\\daylight.jpg", 
		5000.0f);

	//����
	m_pSunset = std::make_unique<SkyRender>(
		m_pd3dDevice, m_pd3dImmediateContext,
		std::vector<std::wstring>{
		L"Texture\\sunset_posX.bmp", L"Texture\\sunset_negX.bmp",
		L"Texture\\sunset_posY.bmp", L"Texture\\sunset_negY.bmp", 
		L"Texture\\sunset_posZ.bmp", L"Texture\\sunset_negZ.bmp", },
		5000.0f);

	//ɳĮ
	m_pDesert = std::make_unique<SkyRender>(
		m_pd3dDevice, m_pd3dImmediateContext,
		L"Texture\\desertcube1024.dds",
		5000.0f);

	//Ĭ��Ϊ����
	m_SkyBoxMode = SkyBoxMode::Daylight;
	m_BasicEffect.SetTextureCube(m_pDaylight->GetTextureCube());
	// ******************
	// ��ʼ����Ϸ����
	//
	
	Model model;
	// ����
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

	//������İ�Χ��
	m_boundingSphere.Center = XMFLOAT3(m_Sphere.GetPosition());
	m_boundingSphere.Radius = 0.5f;

	// ����
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

	// ����(6������)
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
	// ��ʼ�������
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
	// ��ʼ�������¹۲����ͶӰ����(����������̶�)
	camera->UpdateViewMatrix();
	m_BasicEffect.SetViewMatrix(camera->GetViewXM());
	m_BasicEffect.SetProjMatrix(camera->GetProjXM());


	// ******************
	// ��ʼ������仯��ֵ
	//

	// �����
	DirectionalLight dirLight[4];
	dirLight[0].Ambient = XMFLOAT4(0.15f, 0.15f, 0.15f, 1.0f);		//����
	dirLight[0].Diffuse = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);			//����
	dirLight[0].Specular = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);		//����
	dirLight[0].Direction = XMFLOAT3(-0.577f, -0.577f, 0.577f);		//����
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

