#include "stdafx.h"
#include "BlueWolf.h"
#include "Monster_NormalAttack.h"
CBlueWolf::CBlueWolf()
{
	m_ObjId = OBJ::OBJ_MONSTER;
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CBlueWolf::~CBlueWolf()
{
	Release_GameObject();
}

HRESULT CBlueWolf::Ready_GameObject()
{
	
	m_tInfo.vPos = { 1100.f, 600.f, 0.f };

	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	m_tInfo.vRealSize = { 60.f,90.f,0.f };
	//////
	m_tInfo.vDir = { 1.f,1.f,0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	///////
	m_szFrameKey = L"Stand_LDown";
	m_tFrame = { 0.f, 5.f };
	m_fSpeed = 2.f;
	m_fAngle = 0.f;
	m_fAttack = 5.f;
	m_HP = 1000;
	return S_OK;
}

int CBlueWolf::Update_GameObject()
{
	CGameObject::Update_Rect_Object();
	
	
	
	if (m_HP <= 0)
	{

		m_Alpha -= 20;
		if(m_Alpha < 0)
		{return OBJ_DEAD; }
	
	}
	else
	{
		MoveFrame(2.f);

		if (Search_Player(200.f))
		{
			m_isSearch = true;
		}

		if (m_isSearch)
		{

			if (Search_Player(50.f))
			{

				isAttack = true;
				isMoving = false;

			}
			if (!Search_Player(50.f))
			{

				isMoving = true;
				isAttack = false;
			}

			if (isMoving)
			{
				if (m_StateKey != L"Walk_")
				{
					m_tFrame.fFrameStart = 0;
					m_tFrame.fFrameEnd = 5;
					m_Animation = true;
				}
				m_tInfo.vDir = CGameObject_Manager::Get_Instance()->Get_Player()->GetPos() - m_tInfo.vPos;
				D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
				m_tInfo.vPos += m_tInfo.vDir *100.f *CTime_Manager::Get_Instance()->Get_DeltaTime();

				m_StateKey = L"Walk_";


			}

			if (isAttack)
			{
				if (m_StateKey != L"Attack_")
				{
					m_tFrame.fFrameStart = 0;
					m_tFrame.fFrameEnd = 7;
				}

				if (m_tFrame.fFrameStart > 5 && m_fAttackCount == 0)
				{
					++m_fAttackCount;
					CGameObject_Manager::Get_Instance()->Add_GameObject(OBJ::OBJ_MONSTER_ATTACK, CMonster_NormalAttack::Create(m_fAttack));

				}
				if (m_tFrame.fFrameStart == 0)
				{
					m_fAttackCount = 0.f;
				}
				m_StateKey = L"Attack_";

			}


			if (m_tInfo.vPos.x > CGameObject_Manager::Get_Instance()->Get_Player()->GetInfo()->vPos.x)
				m_iMirror = 1.f;
			else
				m_iMirror = -1.f;

			if (m_tInfo.vPos.y > CGameObject_Manager::Get_Instance()->Get_Player()->GetInfo()->vPos.y)
				m_DirectionKey = L"LUp";
			else
				m_DirectionKey = L"LDown";
		}

		if (!m_isSearch)
		{

			m_StateKey = L"Walk_";
			m_DirectionKey = L"LDown";
			m_tInfo.vPos.x -= m_fSpeed*50.f*CTime_Manager::Get_Instance()->Get_DeltaTime();

		}
		m_szFrameKey = m_StateKey + m_DirectionKey;
		return OBJ_NOEVENT;
	}
}

void CBlueWolf::LateUpdate_GameObject()
{
	if (!m_isSearch)
	{
		if (FirstPos.x - 100.f > m_tInfo.vPos.x)
		{
			m_fSpeed = -2.f;
			m_iMirror = -1.f;

		}

		if (FirstPos.x + 100.f < m_tInfo.vPos.x)
		{
			m_fSpeed = 2.f;
			m_iMirror = 1.f;
		}
	}
}

void CBlueWolf::Render_GameObject()
{

	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"BlueWolf", m_szFrameKey, DWORD(m_tFrame.fFrameStart));

	if (nullptr == pTexInfo)
		return;
	_vec3 vCenter = { _float(pTexInfo->tImageInfo.Width >> 1), _float(pTexInfo->tImageInfo.Height >> 1) , 0.f };


	_matrix matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x*m_iMirror, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + CScroll_Manager::Get_Scroll(CScroll_Manager::X), m_tInfo.vPos.y + CScroll_Manager::Get_Scroll(CScroll_Manager::Y), 0.f);

	matWorld = matScale * matTrans;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &vCenter, nullptr, D3DCOLOR_ARGB(m_Alpha, 255, 255, 255));


}

void CBlueWolf::Release_GameObject()
{
}


void CBlueWolf::MoveFrame(_float fSpeed)
{
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * CTime_Manager::Get_Instance()->Get_DeltaTime() * fSpeed;
	if (m_tFrame.fFrameStart >= m_tFrame.fFrameEnd)
	{
		m_tFrame.fFrameStart = 0.f;

	}
}

CGameObject* CBlueWolf::Create(LPVOID* pArg)
{
	CGameObject* pInstnace = new CBlueWolf;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	return pInstnace;
}

CGameObject* CBlueWolf::Create(_vec3 vpos)
{
	CGameObject* pInstnace = new CBlueWolf;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	pInstnace->SetPos(vpos);
	pInstnace->SetFirstPos(vpos);
	return pInstnace;
}
