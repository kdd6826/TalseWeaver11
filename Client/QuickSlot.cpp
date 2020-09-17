#include "stdafx.h"
#include "QuickSlot.h"
#include "Monster.h"
#include "KeyManager.h"
CQuickSlot::CQuickSlot()
{
	m_ObjId = OBJ::OBJ_UI;
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CQuickSlot::~CQuickSlot()
{
	Release_GameObject();
}

HRESULT CQuickSlot::Ready_GameObject()
{
	m_tInfo.vPos = { 67.f, 550.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	//////
	m_tInfo.vDir = { 1.f,1.f,0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };

	//////
	m_tFrame = { 0,1 };

	return S_OK;
}

int CQuickSlot::Update_GameObject()
{
	
	/*rect{ 0, 0, 현재마나 / 최대마나 = 현재마나 퍼센트 * 이미지 가로크기, 이미지 최대세로크기 }*/
	

	return OBJ_NOEVENT;
}

void CQuickSlot::LateUpdate_GameObject()
{
}

void CQuickSlot::Render_GameObject()
{

	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"UI", L"QuickSlot", 0);
	if (nullptr == pTexInfo)
		return;


	_vec3 vCenter = { _float(pTexInfo->tImageInfo.Width >> 1), _float(pTexInfo->tImageInfo.Height >> 1) , 0.f };
	_matrix matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	matWorld = matScale * matTrans;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &vCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

}

void CQuickSlot::Release_GameObject()
{
}

void CQuickSlot::OnCollision(CGameObject* _TargetObj)
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


CGameObject* CQuickSlot::Create(LPVOID* pArg)
{
	CGameObject* pInstnace = new CQuickSlot;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	return pInstnace;
}

CGameObject * CQuickSlot::Create(_vec3 vpos)
{
	CGameObject* pInstnace = new CQuickSlot;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	pInstnace->SetPos(vpos);
	pInstnace->SetFirstPos(vpos);
	return pInstnace;
}
