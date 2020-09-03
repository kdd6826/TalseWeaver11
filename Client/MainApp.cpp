#include "stdafx.h"
#include "MainApp.h"
#include "Scene_Manager.h"
#include "KeyManager.h"
#include "Frame_Manager.h"
#include "AStar.h"
CMainApp::CMainApp()
	: m_pGraphic_Device(CGraphic_Device::Get_Instance())
	, m_pTime_Manager(CTime_Manager::Get_Instance())
{
}


CMainApp::~CMainApp()
{
	Release_MainApp();
}

void CMainApp::Ready_MainApp()
{
	m_pTime_Manager->Ready_TimeManager();
	if (FAILED(CGraphic_Device::Get_Instance()->Ready_Graphic_Device()))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Terrain/Tile/Tile%d.png", L"Terrain", L"Tile", 11)))
		return;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../TextureEtc/Map/Map%d.png", L"TextureEtc", L"Map", 5)))
		return;

	//플레이어
	//STAND
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/STAND_DOWN/STAND_DOWN%d.png", L"Player", L"STAND_DOWN", 10)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/STAND_LDOWN/STAND_LDOWN%d.png", L"Player", L"STAND_LDOWN", 10)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/STAND_LEFT/STAND_LEFT%d.png", L"Player", L"STAND_LEFT", 10)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/STAND_LUP/STAND_LUP%d.png", L"Player", L"STAND_LUP", 10)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/STAND_UP/STAND_UP%d.png", L"Player", L"STAND_UP", 10)))
		return;

	//RUN
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/RUN_DOWN/RUN_DOWN%d.png", L"Player", L"RUN_DOWN", 8)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/RUN_LDOWN/RUN_LDOWN%d.png", L"Player", L"RUN_LDOWN", 8)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/RUN_LEFT/RUN_LEFT%d.png", L"Player", L"RUN_LEFT", 8)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/RUN_LUP/RUN_LUP%d.png", L"Player", L"RUN_LUP", 8)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/RUN_UP/RUN_UP%d.png", L"Player", L"RUN_UP", 8)))
		return;

	//ATTACK
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/ATTACK1_DOWN/ATTACK1_DOWN%d.png", L"Player", L"ATTACK1_DOWN", 13)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/ATTACK1_LDOWN/ATTACK1_LDOWN%d.png", L"Player", L"ATTACK1_LDOWN", 8)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/ATTACK1_LEFT/ATTACK1_LEFT%d.png", L"Player", L"ATTACK1_LEFT", 8)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/ATTACK1_LUP/ATTACK1_LUP%d.png", L"Player", L"ATTACK1_LUP", 8)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/ATTACK1_UP/ATTACK1_UP%d.png", L"Player", L"ATTACK1_UP", 8)))
		return;







	//몬스터
	//BLUEWOLF
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/BlueWolf/STAND_LDOWN/Stand_LDown%d.png", L"BlueWolf", L"Stand_LDown", 6)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/BlueWolf/STAND_LUP/Stand_LUp%d.png", L"BlueWolf", L"Stand_LUp", 6)))
		return;


	CScene_Manager::Get_Instance()->Change_Scene(CScene_Manager::SCENE_TUTORIAL);

}

void CMainApp::Update_MainApp()
{
	m_pTime_Manager->Update_TimeManager();
	CScene_Manager::Get_Instance()->Update_Scene();
	CKey_Manager::Get_Instance()->Update_KeyManager();
}

void CMainApp::Late_Update_MainApp()
{
	CScene_Manager::Get_Instance()->LateUpdate_Scene();
}

void CMainApp::Render_MainApp(CFrame_Manager* pFrameManager)
{
	m_pGraphic_Device->Render_Begin();
	CScene_Manager::Get_Instance()->Render_Scene();
	pFrameManager->Render_FrameManager();
	m_pGraphic_Device->Render_End();
}

void CMainApp::Release_MainApp()
{
	CAStar::Destroy_Instance();
	m_pTime_Manager->Destroy_Instance();
	CGameObject_Manager::Destroy_Instance();
	CScene_Manager::Destroy_Instance();
	CTexture_Manager::Destroy_Instance();
	m_pGraphic_Device->Destroy_Instance();
}
