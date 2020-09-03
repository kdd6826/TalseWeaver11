#include "stdafx.h"
#include "Tutorial.h"
#include "Terrain.h"
#include "Player.h"
#include "Monster.h"
#include "BlueWolf.h"
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

	CGameObject_Manager::Get_Instance()->Add_GameObject(OBJ::OBJ_PLAYER, CPlayer::Create());
	CGameObject_Manager::Get_Instance()->Add_GameObject(OBJ::OBJ_MONSTER, CBlueWolf::Create());
	
	return S_OK;
}

void CTutorial::Update_Scene()
{
	CGameObject_Manager::Get_Instance()->Update_GameObject();

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
