#include "stdafx.h"
#include "NormalAttack.h"
#include "Monster.h"
#include "KeyManager.h"
CNormalAttack::CNormalAttack()
{
	m_ObjId = OBJ::OBJ_PLAYER_AD_ATTACK;
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CNormalAttack::~CNormalAttack()
{
	Release_GameObject();
}

HRESULT CNormalAttack::Ready_GameObject()
{
	
	
	
	//////
	m_tFrame = { 0,5 };
	srand(unsigned(time(nullptr)));
	int iRand = rand()%10;
	if (iRand < 5)
	{
		isCritical = true;
	}
	
	if (isCritical)
	{
		m_fAttack = CGameObject_Manager::Get_Instance()->Get_Player()->GetAttack()*CGameObject_Manager::Get_Instance()->Get_Player()->GetCriticalDamage();
	}
	if (!isCritical)
	{
		m_fAttack = CGameObject_Manager::Get_Instance()->Get_Player()->GetAttack();
	}
	if (m_fAttack > 9999)
	{
		m_fAttack = 9999;
	}
	return S_OK;
}

int CNormalAttack::Update_GameObject()
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

	m_tInfo.vPos.x = CGameObject_Manager::Get_Instance()->Get_Player()->GetInfo()->vPos.x-m_iMirror*30;
	m_tInfo.vPos.y = CGameObject_Manager::Get_Instance()->Get_Player()->GetInfo()->vPos.y-100;
	m_tInfo.vSize = CGameObject_Manager::Get_Instance()->Get_Player()->GetInfo()->vSize;
	//////
	m_tInfo.vDir = CGameObject_Manager::Get_Instance()->Get_Player()->GetInfo()->vDir;
	m_tInfo.vLook = CGameObject_Manager::Get_Instance()->Get_Player()->GetInfo()->vLook;
	m_iMirror = *CGameObject_Manager::Get_Instance()->Get_Player()->GetMirror();
	return OBJ_NOEVENT;
}

void CNormalAttack::LateUpdate_GameObject()
{
}

void CNormalAttack::Render_GameObject()
{

		pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"ATTACK1_UP_RANGE", 0);
		if (nullptr == pTexInfo)
			return;

		m_tInfo.vRealSize = { float(pTexInfo->tImageInfo.Width * 1.3),  float(pTexInfo->tImageInfo.Height)/2, 0.f };

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

void CNormalAttack::Release_GameObject()
{
}

void CNormalAttack::OnCollision(CGameObject* _TargetObj)
{
	switch (_TargetObj->GetObjId()) {
	case OBJ::OBJ_MONSTER:
	{
		CMonster* tempCollision = dynamic_cast<CMonster*>(_TargetObj);

		if (tempCollision)
		{
			m_HP -= 1;
		}
	}
	}
}

CGameObject* CNormalAttack::Create(LPVOID* pArg)
{
	CGameObject* pInstnace = new CNormalAttack;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	return pInstnace;
}
