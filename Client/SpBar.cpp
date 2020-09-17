#include "stdafx.h"
#include "SpBar.h"
#include "Monster.h"
#include "KeyManager.h"
CSpBar::CSpBar()
{
	m_ObjId = OBJ::OBJ_UI;
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CSpBar::~CSpBar()
{
	Release_GameObject();
}

HRESULT CSpBar::Ready_GameObject()
{
	m_tInfo.vPos = { 142.f, 65.f, 0.f };
	m_tInfo.vSize = { 0.05f, 1.f, 0.f };
	//////
	m_tInfo.vDir = { 1.f,1.f,0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };

	//////
	m_tFrame = { 0,1 };

	return S_OK;
}

int CSpBar::Update_GameObject()
{
	m_tInfo.vSize.x = float(CGameObject_Manager::Get_Instance()->Get_Player()->GetSp()) / float(CGameObject_Manager::Get_Instance()->Get_Player()->GetMaxSp());
	/*rect{ 0, 0, 현재마나 / 최대마나 = 현재마나 퍼센트 * 이미지 가로크기, 이미지 최대세로크기 }*/
	m_tInfo.vPos.x = (142 - 0.08*(float(CGameObject_Manager::Get_Instance()->Get_Player()->GetMaxSp()) - float(CGameObject_Manager::Get_Instance()->Get_Player()->GetSp())) / 2);

	return OBJ_NOEVENT;
}

void CSpBar::LateUpdate_GameObject()
{
}

void CSpBar::Render_GameObject()
{

	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"UI", L"SpBar", 0);
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

void CSpBar::Release_GameObject()
{
}

void CSpBar::OnCollision(CGameObject* _TargetObj)
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


CGameObject* CSpBar::Create(LPVOID* pArg)
{
	CGameObject* pInstnace = new CSpBar;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	return pInstnace;
}

CGameObject * CSpBar::Create(_vec3 vpos)
{
	CGameObject* pInstnace = new CSpBar;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	pInstnace->SetPos(vpos);
	pInstnace->SetFirstPos(vpos);
	return pInstnace;
}
