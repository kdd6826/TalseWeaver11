#include "stdafx.h"
#include "Shop.h"
#include "Terrain.h"
#include "Player.h"
#include "Monster.h"
#include "BlueWolf.h"
#include "Scene_Manager.h"
CShop::CShop()
{
}


CShop::~CShop()
{
	Release_Scene();
}

HRESULT CShop::Ready_Scene()
{
	
	CGameObject_Manager::Get_Instance()->Add_GameObject(OBJ::OBJ_TERRAIN, CTerrain::Create(L"../Data/ShopData.dat"));
		
	CGameObject_Manager::Get_Instance()->Add_GameObject(OBJ::OBJ_MONSTER, CBlueWolf::Create({ 1300.f, 400.f,0.f }));

	_vec3 pos = { 850.f,650.f,0.f };
	CGameObject_Manager::Get_Instance()->Get_Player()->SetPos(pos);
	CScroll_Manager::Init_ScrollXY();
	CScroll_Manager::Set_Scroll({ -pos.x / 2,-pos.y / 2,0.f });
	return S_OK;
}

void CShop::Update_Scene()
{
	CGameObject_Manager::Get_Instance()->Update_GameObject();
	_vec3 pos = CGameObject_Manager::Get_Instance()->Get_Player()->GetPos();

	if (pos.x > 850 && pos.x < 950 && pos.y > 650 && pos.y < 700)
	{
		CScene_Manager::Get_Instance()->Change_Scene(CScene_Manager::SCENE_TOWN1);
	}
}

void CShop::LateUpdate_Scene()
{
	CGameObject_Manager::Get_Instance()->LateUpdate_GameObject();
	CScroll_Manager::Scroll_Lock(ShopSize);
}

void CShop::Render_Scene()
{

	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"TextureEtc", L"Map", 0);

	if (nullptr == pTexInfo)
		return;
	_vec3 vCenter = { _float(pTexInfo->tImageInfo.Width >> 1) , _float(pTexInfo->tImageInfo.Height >> 1) , 0.f };

	_matrix matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, ShopSize.x / 2 + CScroll_Manager::Get_Scroll(CScroll_Manager::X), ShopSize.y / 2 + CScroll_Manager::Get_Scroll(CScroll_Manager::Y), 0.f);

	matWorld = matScale * matTrans;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &vCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	CGameObject_Manager::Get_Instance()->Render_GameObject();
}

void CShop::Release_Scene()
{
	CGameObject_Manager::Get_Instance()->Release_GameObject(OBJ::OBJ_TERRAIN);
	CGameObject_Manager::Get_Instance()->Release_GameObject(OBJ::OBJ_MONSTER);

	_vec3 pos = { 350.f,500.f,0.f };
	CGameObject_Manager::Get_Instance()->Get_Player()->SetPos(pos);
	CScroll_Manager::Init_ScrollXY();
	CScroll_Manager::Set_Scroll({ -pos.x / 2,-pos.y / 2,0.f });

	dynamic_cast<CPlayer*>(CGameObject_Manager::Get_Instance()->Get_Player())->StopAStar();
}
