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

bool GameApp::Init()
{
	if (!D3DApp::Init())
		return false;

	if (!InitEffect())
		return false;

	if (!InitResource())
		return false;

	// 初始化鼠标，键盘不需要
	m_pMouse->SetWindow(m_hMainWnd);
	m_pMouse->SetMode(DirectX::Mouse::MODE_ABSOLUTE);

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
			DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 20, L"zh-cn",
			m_pTextFormat.GetAddressOf()));
	}
	else
	{
		// 报告异常问题
		assert(m_pd2dRenderTarget);
	}
}

void GameApp::UpdateScene(float dt)
{
	Keyboard::State state = m_pKeyboard->GetState();
	m_KeyboardTracker.Update(state);

	// 键盘切换模式
	if (m_KeyboardTracker.IsKeyPressed(Keyboard::D1))
	{
		// 播放木箱动画
		m_CurrMode = ShowMode::WoodCrate;
		m_pd3dImmediateContext->IASetInputLayout(m_pVertexLayout3D.Get());
		auto meshData = Geometry::CreateBox(2);
		ResetMesh(meshData);
		m_pd3dImmediateContext->VSSetShader(m_pVertexShader3D.Get(), nullptr, 0);
		m_pd3dImmediateContext->PSSetShader(m_pPixelShader3D.Get(), nullptr, 0);
	}
	else if (m_KeyboardTracker.IsKeyPressed(Keyboard::D2))
	{
		//播放火焰动画
		m_CurrMode = ShowMode::FireAnim;
		m_CurrFrame = 0;
		m_pd3dImmediateContext->IASetInputLayout(m_pVertexLayout2D.Get());
		auto meshData = Geometry::Create2DShow();
		ResetMesh(meshData);
		m_pd3dImmediateContext->VSSetShader(m_pVertexShader2D.Get(), nullptr, 0);
		m_pd3dImmediateContext->PSSetShader(m_pPixelShader2D.Get(), nullptr, 0);
		m_pd3dImmediateContext->PSSetShaderResources(0, 1, m_pFireAnims[0].GetAddressOf());
	}

	else if (m_KeyboardTracker.IsKeyPressed(Keyboard::D3))
	{
		//播放特效箱子
		m_CurrMode = ShowMode::EffectBox;
		m_pd3dImmediateContext->IASetInputLayout(m_pVertexLayout3D.Get());
		auto meshData = Geometry::CreateBox(2);
		ResetMesh(meshData);
		m_pd3dImmediateContext->VSSetShader(m_pVertexShader3D1.Get(), nullptr, 0);
		m_pd3dImmediateContext->PSSetShader(m_pPixelShader3D1.Get(), nullptr, 0);
		
	}

	//如果当前显示立方体，则进行旋转操作
	if (m_CurrMode == ShowMode::WoodCrate || m_CurrMode == ShowMode::EffectBox)
	{
		static float phi = 0.0f, theta = 0.0f;
		phi += 0.0001f, theta += 0.0001f;
		XMMATRIX W = XMMatrixRotationX(phi) * XMMatrixRotationY(theta);
		m_VSConstantBuffer.world = XMMatrixTranspose(W);
		m_VSConstantBuffer.worldInvTranspose = XMMatrixInverse(nullptr, W);	// 两次转置抵消

		// 更新常量缓冲区，让立方体转起来
		D3D11_MAPPED_SUBRESOURCE mappedData;
		HR(m_pd3dImmediateContext->Map(m_pConstantBuffers[0].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
		memcpy_s(mappedData.pData, sizeof(VSConstantBuffer), &m_VSConstantBuffer, sizeof(VSConstantBuffer));
		m_pd3dImmediateContext->Unmap(m_pConstantBuffers[0].Get(), 0);

		HR(m_pd3dImmediateContext->Map(m_pConstantBuffers[1].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
		memcpy_s(mappedData.pData, sizeof(PSConstantBuffer), &m_PSConstantBuffer, sizeof(PSConstantBuffer));
		m_pd3dImmediateContext->Unmap(m_pConstantBuffers[1].Get(), 0);

	}

	if (m_CurrMode == ShowMode::EffectBox)
	{
		//旋转合成纹理
		m_pd3dImmediateContext->VSSetConstantBuffers(1, 1, m_pConstantBuffers[2].GetAddressOf());
		static float thete = 0.0f;

		thete += 0.001f;
		D3D11_MAPPED_SUBRESOURCE mappedData;
		m_Cbuffer.roate = XMMatrixTranspose(XMMatrixTranslation(-0.5f, -0.5f, 0)*XMMatrixRotationZ(thete)*XMMatrixTranslation(0.5f, 0.5f, 0));
		HR(m_pd3dImmediateContext->Map(m_pConstantBuffers[2].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
		memcpy_s(mappedData.pData, sizeof(RoateBuffer), &m_Cbuffer, sizeof(RoateBuffer));
		m_pd3dImmediateContext->Unmap(m_pConstantBuffers[2].Get(), 0);
	}
	
	//如果当前显示火焰，则进行限制操作
	else if (m_CurrMode == ShowMode::FireAnim)
	{
		// 用于限制在1秒60帧
		static float totDeltaTime = 0;

		totDeltaTime += dt;
		if (totDeltaTime > 1.0f / 60)
		{
			totDeltaTime -= 1.0f / 60;
			m_CurrFrame = (m_CurrFrame + 1) % 120;
			m_pd3dImmediateContext->PSSetShaderResources(0, 1, m_pFireAnims[m_CurrFrame].GetAddressOf());
		}
	}
}

void GameApp::DrawScene()
{
	assert(m_pd3dImmediateContext);
	assert(m_pSwapChain);

	m_pd3dImmediateContext->ClearRenderTargetView(m_pRenderTargetView.Get(), reinterpret_cast<const float*>(&Colors::Black));
	m_pd3dImmediateContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	
	// 绘制几何模型
	if (m_CurrMode == ShowMode::WoodCrate)
	{
		for (int i = 0; i < 6; ++i)
		{
			m_pd3dImmediateContext->PSSetShaderResources(0, 1, m_pWoodCrates[i].GetAddressOf());
			m_pd3dImmediateContext->DrawIndexed((i + 1) * 6, 0, 0);
		}
	}
	// 绘制火焰动画
	if (m_CurrMode == ShowMode::FireAnim)
	{
		m_pd3dImmediateContext->DrawIndexed(m_IndexCount, 0, 0);
	}

	// 绘制特效箱子
	if (m_CurrMode == ShowMode::EffectBox)
	{
		m_pd3dImmediateContext->PSSetShaderResources(0, 1, m_pEffectBoxs[0].GetAddressOf());
		m_pd3dImmediateContext->PSSetShaderResources(1, 1, m_pEffectBoxs[1].GetAddressOf());
		m_pd3dImmediateContext->DrawIndexed(m_IndexCount, 0, 0);
	}

	//
	// 绘制Direct2D部分
	//
	if (m_pd2dRenderTarget != nullptr)
	{
		m_pd2dRenderTarget->BeginDraw();
		static const WCHAR* textStr = L"切换类型: 1-普通立方体 2-2D火焰 3-特效立方体\n";
			//"切换模型: Q-立方体 W-球体 E-圆柱体";
		static const WCHAR* textInfor = L"2019QG工作室手游组第4次小组培训\n"
										 "                         朱豪光\n"
										 "                   2019年4月19日";
		m_pd2dRenderTarget->DrawTextW(textStr, (UINT32)wcslen(textStr), m_pTextFormat.Get(),
			D2D1_RECT_F{ 0.0f, 0.0f, 600.0f, 200.0f }, m_pColorBrush.Get());
		m_pd2dRenderTarget->DrawTextW(textInfor, (UINT32)wcslen(textInfor), m_pTextFormat.Get(),
			D2D1_RECT_F{ 480.0f, 520.0f, (float)m_ClientWidth, (float)m_ClientHeight }, m_pColorBrush.Get());
		HR(m_pd2dRenderTarget->EndDraw());
	}

	HR(m_pSwapChain->Present(0, 0));
}



bool GameApp::InitEffect()
{
	ComPtr<ID3DBlob> blob;

	// 创建顶点着色器
	HR(CreateShaderFromFile(L"HLSL\\Light_VS.cso", L"HLSL\\Light_VS.hlsl", "VS", "vs_5_0", blob.ReleaseAndGetAddressOf()));
	HR(m_pd3dDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pVertexShader.GetAddressOf()));
	// 创建并绑定顶点布局
	HR(m_pd3dDevice->CreateInputLayout(VertexPosNormalColor::inputLayout, ARRAYSIZE(VertexPosNormalColor::inputLayout),
		blob->GetBufferPointer(), blob->GetBufferSize(), m_pVertexLayout.GetAddressOf()));

	// 创建像素着色器
	HR(CreateShaderFromFile(L"HLSL\\Light_PS.cso", L"HLSL\\Light_PS.hlsl", "PS", "ps_5_0", blob.ReleaseAndGetAddressOf()));
	HR(m_pd3dDevice->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pPixelShader.GetAddressOf()));

	// 创建顶点着色器(2D)
	HR(CreateShaderFromFile(L"HLSL\\Basic_VS_2D.cso", L"HLSL\\Basic_VS_2D.hlsl", "VS_2D", "vs_5_0", blob.ReleaseAndGetAddressOf()));
	HR(m_pd3dDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pVertexShader2D.GetAddressOf()));
	// 创建顶点布局(2D)
	HR(m_pd3dDevice->CreateInputLayout(VertexPosTex::inputLayout, ARRAYSIZE(VertexPosTex::inputLayout),
		blob->GetBufferPointer(), blob->GetBufferSize(), m_pVertexLayout2D.GetAddressOf()));

	// 创建像素着色器(2D)
	HR(CreateShaderFromFile(L"HLSL\\Basic_PS_2D.cso", L"HLSL\\Basic_PS_2D.hlsl", "PS_2D", "ps_5_0", blob.ReleaseAndGetAddressOf()));
	HR(m_pd3dDevice->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pPixelShader2D.GetAddressOf()));


	
	// 创建顶点着色器(3D)
	HR(CreateShaderFromFile(L"HLSL\\Basic_VS_3D.cso", L"HLSL\\Basic_VS_3D.hlsl", "VS_3D", "vs_5_0", blob.ReleaseAndGetAddressOf()));
	HR(m_pd3dDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pVertexShader3D.GetAddressOf()));
	// 创建顶点布局(3D)
	HR(m_pd3dDevice->CreateInputLayout(VertexPosNormalTex::inputLayout, ARRAYSIZE(VertexPosNormalTex::inputLayout),
		blob->GetBufferPointer(), blob->GetBufferSize(), m_pVertexLayout3D.GetAddressOf()));

	// 创建像素着色器(3D)
	HR(CreateShaderFromFile(L"HLSL\\Basic_PS_3D.cso", L"HLSL\\Basic_PS_3D.hlsl", "PS_3D", "ps_5_0", blob.ReleaseAndGetAddressOf()));
	HR(m_pd3dDevice->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pPixelShader3D.GetAddressOf()));


	//创建新的顶点着色器，像素着色器和顶点布局
	// 创建顶点着色器(3D)
	HR(CreateShaderFromFile(L"HLSL\\Basic_VS.cso", L"HLSL\\Basic_VS.hlsl", "VS", "vs_5_0", blob.ReleaseAndGetAddressOf()));
	HR(m_pd3dDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pVertexShader3D1.GetAddressOf()));
	// 创建顶点布局(3D)
	HR(m_pd3dDevice->CreateInputLayout(VertexPosNormalTex::inputLayout, ARRAYSIZE(VertexPosNormalTex::inputLayout),
		blob->GetBufferPointer(), blob->GetBufferSize(), m_pVertexLayout3D.GetAddressOf()));

	// 创建像素着色器(3D)
	HR(CreateShaderFromFile(L"HLSL\\Basic_PS.cso", L"HLSL\\Basic_PS.hlsl", "PS", "ps_5_0", blob.ReleaseAndGetAddressOf()));
	HR(m_pd3dDevice->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pPixelShader3D1.GetAddressOf()));

	return true;
}

