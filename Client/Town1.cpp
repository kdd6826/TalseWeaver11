#include "stdafx.h"
#include "Town1.h"
#include "Terrain.h"
#include "Player.h"
#include "Monster.h"
#include "BlueWolf.h"
#include "Scene_Manager.h"
#include "Portal.h"
CTown1::CTown1()
{
}


CTown1::~CTown1()
{
	Release_Scene();
}

HRESULT CTown1::Ready_Scene()
{
	
	dynamic_cast<CPlayer*>(CGameObject_Manager::Get_Instance()->Get_Player())->StopAStar();
	CGameObject_Manager::Get_Instance()->Add_GameObject(OBJ::OBJ_TERRAIN, CTerrain::Create(L"../Data/TileData.dat"));
	CGameObject_Manager::Get_Instance()->Add_GameObject(OBJ::OBJ_PORTAL, CPortal::Create({ 700.f,750.f,0.f }, { 750.f,600.f,0.f }, CScene_Manager::SCENE_TUTORIAL));
	CGameObject_Manager::Get_Instance()->Add_GameObject(OBJ::OBJ_PORTAL, CPortal::Create({ 390.f,450.f,0.f }, { 750.f,600.f,0.f }, CScene_Manager::SCENE_SHOP));



	return S_OK;
}

void CTown1::Update_Scene()
{
	CGameObject_Manager::Get_Instance()->Update_GameObject();
	ReScroll();
}

void CTown1::LateUpdate_Scene()
{
	CGameObject_Manager::Get_Instance()->LateUpdate_GameObject();
	CScroll_Manager::Scroll_Lock(Town1Size);
}

void CTown1::Render_Scene()
{

	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"TextureEtc", L"Map", 2);

	if (nullptr == pTexInfo)
		return;
	_vec3 vCenter = { _float(pTexInfo->tImageInfo.Width >> 1) , _float(pTexInfo->tImageInfo.Height >> 1) , 0.f };

	_matrix matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, Town1Size.x / 2 + CScroll_Manager::Get_Scroll(CScroll_Manager::X), Town1Size.y / 2 + CScroll_Manager::Get_Scroll(CScroll_Manager::Y), 0.f);

	matWorld = matScale * matTrans;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &vCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	CGameObject_Manager::Get_Instance()->Render_GameObject();
}

void CTown1::Release_Scene()
{
	CGameObject_Manager::Get_Instance()->Release_GameObject(OBJ::OBJ_TERRAIN);
	CGameObject_Manager::Get_Instance()->Release_GameObject(OBJ::OBJ_MONSTER);
	if (ObjManager->GetList(OBJ::OBJ_PORTAL)->size() == 1) {
		CGameObject_Manager::Get_Instance()->Release_GameObject(OBJ::OBJ_PORTAL);
	}
}
