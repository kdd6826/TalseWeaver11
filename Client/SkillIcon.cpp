#include "stdafx.h"
#include "SkillIcon.h"
#include "Monster.h"
#include "KeyManager.h"
CSkillIcon::CSkillIcon()
{
	m_ObjId = OBJ::OBJ_UI;
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CSkillIcon::~CSkillIcon()
{
	Release_GameObject();
}

HRESULT CSkillIcon::Ready_GameObject()
{
	m_tInfo.vPos = { 23.5f, 541.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	//////
	m_tInfo.vDir = { 1.f,1.f,0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };

	//////
	m_tFrame = { 0,1 };

	return S_OK;
}

int CSkillIcon::Update_GameObject()
{
	
	/*rect{ 0, 0, 현재마나 / 최대마나 = 현재마나 퍼센트 * 이미지 가로크기, 이미지 최대세로크기 }*/


	return OBJ_NOEVENT;
}

void CSkillIcon::LateUpdate_GameObject()
{
}

void CSkillIcon::Render_GameObject()
{

	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"UI", L"MultiAttackIcon", 0);
	if (nullptr == pTexInfo)
		return;
	_vec3 vCenter = { _float(pTexInfo->tImageInfo.Width >> 1), _float(pTexInfo->tImageInfo.Height >> 1) , 0.f };
	_matrix matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	matWorld = matScale * matTrans;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &vCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"UI", L"ChainAttackIcon", 0);
	if (nullptr == pTexInfo)
		return;

	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x+30, m_tInfo.vPos.y, 0.f);
	matWorld = matScale * matTrans;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &vCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"UI", L"ASBuffIcon", 0);
	if (nullptr == pTexInfo)
		return;

	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + 60, m_tInfo.vPos.y, 0.f);
	matWorld = matScale * matTrans;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &vCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"UI", L"ThunderBoltIcon", 0);
	if (nullptr == pTexInfo)
		return;

	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + 90, m_tInfo.vPos.y, 0.f);
	matWorld = matScale * matTrans;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &vCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));





}

void CSkillIcon::Release_GameObject()
{
}

void CSkillIcon::OnCollision(CGameObject* _TargetObj)
{
	switch (_TargetObj->GetObjId()) {
	case OBJ::OBJ_MONSTER:
	{
		CMonster* tempCollision = dynamic_cast<CMonster*>(_TargetObj);

		if (tempCollision)
		{
			/*m_SP -= 1;*/
		}
	}
	}
}


CGameObject* CSkillIcon::Create(LPVOID* pArg)
{
	CGameObject* pInstnace = new CSkillIcon;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	return pInstnace;
}

CGameObject * CSkillIcon::Create(_vec3 vpos)
{
	CGameObject* pInstnace = new CSkillIcon;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	pInstnace->SetPos(vpos);
	pInstnace->SetFirstPos(vpos);
	return pInstnace;
}