bool GameApp::InitResource()
{
	// 初始化网格模型并设置到输入装配阶段
	auto meshData = Geometry::CreateBox(1);
	ResetMesh(meshData);

	// ******************
	// 设置常量缓冲区描述
	D3D11_BUFFER_DESC cbd;
	ZeroMemory(&cbd, sizeof(cbd));
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.ByteWidth = sizeof(VSConstantBuffer);
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	// 新建用于VS和PS的常量缓冲区
	HR(m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pConstantBuffers[0].GetAddressOf()));
	cbd.ByteWidth = sizeof(PSConstantBuffer);
	HR(m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pConstantBuffers[1].GetAddressOf()));
	cbd.ByteWidth = sizeof(RoateBuffer);
	HR(m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pConstantBuffers[2].GetAddressOf()));

	// ******************

	// 初始化木箱纹理
	m_pWoodCrates.resize(6);
	HR(CreateWICTextureFromFile(m_pd3dDevice.Get(), L"Resource\\WoodCrate.dds", nullptr, m_pWoodCrates[0].GetAddressOf()));
	HR(CreateWICTextureFromFile(m_pd3dDevice.Get(), L"Resource\\Flare.dds", nullptr, m_pWoodCrates[1].GetAddressOf()));
	HR(CreateWICTextureFromFile(m_pd3dDevice.Get(), L"Resource\\FlareAlpha.dds", nullptr, m_pWoodCrates[2].GetAddressOf()));
	HR(CreateWICTextureFromFile(m_pd3dDevice.Get(), L"Resource\\water.dds", nullptr, m_pWoodCrates[3].GetAddressOf()));
	HR(CreateWICTextureFromFile(m_pd3dDevice.Get(), L"Resource\\ice.dds", nullptr, m_pWoodCrates[4].GetAddressOf()));
	HR(CreateWICTextureFromFile(m_pd3dDevice.Get(), L"Resource\\floor.dds", nullptr, m_pWoodCrates[5].GetAddressOf()));
	
	// 初始化火焰纹理
	WCHAR strFile[40];
	m_pFireAnims.resize(120);
	for (int i = 1; i <= 120; ++i)
	{
		wsprintf(strFile, L"Resource\\FireAnim\\Fire%03d.bmp", i);
		HR(CreateWICTextureFromFile(m_pd3dDevice.Get(), strFile, nullptr, m_pFireAnims[i - 1].GetAddressOf()));
	}

	//初始化特效箱子纹理
	m_pEffectBoxs.resize(2);
	HR(CreateWICTextureFromFile(m_pd3dDevice.Get(), L"Resource\\Flare.dds", nullptr, m_pEffectBoxs[0].GetAddressOf()));
	HR(CreateWICTextureFromFile(m_pd3dDevice.Get(), L"Resource\\FlareAlpha.dds", nullptr, m_pEffectBoxs[1].GetAddressOf()));


	// 初始化采样器状态
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	HR(m_pd3dDevice->CreateSamplerState(&sampDesc, m_pSamplerState.GetAddressOf()));


	// ******************
	// 初始化常量缓冲区的值

	// 初始化用于VS的常量缓冲区的值
	m_VSConstantBuffer.world = XMMatrixIdentity();
	m_VSConstantBuffer.view = XMMatrixTranspose(XMMatrixLookAtLH(
		XMVectorSet(0.0f, 0.0f, -5.0f, 0.0f),
		XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
		XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
	));
	m_VSConstantBuffer.proj = XMMatrixTranspose(XMMatrixPerspectiveFovLH(XM_PIDIV2, AspectRatio(), 1.0f, 1000.0f));
	m_VSConstantBuffer.worldInvTranspose = XMMatrixIdentity();

	// 初始化用于PS的常量缓冲区的值
	// 这里只使用平行光来演示
	m_PSConstantBuffer.dirLight[0].Ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	m_PSConstantBuffer.dirLight[0].Diffuse = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	m_PSConstantBuffer.dirLight[0].Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	m_PSConstantBuffer.dirLight[0].Direction = XMFLOAT3(-0.577f, -0.577f, 0.577f);
	m_PSConstantBuffer.numDirLight = 1;
	m_PSConstantBuffer.numPointLight = 0;
	m_PSConstantBuffer.numSpotLight = 0;

	// 初始化材质
	m_PSConstantBuffer.material.Ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	m_PSConstantBuffer.material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_PSConstantBuffer.material.Specular = XMFLOAT4(0.1f, 0.1f, 0.1f, 5.0f);
	// 注意不要忘记设置此处的观察位置，否则高亮部分会有问题
	m_PSConstantBuffer.eyePos = XMFLOAT4(0.0f, 0.0f, -5.0f, 0.0f);

	// 更新PS常量缓冲区资源
	D3D11_MAPPED_SUBRESOURCE mappedData;
	HR(m_pd3dImmediateContext->Map(m_pConstantBuffers[1].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
	memcpy_s(mappedData.pData, sizeof(PSConstantBuffer), &m_PSConstantBuffer, sizeof(PSConstantBuffer));
	m_pd3dImmediateContext->Unmap(m_pConstantBuffers[1].Get(), 0);

	m_Cbuffer.roate = XMMatrixIdentity();

	HR(m_pd3dImmediateContext->Map(m_pConstantBuffers[2].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
	memcpy_s(mappedData.pData, sizeof(RoateBuffer), &m_Cbuffer, sizeof(RoateBuffer));
	m_pd3dImmediateContext->Unmap(m_pConstantBuffers[2].Get(), 0);

	// ******************
	// 给渲染管线各个阶段绑定好所需资源
	// 设置图元类型，设定输入布局
	m_pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pd3dImmediateContext->IASetInputLayout(m_pVertexLayout3D.Get());
	// 默认绑定3D着色器
	m_pd3dImmediateContext->VSSetShader(m_pVertexShader3D.Get(), nullptr, 0);
	// VS常量缓冲区对应HLSL寄存于b0的常量缓冲区
	m_pd3dImmediateContext->VSSetConstantBuffers(0, 1, m_pConstantBuffers[0].GetAddressOf());
	// PS常量缓冲区对应HLSL寄存于b1的常量缓冲区
	m_pd3dImmediateContext->PSSetConstantBuffers(1, 1, m_pConstantBuffers[1].GetAddressOf());
	m_pd3dImmediateContext->VSSetConstantBuffers(2, 1, m_pConstantBuffers[2].GetAddressOf());
	// 像素着色阶段设置好采样器
	m_pd3dImmediateContext->PSSetSamplers(0, 1, m_pSamplerState.GetAddressOf());
	m_pd3dImmediateContext->PSSetShaderResources(0, 1, m_pWoodCrates[0].GetAddressOf());
	m_pd3dImmediateContext->PSSetShader(m_pPixelShader3D.Get(), nullptr, 0);


	// 像素着色阶段默认设置木箱纹理
	m_CurrMode = ShowMode::WoodCrate;

	return true;
	
}

template<class VertexType>
bool GameApp::ResetMesh(const Geometry::MeshData<VertexType>& meshData)
{
	// 释放旧资源
	m_pVertexBuffer.Reset();
	m_pIndexBuffer.Reset();



	// 设置顶点缓冲区描述
	D3D11_BUFFER_DESC vbd;
	ZeroMemory(&vbd, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = (UINT)meshData.vertexVec.size() * sizeof(VertexType);
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	// 新建顶点缓冲区
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = meshData.vertexVec.data();
	HR(m_pd3dDevice->CreateBuffer(&vbd, &InitData, m_pVertexBuffer.GetAddressOf()));

	// 输入装配阶段的顶点缓冲区设置
	UINT stride = sizeof(VertexType);			// 跨越字节数
	UINT offset = 0;							// 起始偏移量

	m_pd3dImmediateContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);



	// 设置索引缓冲区描述
	m_IndexCount = (UINT)meshData.indexVec.size();
	D3D11_BUFFER_DESC ibd;
	ZeroMemory(&ibd, sizeof(ibd));
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(WORD) * m_IndexCount;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	// 新建索引缓冲区
	InitData.pSysMem = meshData.indexVec.data();
	HR(m_pd3dDevice->CreateBuffer(&ibd, &InitData, m_pIndexBuffer.GetAddressOf()));
	// 输入装配阶段的索引缓冲区设置
	m_pd3dImmediateContext->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

	return true;
}

