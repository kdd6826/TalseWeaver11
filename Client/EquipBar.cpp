#include "stdafx.h"
#include "EquipBar.h"
#include "Monster.h"
#include "KeyManager.h"
CEquipBar::CEquipBar()
{
	m_ObjId = OBJ::OBJ_BUTTON;
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CEquipBar::~CEquipBar()
{
	Release_GameObject();
}

HRESULT CEquipBar::Ready_GameObject()
{
	m_tInfo.vPos = { 790.f, 150.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	//////
	m_tInfo.vDir = { 1.f,1.f,0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };

	//////
	m_szFrameKey = L"EquipBarUp";
	m_tFrame = { 0,1 };

	return S_OK;
}

int CEquipBar::Update_GameObject()
{




	return OBJ_NOEVENT;
}

void CEquipBar::LateUpdate_GameObject()
{
}

void CEquipBar::Render_GameObject()
{

	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"UI", m_szFrameKey, 0);
	if (nullptr == pTexInfo)
		return;

	m_tInfo.vRealSize = { float(pTexInfo->tImageInfo.Width),  float(pTexInfo->tImageInfo.Height), 0.f };
	_vec3 vCenter = { _float(pTexInfo->tImageInfo.Width >> 1), _float(pTexInfo->tImageInfo.Height >> 1) , 0.f };
	_matrix matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	matWorld = matScale * matTrans;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &vCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

}

void CEquipBar::Release_GameObject()
{
}

void CEquipBar::OnCollision(CGameObject* _TargetObj)
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


CGameObject* CEquipBar::Create(LPVOID* pArg)
{
	CGameObject* pInstnace = new CEquipBar;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	return pInstnace;
}

CGameObject * CEquipBar::Create(_vec3 vpos)
{
	CGameObject* pInstnace = new CEquipBar;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	pInstnace->SetPos(vpos);
	pInstnace->SetFirstPos(vpos);
	return pInstnace;
}
