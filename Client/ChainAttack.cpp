#include "stdafx.h"
#include "ChainAttack.h"
#include "Monster.h"
#include "KeyManager.h"
CChainAttack::CChainAttack()
{
	m_ObjId = OBJ::OBJ_PLAYER_AD_ATTACK;
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CChainAttack::~CChainAttack()
{
	Release_GameObject();
}

HRESULT CChainAttack::Ready_GameObject()
{
	m_tInfo.vPos = { 1100.f, 600.f, 0.f };

	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	m_tInfo.vRealSize = { 60.f,90.f,0.f };
	//////
	m_tInfo.vDir = { 1.f,1.f,0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };



	//////
	m_tFrame = { 0,11 };
	srand(unsigned(time(nullptr)));
	int iRand = rand() % 100;
	if (iRand < CGameObject_Manager::Get_Instance()->Get_Player()->GetCritical())
	{
		isCritical = true;
	}

	if (isCritical)
	{
		m_fAttack = CGameObject_Manager::Get_Instance()->Get_Player()->GetAttack()*3 * CGameObject_Manager::Get_Instance()->Get_Player()->GetCriticalDamage();
	}
	if (!isCritical)
	{
		m_fAttack = CGameObject_Manager::Get_Instance()->Get_Player()->GetAttack()*3;
	}
	if (m_fAttack > 9999)
	{
		m_fAttack = 9999;
	}
	return S_OK;
}

int CChainAttack::Update_GameObject()
{
	MoveFrame(2.f);

	if (m_tFrame.fFrameStart >= m_tFrame.fFrameEnd - 1)
	{
		return OBJ_DEAD;
	}






	return OBJ_NOEVENT;
}

void CChainAttack::LateUpdate_GameObject()
{
}

void CChainAttack::Render_GameObject()
{

	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Effect", m_tInfo.chName, DWORD(m_tFrame.fFrameStart));
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

void CChainAttack::Release_GameObject()
{
}

void CChainAttack::OnCollision(CGameObject* _TargetObj)
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

void CChainAttack::MoveFrame(_float fSpeed)
{
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * CTime_Manager::Get_Instance()->Get_DeltaTime() * fSpeed;
	if (m_tFrame.fFrameStart >= m_tFrame.fFrameEnd)
	{
		m_tFrame.fFrameStart = 0.f;

	}
}

CGameObject* CChainAttack::Create(LPVOID* pArg)
{
	CGameObject* pInstnace = new CChainAttack;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	return pInstnace;
}

CGameObject* CChainAttack::Create(_vec3 vpos, WCHAR* _name)
{
	CGameObject* pInstnace = new CChainAttack;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	pInstnace->SetPos(vpos);
	pInstnace->SetFirstPos(vpos);
	pInstnace->SetName(_name);
	return pInstnace;
}
