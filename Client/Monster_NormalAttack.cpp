#include "stdafx.h"
#include "Monster_NormalAttack.h"
#include "Monster.h"
#include "Player.h"
#include "KeyManager.h"
CMonster_NormalAttack::CMonster_NormalAttack()
{
	m_ObjId = OBJ::OBJ_MONSTER_ATTACK;
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CMonster_NormalAttack::~CMonster_NormalAttack()
{
	Release_GameObject();
}

HRESULT CMonster_NormalAttack::Ready_GameObject()
{



	//////
	m_tFrame = { 0,5 };

	m_fAttack = CGameObject_Manager::Get_Instance()->Get_Player()->GetAttack() * 2.f;
	return S_OK;
}

int CMonster_NormalAttack::Update_GameObject()
{
	if (m_HP <= 0)
	{
		return OBJ_DEAD;
	}
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * CTime_Manager::Get_Instance()->Get_DeltaTime() * 3.f;
	if (m_tFrame.fFrameStart >= m_tFrame.fFrameEnd)
	{
		return OBJ_DEAD;
	}

	m_tInfo.vPos.x = CGameObject_Manager::Get_Instance()->Get_Player()->GetInfo()->vPos.x;
	m_tInfo.vPos.y = CGameObject_Manager::Get_Instance()->Get_Player()->GetInfo()->vPos.y;
	m_tInfo.vSize = CGameObject_Manager::Get_Instance()->Get_Player()->GetInfo()->vSize;
	//////
	m_tInfo.vDir = CGameObject_Manager::Get_Instance()->Get_Player()->GetInfo()->vDir;
	m_tInfo.vLook = CGameObject_Manager::Get_Instance()->Get_Player()->GetInfo()->vLook;
	m_iMirror = *CGameObject_Manager::Get_Instance()->Get_Player()->GetMirror();
	return OBJ_NOEVENT;
}

void CMonster_NormalAttack::LateUpdate_GameObject()
{
}

void CMonster_NormalAttack::Render_GameObject()
{

	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"ATTACK1_UP_RANGE", 0);
	if (nullptr == pTexInfo)
		return;

	m_tInfo.vRealSize = { float(pTexInfo->tImageInfo.Width/2),  float(pTexInfo->tImageInfo.Height) / 2, 0.f };

	_vec3 vCenter = { _float(pTexInfo->tImageInfo.Width >> 1), _float(pTexInfo->tImageInfo.Height >> 1) , 0.f };
	_matrix matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, m_iMirror * m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + CScroll_Manager::Get_Scroll(CScroll_Manager::X) + 100 * -m_iMirror, m_tInfo.vPos.y + CScroll_Manager::Get_Scroll(CScroll_Manager::Y), 0.f);
	matWorld = matScale * matTrans;
	if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_F1))
	{
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &vCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CMonster_NormalAttack::Release_GameObject()
{
}

void CMonster_NormalAttack::OnCollision(CGameObject* _TargetObj)
{
	switch (_TargetObj->GetObjId()) {
	case OBJ::OBJ_PLAYER:
	{
		CPlayer* tempCollision = dynamic_cast<CPlayer*>(_TargetObj);

		if (tempCollision)
		{
			m_HP -= 1;
		}
	}
	}
}

CGameObject* CMonster_NormalAttack::Create(LPVOID* pArg)
{
	CGameObject* pInstnace = new CMonster_NormalAttack;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	return pInstnace;
}

CGameObject * CMonster_NormalAttack::Create(float _Att)
{
	CGameObject* pInstnace = new CMonster_NormalAttack;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	pInstnace->SetAttack(_Att);
	return pInstnace;
}
