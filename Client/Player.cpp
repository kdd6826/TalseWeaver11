#include "stdafx.h"
#include "Player.h"
#include "KeyManager.h"
#include "AStar.h"
#include "Scene_Manager.h"
CPlayer::CPlayer()
{
	m_ObjId = OBJ::OBJ_PLAYER;
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}


CPlayer::~CPlayer()
{
}

void CPlayer::RouteTrack()
{

	list<TILE*>& BestList = CAStar::Get_Instance()->Get_BestList();
	if (BestList.empty())
		return;

	m_tInfo.vDir = BestList.front()->vPos - m_tInfo.vPos;
	float fDist = D3DXVec3Length(&m_tInfo.vDir);
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	//
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);
	D3DXVECTOR3 vMouse = { float(pt.x) - CScroll_Manager::Get_Scroll(CScroll_Manager::X), float(pt.y) - CScroll_Manager::Get_Scroll(CScroll_Manager::Y), 0.f };
	float fRadian = D3DXVec3Dot(&m_tInfo.vLook, &m_tInfo.vDir);
	m_fAngle = acosf(fRadian);
	if (m_tInfo.vPos.y < BestList.front()->vPos.y)
		m_fAngle *= -1.f;
	if (m_tInfo.vPos.x < BestList.front()->vPos.x)
		m_iMirror = -1;
	else
		m_iMirror = 1;
	isMovingCount = true;

	//
	if (10.f > fDist)
	{
		BestList.pop_front();
	}
	m_tInfo.vPos += m_tInfo.vDir * 300.f * CTime_Manager::Get_Instance()->Get_DeltaTime();

	//방향
	if (-0.5f <= m_fAngle && m_fAngle < 0.5f)
	{
		m_DirectionKey = L"LEFT";
	}
	if (0.5f <= m_fAngle && m_fAngle < 1.25f)
	{
		m_DirectionKey = L"LUP";
	}
	if (1.25f <= m_fAngle && m_fAngle < 2.25f)
	{
		m_DirectionKey = L"UP";
	}
	if (2.25f <= m_fAngle && m_fAngle < 3.f)
	{
		m_DirectionKey = L"LUP";
	}
	if (3.f <= m_fAngle && m_fAngle < 3.25f)
	{
		m_DirectionKey = L"LEFT";
	}
	if (-3.25f <= m_fAngle && m_fAngle < -2.5f)
	{
		m_DirectionKey = L"LEFT";
	}
	if (-2.5f <= m_fAngle && m_fAngle < -2.f)
	{
		m_DirectionKey = L"LDOWN";
	}
	if (-2.f <= m_fAngle && m_fAngle < -1.f)
	{
		m_DirectionKey = L"DOWN";
	}
	if (-1.f <= m_fAngle && m_fAngle < -0.5f)
	{
		m_DirectionKey = L"LDOWN";
	}

	if (BestList.empty())
		isMoving = false;

	CScroll_Manager::Set_Scroll(-m_tInfo.vDir * 300.f * CTime_Manager::Get_Instance()->Get_DeltaTime());
}

void CPlayer::MoveFrame(_float fSpeed)
{
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * CTime_Manager::Get_Instance()->Get_DeltaTime() * fSpeed;
	if (m_tFrame.fFrameStart >= m_tFrame.fFrameEnd)
		m_tFrame.fFrameStart = 0.f;
}

