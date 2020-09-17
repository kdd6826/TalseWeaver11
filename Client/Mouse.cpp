#include "stdafx.h"
#include "Mouse.h"
#include "Monster.h"
#include "KeyManager.h"
#include "StatusBar.h"
#include "EquipBar.h"
#include "InvenBar.h"
#include "Portal.h"
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
	if (m_szFrameKey != L"Normal")
	{
		m_szFrameKey = L"Normal";
		m_tFrame = { 0,12 };
	}
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);
	D3DXVECTOR3 vMouse = { float(pt.x) - CScroll_Manager::Get_Scroll(CScroll_Manager::X), float(pt.y) - CScroll_Manager::Get_Scroll(CScroll_Manager::Y), 0.f };
	m_tInfo.vPos = vMouse;
	MoveFrame();
	//if (CKey_Manager::Get_Instance()->Key_DOWN(KEY_F2))
	//{
	//	m_isMagic = true;
	//}
	if (m_isMagic)
	{
		m_szFrameKey = L"Magic";
		if (CKey_Manager::Get_Instance()->Key_DOWN(KEY_LBUTTON))
		{
			m_isMagic = false;
		}
	}
	else
	{
		m_szFrameKey = L"Normal";
	}
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
				if (m_szFrameKey != L"Battle")
				{
					m_szFrameKey = L"Battle";
					m_tFrame = { 0,7 };
				}
				
			}
			break;
		}
		case OBJ::OBJ_BUTTON:
		{
			CEquipBar* tempCollision = dynamic_cast<CEquipBar*>(_TargetObj);
			if (tempCollision)
			{
				m_szFrameKey = L"Battle";
			}
			break;
			CStatusBar* temp2Collision = dynamic_cast<CStatusBar*>(_TargetObj);
			if (temp2Collision)
			{
				m_szFrameKey = L"Battle";
			}
			break;
		}
		case OBJ::OBJ_PORTAL:
		{
			CPortal* tempCollision = dynamic_cast<CPortal*>(_TargetObj);
			if (tempCollision)
			{
				if (m_szFrameKey != L"Gate")
				{
					m_szFrameKey = L"Gate";
					m_tFrame = { 0,3 };
				}

			}
			break;
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
