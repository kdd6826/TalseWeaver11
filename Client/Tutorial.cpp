#include "stdafx.h"
#include "Tutorial.h"
#include "Terrain.h"
#include "Player.h"
#include "Monster.h"
#include "Mouse.h"
#include "BlueWolf.h"
#include "Scene_Manager.h"
#include "Portal.h"
CTutorial::CTutorial()
{
}


CTutorial::~CTutorial()
{
	Release_Scene();
}

HRESULT CTutorial::Ready_Scene()
{
	CGameObject_Manager::Get_Instance()->Add_GameObject(OBJ::OBJ_TERRAIN, CTerrain::Create(L"../Data/TutorialData.dat"));
	if (ObjManager->GetList(OBJ::OBJ_PLAYER)->size() == 0) {
		CGameObject_Manager::Get_Instance()->Add_GameObject(OBJ::OBJ_PLAYER, CPlayer::Create());
		}
	CGameObject_Manager::Get_Instance()->Add_GameObject(OBJ::OBJ_MOUSE, CMouse::Create());
	
	CGameObject_Manager::Get_Instance()->Add_GameObject(OBJ::OBJ_MONSTER, CBlueWolf::Create({ 1300.f,500.f,0.f }));
	CGameObject_Manager::Get_Instance()->Add_GameObject(OBJ::OBJ_MONSTER, CBlueWolf::Create({ 1400.f,750.f,0.f }));
	CGameObject_Manager::Get_Instance()->Add_GameObject(OBJ::OBJ_MONSTER, CBlueWolf::Create({ 1500.f,350.f,0.f }));
	CGameObject_Manager::Get_Instance()->Add_GameObject(OBJ::OBJ_PORTAL, CPortal::Create({ 1630.f,850.f,0.f }, {1000.f,500.f,0.f},CScene_Manager::SCENE_TOWN1));
	srand(unsigned(time(nullptr)));
	return S_OK;
}

void CTutorial::Update_Scene()
{
	
	iRandX = rand() % 1300;
	
	iRandY = rand() % 1000;
	CGameObject_Manager::Get_Instance()->Update_GameObject();
	
	if (ObjManager->GetList(OBJ::OBJ_MONSTER)->size() <= 8) {
		{

			CGameObject_Manager::Get_Instance()->Add_GameObject(OBJ::OBJ_MONSTER, CBlueWolf::Create({ iRandX+700,iRandY+300,0.f }));
		}
	}
	
	
	
}

void CTutorial::LateUpdate_Scene()
{
	CGameObject_Manager::Get_Instance()->LateUpdate_GameObject();
	CScroll_Manager::Scroll_Lock(TutorialSize);
}

void CTutorial::Render_Scene()
{

	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"TextureEtc", L"Map", 3);

	if (nullptr == pTexInfo)
		return;
	_vec3 vCenter = { _float(pTexInfo->tImageInfo.Width >> 1) , _float(pTexInfo->tImageInfo.Height >> 1) , 0.f };

	_matrix matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, TutorialSize.x / 2 + CScroll_Manager::Get_Scroll(CScroll_Manager::X), TutorialSize.y / 2 + CScroll_Manager::Get_Scroll(CScroll_Manager::Y), 0.f);

	matWorld = matScale * matTrans;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &vCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	CGameObject_Manager::Get_Instance()->Render_GameObject();
}

void CTutorial::Release_Scene()
{
	CGameObject_Manager::Get_Instance()->Release_GameObject(OBJ::OBJ_TERRAIN);
	CGameObject_Manager::Get_Instance()->Release_GameObject(OBJ::OBJ_MONSTER);

	

	

	
}
