#include "stdafx.h"
#include "Player.h"
#include "KeyManager.h"
#include "AStar.h"
#include "Monster.h"
#include "Scene_Manager.h"
#include "NormalAttack.h"
#include "Damage.h"
#include "Monster_NormalAttack.h"
CPlayer::CPlayer()
{
	m_ObjId = OBJ::OBJ_PLAYER;
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}


CPlayer::~CPlayer()
{
	Release_GameObject();
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
	{
		isMoving = false;
		m_tFrame = { 0,9 };
	}

	CScroll_Manager::Set_Scroll(-m_tInfo.vDir * 300.f * CTime_Manager::Get_Instance()->Get_DeltaTime());
}

void CPlayer::MoveFrame(_float fSpeed)
{
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * CTime_Manager::Get_Instance()->Get_DeltaTime() * fSpeed;
	if (m_tFrame.fFrameStart >= m_tFrame.fFrameEnd)
		m_tFrame.fFrameStart = 0.f;
}

void CPlayer::StopAStar()
{
	list<TILE*>& BestList = CAStar::Get_Instance()->Get_BestList();
	if (!BestList.empty())
		BestList.pop_front();

	return;
}


HRESULT CPlayer::Ready_GameObject()
{

	m_tInfo.vPos = { 800.f, 400.f, 0.f };
	CScroll_Manager::Set_Scroll({ -m_tInfo.vPos.x / 2,-m_tInfo.vPos.y / 2,0.f });
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	m_tInfo.vRealSize = { 60.f,90.f,0.f };
	//////
	m_tInfo.vDir = { 1.f,1.f,0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	///////
	m_szFrameKey = L"STAND_LEFT";
	m_tFrame = { 0.f, 10.f };
	m_fSpeed = 2.f;
	m_fAngle = 0.f;
	
	m_MaxHP = 1000;
	m_MaxMP = 1000;
	m_MaxSP = 1000;

	m_HP = m_MaxHP;
	m_MP = m_MaxMP;
	m_SP = m_MaxSP;

	

	m_fAttack = 10.f;
	m_fDef = 1.f;
	m_fCritical = 0.1f;
	m_fCriticalDamage = 2.f;
	
	return S_OK;
}

int CPlayer::Update_GameObject()
{

	//if (m_HP <= 0)
	//{
	//	return OBJ_DEAD;
	//}

	CGameObject::Update_Rect_Object();

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
	{
		m_StateKey = L"STAND_";
	}


	//공격,  마법
	if (!isMoving&&!isAttack&&!isEvolution)
	{
		if (CGameObject_Manager::Get_Instance()->Get_Mouse()->GetState() == L"Battle")
		{


			if (CKey_Manager::Get_Instance()->Key_DOWN(KEY_LBUTTON))
			{

				POINT pt = {};
				GetCursorPos(&pt);
				ScreenToClient(g_hWND, &pt);
				D3DXVECTOR3 vMouse = { float(pt.x) - CScroll_Manager::Get_Scroll(CScroll_Manager::X), float(pt.y) - CScroll_Manager::Get_Scroll(CScroll_Manager::Y), 0.f };
				m_tInfo.vDir = vMouse - m_tInfo.vPos;
				float fDist = D3DXVec3Length(&m_tInfo.vDir);
				D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
				float fRadian = D3DXVec3Dot(&m_tInfo.vLook, &m_tInfo.vDir);
				m_fAngle = acosf(fRadian);
				if (m_tInfo.vPos.y < vMouse.y)
					m_fAngle *= -1.f;
				if (m_tInfo.vPos.x < vMouse.x)
					m_iMirror = -1;
				else
					m_iMirror = 1;
				isAttack = true;
				m_fAttackTime = 0;
				m_tFrame.fFrameStart = 0;
				m_tFrame.fFrameEnd = 13;
				
			}
			if (CKey_Manager::Get_Instance()->Key_DOWN(KEY_S))
			{
				isEvolution = true;
				m_fAttackTime = 0;
				m_tFrame.fFrameStart = 0;
				m_tFrame.fFrameEnd = 10;
			}
		}
	}
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
	if (-3.25f <= m_fAngle && m_fAngle < -2.7f)
	{
		m_DirectionKey = L"LEFT";
	}
	if (-2.7f <= m_fAngle && m_fAngle < -2.f)
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
	if (isAttack)
	{
		if (m_fAttackTime > 0.5 && m_fAttackCount==0)
		{
			CGameObject_Manager::Get_Instance()->Add_GameObject(OBJ::OBJ_ATTACK, CNormalAttack::Create());
			++m_fAttackCount;
		}
		if (m_fAttackTime > 1.5 && m_fAttackCount == 1)
		{
			CGameObject_Manager::Get_Instance()->Add_GameObject(OBJ::OBJ_ATTACK, CNormalAttack::Create());
			++m_fAttackCount;
		}
		if (m_fAttackTime < 1.9)
		{
			
			m_fAttackTime += 1.9* CTime_Manager::Get_Instance()->Get_DeltaTime() * m_fSpeed;
			m_StateKey = L"ATTACK1_";

		}
		else
		{
			
			isAttack = false;
			m_StateKey = L"STAND_";
			m_tFrame.fFrameEnd = 10;
			m_tFrame.fFrameStart = 0;
			m_fAttackCount = 0;
		}
	}
	if (isEvolution)
	{

		if (m_fAttackTime < 2.1)
		{
			m_fSpeed = 2.f;
			m_fAttackTime += 0.1;
			m_StateKey = L"EVOLUTION";
			m_DirectionKey = L"";
		}
		else
		{
			m_fSpeed = 8.f;
			isEvolution = false;
			m_StateKey = L"STAND_";
			isEvoluting = true;
				
		}
	}

	if (!isAttack)
	{
		if (CGameObject_Manager::Get_Instance()->Get_Mouse()->GetState() == L"Normal")
		{
			if (CKey_Manager::Get_Instance()->Key_DOWN(KEY_LBUTTON))
			{

				POINT pt = {};
				GetCursorPos(&pt);
				ScreenToClient(g_hWND, &pt);
				pt.x -= CScroll_Manager::Get_Scroll(CScroll_Manager::X);
				pt.y -= CScroll_Manager::Get_Scroll(CScroll_Manager::Y);
				_vec3 vMouse = { float(pt.x), float(pt.y), 0.f };
				m_tInfo.vPos;
				CAStar::Get_Instance()->Start_AStar(m_tInfo.vPos, vMouse);
				isMoving = true;

			}
		}


	}




	m_szFrameKey = m_StateKey + m_DirectionKey;
	return OBJ_NOEVENT;
}

void CPlayer::LateUpdate_GameObject()
{
	if (isMoving)
	{
		m_fSpeed = 2.f;
		RouteTrack();
		m_tFrame.fFrameEnd =7;
	}
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

CGameObject * CPlayer::Create(_vec3 vpos)
{
	CGameObject* pInstnace = new CPlayer;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	pInstnace->SetPos(vpos);
	return pInstnace;
}

void CPlayer::OnCollision(CGameObject* _TargetObj)
{
	switch (_TargetObj->GetObjId()) {
	case OBJ::OBJ_MONSTER:
	{
		CMonster* tempCollision = dynamic_cast<CMonster*>(_TargetObj);

		if (tempCollision)
		{

			/*m_tInfo.vPos.x -= 100;*/

		}
		break;
	}
	case OBJ::OBJ_MONSTER_ATTACK:
	{
		CMonster_NormalAttack* tempCollision = dynamic_cast<CMonster_NormalAttack*>(_TargetObj);
		if (tempCollision)
		{
			m_HP -= _TargetObj->GetAttack();
			CGameObject_Manager::Get_Instance()->Add_GameObject(OBJ::OBJ_DAMAGE, CDamage::Create({ m_tInfo.vPos.x - pTexInfo->tImageInfo.Width / 5,m_tInfo.vPos.y - pTexInfo->tImageInfo.Height / 3,0.f }, _TargetObj->GetAttack()));

		}
		break;
	}
	default:
		break;
	}
}
