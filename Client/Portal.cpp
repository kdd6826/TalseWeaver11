#include "stdafx.h"
#include "Portal.h"
#include "Monster.h"
#include "KeyManager.h"
CPortal::CPortal()
{
	m_ObjId = OBJ::OBJ_PORTAL;
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CPortal::~CPortal()
{
	Release_GameObject();
}

HRESULT CPortal::Ready_GameObject()
{

	

	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	//////
	m_tInfo.vDir = { 1.f,1.f,0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	///////
	m_szFrameKey = L"Stand_LDown";
	m_tFrame = { 0.f, 23.f };
	m_fSpeed = 2.f;
	m_fAngle = 0.f;
	m_fAttack = 5.f;
		
	return S_OK;
}

int CPortal::Update_GameObject()
{
	MoveFrame(2.f);

	if (m_HP <= 0)
	{
		return OBJ_DEAD;
	}
	
	if (m_tFrame.fFrameStart >= m_tFrame.fFrameEnd)
	{
		return OBJ_DEAD;
	}


	return OBJ_NOEVENT;
}

void CPortal::LateUpdate_GameObject()
{
}

void CPortal::Render_GameObject()
{

	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"WARPGATE", L"WarpGate", DWORD(m_tFrame.fFrameStart));
	if (nullptr == pTexInfo)
		return;

	m_tInfo.vRealSize = { float(pTexInfo->tImageInfo.Width * 1.3),  float(pTexInfo->tImageInfo.Height) / 2, 0.f };

	_vec3 vCenter = { _float(pTexInfo->tImageInfo.Width >> 1), _float(pTexInfo->tImageInfo.Height >> 1) , 0.f };
	_matrix matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, m_iMirror * m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + CScroll_Manager::Get_Scroll(CScroll_Manager::X) + 100 * -m_iMirror, m_tInfo.vPos.y + CScroll_Manager::Get_Scroll(CScroll_Manager::Y), 0.f);
	matWorld = matScale * matTrans;
	
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &vCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	
}

void CPortal::Release_GameObject()
{
}

void CPortal::OnCollision(CGameObject* _TargetObj)
{
	switch (_TargetObj->GetObjId()) {
	case OBJ::OBJ_MONSTER:
	{
		CMonster* tempCollision = dynamic_cast<CMonster*>(_TargetObj);

		if (tempCollision)
		{

		}
	}
	}
}

void CPortal::MoveFrame(_float fSpeed)
{
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * CTime_Manager::Get_Instance()->Get_DeltaTime() * fSpeed;
	if (m_tFrame.fFrameStart >= m_tFrame.fFrameEnd)
	{
		m_tFrame.fFrameStart = 0.f;

	}
}

CGameObject* CPortal::Create(LPVOID* pArg)
{
	CGameObject* pInstnace = new CPortal;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	return pInstnace;
}

CGameObject* CPortal::Create(_vec3 vpos)
{
	CGameObject* pInstnace = new CPortal;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	pInstnace->SetPos(vpos);
	return pInstnace;
}
