#include "stdafx.h"
#include "Mouse.h"
#include "Monster.h"
CMouse::CMouse()
{
	m_ObjId = OBJ::OBJ_MOUSE;
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CMouse::~CMouse()
{
	Release_GameObject();
}

void CMouse::MoveFrame(_float fSpeed)
{
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * CTime_Manager::Get_Instance()->Get_DeltaTime() * fSpeed;
	if (m_tFrame.fFrameStart >= m_tFrame.fFrameEnd)
		m_tFrame.fFrameStart = 0.f;
}

void CMouse::Animaition_Change()
{
}

HRESULT CMouse::Ready_GameObject()
{
	m_tInfo.vPos = { 800.f, 400.f, 0.f };
	
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	m_tInfo.vRealSize = { 60.f,90.f,0.f };
	//////
	m_tInfo.vDir = { 1.f,1.f,0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	///////
	m_szFrameKey = L"Normal";
	m_tFrame = { 0.f, 5.f };
	m_fSpeed = 2.f;
	m_fAngle = 0.f;

	return S_OK;
}

int CMouse::Update_GameObject()
{
	m_szFrameKey = L"Normal";
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);
	D3DXVECTOR3 vMouse = { float(pt.x) - CScroll_Manager::Get_Scroll(CScroll_Manager::X), float(pt.y) - CScroll_Manager::Get_Scroll(CScroll_Manager::Y), 0.f };
	m_tInfo.vPos = vMouse;
	MoveFrame();
	
	return 0;
}

void CMouse::LateUpdate_GameObject()
{
}

void CMouse::Render_GameObject()
{
	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Mouse", m_szFrameKey, DWORD(m_tFrame.fFrameStart));
	if (nullptr == pTexInfo)
		return;
	_vec3 vCenter = { _float(pTexInfo->tImageInfo.Width >> 1), _float(pTexInfo->tImageInfo.Height >> 1) , 0.f };
	_matrix matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + CScroll_Manager::Get_Scroll(CScroll_Manager::X), m_tInfo.vPos.y + CScroll_Manager::Get_Scroll(CScroll_Manager::Y), 0.f);
	matWorld = matScale * matTrans;
	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &vCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CMouse::Release_GameObject()
{
}

void CMouse::OnCollision(CGameObject* _TargetObj)
{
		switch (_TargetObj->GetObjId()) {
		case OBJ::OBJ_MONSTER:
		{
			CMonster* tempCollision = dynamic_cast<CMonster*>(_TargetObj);
			if (tempCollision)
			{

				m_szFrameKey = L"Battle";

			}

		}
		}
	
}

CGameObject* CMouse::Create(LPVOID* pArg)
{
	
		CGameObject* pInstnace = new CMouse;
		if (FAILED(pInstnace->Ready_GameObject()))
			return nullptr;
		return pInstnace;
}
