#include "stdafx.h"
#include "MultiAttack.h"
#include "Monster.h"
#include "KeyManager.h"
CMultiAttack::CMultiAttack()
{
	m_ObjId = OBJ::OBJ_PLAYER_AD_ATTACK;
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CMultiAttack::~CMultiAttack()
{
	Release_GameObject();
}

HRESULT CMultiAttack::Ready_GameObject()
{
	m_tInfo.vPos = { 1100.f, 600.f, 0.f };

	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	m_tInfo.vRealSize = { 60.f,90.f,0.f };
	//////
	m_tInfo.vDir = { 1.f,1.f,0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };

	m_tInfo.vSize.x += 20 * CTime_Manager::Get_Instance()->Get_DeltaTime();
	m_tInfo.vSize.y += 20 * CTime_Manager::Get_Instance()->Get_DeltaTime();
	//////
	m_tFrame = { 0,40 };
	srand(unsigned(time(nullptr)));
	int iRand = rand() % 100;
	if (iRand < CGameObject_Manager::Get_Instance()->Get_Player()->GetCritical())
	{
		isCritical = true;
	}

	if (isCritical)
	{
		m_fAttack = CGameObject_Manager::Get_Instance()->Get_Player()->GetAttack() * 10 * CGameObject_Manager::Get_Instance()->Get_Player()->GetCriticalDamage();
	}
	if (!isCritical)
	{
		m_fAttack = CGameObject_Manager::Get_Instance()->Get_Player()->GetAttack() * 10;
	}
	if (m_fAttack > 9999)
	{
		m_fAttack = 9999;
	}
	return S_OK;
}

int CMultiAttack::Update_GameObject()
{
	MoveFrame(1.f);

	if (m_tFrame.fFrameStart >= m_tFrame.fFrameEnd - 1)
	{
		return OBJ_DEAD;
	}
	m_fAngle = 10;





	return OBJ_NOEVENT;
}

void CMultiAttack::LateUpdate_GameObject()
{
}

void CMultiAttack::Render_GameObject()
{

	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Effect", L"MultiAttack", DWORD(m_tFrame.fFrameStart));
	if (nullptr == pTexInfo)
		return;

	m_tInfo.vRealSize = { float(pTexInfo->tImageInfo.Width),  float(pTexInfo->tImageInfo.Height), 0.f };

	_vec3 vCenter = { _float(pTexInfo->tImageInfo.Width >> 1), _float(pTexInfo->tImageInfo.Height >> 1) , 0.f };
	_matrix matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, m_iMirror * m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + CScroll_Manager::Get_Scroll(CScroll_Manager::X), m_tInfo.vPos.y + CScroll_Manager::Get_Scroll(CScroll_Manager::Y), 0.f);
	matWorld = matScale * matTrans;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &vCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

}

void CMultiAttack::Release_GameObject()
{
}

void CMultiAttack::OnCollision(CGameObject* _TargetObj)
{
	switch (_TargetObj->GetObjId()) {
	case OBJ::OBJ_MONSTER:
	{
		CMonster* tempCollision = dynamic_cast<CMonster*>(_TargetObj);

		if (tempCollision)
		{
			/*m_HP -= 1;*/
		}
	}
	}
}

void CMultiAttack::MoveFrame(_float fSpeed)
{
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * CTime_Manager::Get_Instance()->Get_DeltaTime() * fSpeed;
	if (m_tFrame.fFrameStart >= m_tFrame.fFrameEnd)
	{
		m_tFrame.fFrameStart = 0.f;

	}
}

CGameObject* CMultiAttack::Create(LPVOID* pArg)
{
	CGameObject* pInstnace = new CMultiAttack;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	return pInstnace;
}

CGameObject * CMultiAttack::Create(_vec3 vpos)
{
	CGameObject* pInstnace = new CMultiAttack;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	pInstnace->SetPos(vpos);
	pInstnace->SetFirstPos(vpos);
	return pInstnace;
}
