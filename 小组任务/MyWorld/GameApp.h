#ifndef GAMEAPP_H
#define GAMEAPP_H

#include "d3dApp.h"
#include "Camera.h"
#include "GameObject.h"
#include "SkyRender.h"
#include "ObjReader.h"
#include "Collision.h"
class GameApp : public D3DApp
{
public:
	// �����ģʽ
	enum class CameraMode { FirstPerson, ThirdPerson, Free };
	// ��պ�ģʽ
	enum class SkyBoxMode { Daylight, Sunset, Desert };

public:
	GameApp(HINSTANCE hInstance);
	~GameApp();

	bool Init();
	void OnResize();
	void UpdateScene(float dt);
	void DrawScene();

private:
	bool InitResource();
	
private:
	
	ComPtr<ID2D1SolidColorBrush> m_pColorBrush;				    // ��ɫ��ˢ
	ComPtr<IDWriteFont> m_pFont;								// ����
	ComPtr<IDWriteTextFormat> m_pTextFormat;					// �ı���ʽ

	GameObject m_Sphere;										// ��
	GameObject m_Ground;										// ����
	std::vector<GameObject> m_Cylinder;							// Բ��

	BasicEffect m_BasicEffect;								    // ������Ⱦ��Ч����
	
	SkyEffect m_SkyEffect;									    // ��պ���Ч����
	std::unique_ptr<SkyRender> m_pDaylight;					    // ��պ�(����)
	std::unique_ptr<SkyRender> m_pSunset;						// ��պ�(����)
	std::unique_ptr<SkyRender> m_pDesert;						// ��պ�(ɳĮ)
	SkyBoxMode m_SkyBoxMode;									// ��պ�ģʽ

	DirectX::BoundingSphere m_boundingSphere;					//��İ�Χ��

	std::shared_ptr<Camera> m_pCamera;						    // �����
	CameraMode m_CameraMode;									// �����ģʽ

	ObjReader m_ObjReader;									    // ģ�Ͷ�ȡ����
};


#endif