HRESULT CPlayer::Ready_GameObject()
{

	m_tInfo.vPos = { 800.f, 400.f, 0.f };
	CScroll_Manager::Set_Scroll({ -m_tInfo.vPos.x / 2,-m_tInfo.vPos.y / 2,0.f });
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	//////
	m_tInfo.vDir = { 1.f,1.f,0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	///////
	m_szFrameKey = L"STAND_LEFT";
	m_tFrame = { 0.f, 5.f };
	m_fSpeed = 2.f;
	m_fAngle = 0.f;
	
	
	return S_OK;
}

int CPlayer::Update_GameObject()
{

	if (CKey_Manager::Get_Instance()->Key_DOWN(KEY_F10))
	{
		CScene_Manager::Get_Instance()->Change_Scene(CScene_Manager::SCENE_TOWN1);
	}
	if (CKey_Manager::Get_Instance()->Key_DOWN(KEY_F9))
	{
		CScene_Manager::Get_Instance()->Change_Scene(CScene_Manager::SCENE_SHOP);
	}
	MoveFrame(m_fSpeed);




	if (isMoving)
	{
		m_StateKey = L"RUN_";
	}
	if (!isMoving)
		m_StateKey = L"STAND_";

	//방향
	if (-0.5f <= m_fAngle && m_fAngle < 0.5f)
	{
		m_DirectionKey = L"LEFT";
	}
	if (0.5f <= m_fAngle && m_fAngle < 1.25f)
	{
		m_DirectionKey = L"LUP";
	}
	if (1.25f <= m_fAngle && m_fAngle < 2.25f)
	{
		m_DirectionKey = L"UP";
	}
	if (2.25f <= m_fAngle && m_fAngle < 3.f)
	{
		m_DirectionKey = L"LUP";
	}
	if (3.f <= m_fAngle && m_fAngle < 3.25f)
	{
		m_DirectionKey = L"LEFT";
	}
	if (-3.25f <= m_fAngle && m_fAngle < -2.5f)
	{
		m_DirectionKey = L"LEFT";
	}
	if (-2.5f <= m_fAngle && m_fAngle < -2.f)
	{
		m_DirectionKey = L"LDOWN";
	}
	if (-2.f <= m_fAngle && m_fAngle < -1.f)
	{
		m_DirectionKey = L"DOWN";
	}
	if (-1.f <= m_fAngle && m_fAngle < -0.5f)
	{
		m_DirectionKey = L"LDOWN";
	}

	if (!isMoving&&!isAttack)
	{
		
		if (CKey_Manager::Get_Instance()->Key_DOWN(KEY_D))
		{
			isAttack = true;
			m_fAttackTime = 0;
			m_tFrame.fFrameStart = 0;
		}
	}
	if (isAttack)
	{

		if (m_fAttackTime < 2.1)
		{
			m_fSpeed = 10.f;
			m_fAttackTime += 0.1;
			m_StateKey = L"ATTACK1_";

		}
		else
		{
			m_fSpeed = 2.f;
			isAttack = false;
			m_StateKey = L"STAND_";
		}
	}

	if (!isAttack)
	{
		if (CKey_Manager::Get_Instance()->Key_DOWN(KEY_LBUTTON))
		{
			POINT pt = {};
			GetCursorPos(&pt);
			ScreenToClient(g_hWND, &pt);
			pt.x -= CScroll_Manager::Get_Scroll(CScroll_Manager::X);
			pt.y -= CScroll_Manager::Get_Scroll(CScroll_Manager::Y);
			_vec3 vMouse = { float(pt.x), float(pt.y), 0.f };
			CAStar::Get_Instance()->Start_AStar(m_tInfo.vPos, vMouse);
			isMoving = true;
		}
	}

	m_szFrameKey = m_StateKey + m_DirectionKey;
	return 0;
}

void CPlayer::LateUpdate_GameObject()
{
	if (isMoving)
		RouteTrack();

}

void CPlayer::Render_GameObject()
{

	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", m_szFrameKey, DWORD(m_tFrame.fFrameStart));

	if (nullptr == pTexInfo)
		return;
	_vec3 vCenter = { _float(pTexInfo->tImageInfo.Width >> 1), _float(pTexInfo->tImageInfo.Height >> 1) , 0.f };


	_matrix matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, m_iMirror * m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + CScroll_Manager::Get_Scroll(CScroll_Manager::X), m_tInfo.vPos.y + CScroll_Manager::Get_Scroll(CScroll_Manager::Y), 0.f);

	matWorld = matScale * matTrans;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &vCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


}

void CPlayer::Release_GameObject()
{
}

CGameObject* CPlayer::Create(LPVOID* pArg)
{
	CGameObject* pInstnace = new CPlayer;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	return pInstnace;
}
