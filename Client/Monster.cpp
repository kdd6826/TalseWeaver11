#include "stdafx.h"
#include "Monster.h"
#include "BlueWolf.h"
#include "Player.h"
#include "NormalAttack.h"
#include "Damage.h"
#include "Critical.h"
#include "ThunderBolt.h"
#include "ChainAttack.h"
#include "Summon.h"
#include "MultiAttack.h"
CMonster::CMonster()
{
	m_ObjId = OBJ::OBJ_MONSTER;
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CMonster::CMonster(float _forceX, float _forceY)
{
	m_ObjId = OBJ::OBJ_MONSTER;
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CMonster::~CMonster()
{
	Release_GameObject();
}

HRESULT CMonster::Ready_GameObject()
{
	srand(unsigned(time(nullptr)));
	
	return E_NOTIMPL;
}

int CMonster::Update_GameObject()
{

	CGameObject::Update_Rect_Object();

	return OBJ_NOEVENT;
}

void CMonster::LateUpdate_GameObject()
{
}

void CMonster::Render_GameObject()
{
}

void CMonster::Release_GameObject()
{
}

CGameObject* CMonster::Create(LPVOID* pArg)
{
	CGameObject* pInstnace = new CMonster;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	return pInstnace;
}

void CMonster::OnCollision(CGameObject* _TargetObj)
{

	switch (_TargetObj->GetObjId()) {
	case OBJ::OBJ_PLAYER: {
		CPlayer* tempSwordAttack = dynamic_cast<CPlayer*>(_TargetObj);
		if (tempSwordAttack ) {
			/*m_HP -= _TargetObj->GetAttack();*/
			
			if (m_HP <= 0) {

			}
		}
		break;
	}
	case OBJ::OBJ_PLAYER_AD_ATTACK: {
		CNormalAttack* tempSwordAttack = dynamic_cast<CNormalAttack*>(_TargetObj);
		if (tempSwordAttack) {
			m_HP -= _TargetObj->GetAttack();
			if (_TargetObj->GetisCritical())
			{
				CGameObject_Manager::Get_Instance()->Add_GameObject(OBJ::OBJ_EFFECT, CCritical::Create({ m_tInfo.vPos.x - pTexInfo->tImageInfo.Width / 2+100,m_tInfo.vPos.y - pTexInfo->tImageInfo.Height / 2,0.f }));
			}
			CGameObject_Manager::Get_Instance()->Add_GameObject(OBJ::OBJ_DAMAGE, CDamage::Create({ m_tInfo.vPos.x - pTexInfo->tImageInfo.Width / 2,m_tInfo.vPos.y - pTexInfo->tImageInfo.Height/4,0.f },_TargetObj->GetAttack(),1));

			if (m_HP <= 0) {

			}
		}

		CChainAttack* tempChainAttack = dynamic_cast<CChainAttack*>(_TargetObj);
		if (tempChainAttack) {
			m_iChainTimer++;
			if (m_iChainTimer == 20)
			{
				int iRand = rand() % 50;
				int iRandX = 0;
				int iRandY = 0;
				if (iRand % 2 == 0)
				{
					iRandX = iRand;
					iRandY = iRand;
				}
				if (iRand % 2 == 1)
				{
					iRandX = -iRand;
					iRandY = -iRand;
				}
				m_tInfo.vPos.x = CGameObject_Manager::Get_Instance()->Get_Player()->GetPos().x + iRandX;
				m_tInfo.vPos.y = CGameObject_Manager::Get_Instance()->Get_Player()->GetPos().y + iRandY;
				m_isSearch = true;
				m_iChainTimer = 0;
			}
			if (m_HP <= 0) {

			}
		}

		CMultiAttack* tempMultiAttack = dynamic_cast<CMultiAttack*>(_TargetObj);
		if (tempMultiAttack) {
			m_iMultiTimer++;

			if (m_iMultiTimer == 5)
			{
				if (_TargetObj->GetisCritical())
				{
					CGameObject_Manager::Get_Instance()->Add_GameObject(OBJ::OBJ_EFFECT, CCritical::Create({ m_tInfo.vPos.x - pTexInfo->tImageInfo.Width / 2 + 100,m_tInfo.vPos.y - pTexInfo->tImageInfo.Height / 2,0.f }));
				}
				m_HP -= _TargetObj->GetAttack();
				CGameObject_Manager::Get_Instance()->Add_GameObject(OBJ::OBJ_DAMAGE, CDamage::Create({ m_tInfo.vPos.x - pTexInfo->tImageInfo.Width / 2,m_tInfo.vPos.y - pTexInfo->tImageInfo.Height/4,0.f }, _TargetObj->GetAttack(),1));
				m_isSearch = true;
				m_iMultiTimer = 0;
			}
			if (m_HP <= 0) {

			}
		}
		break;
	}
	case OBJ::OBJ_PLAYER_AP_ATTACK: {
		CThunderBolt* tempThunderBolt = dynamic_cast<CThunderBolt*>(_TargetObj);
		if (tempThunderBolt) {
			m_iThunderTimer++;
			if (m_iThunderTimer == 3)
			{
				if (_TargetObj->GetisCritical())
				{
					CGameObject_Manager::Get_Instance()->Add_GameObject(OBJ::OBJ_EFFECT, CCritical::Create({ m_tInfo.vPos.x - pTexInfo->tImageInfo.Width / 2 + 100,m_tInfo.vPos.y - pTexInfo->tImageInfo.Height / 2,0.f }));
				}
				m_HP -= _TargetObj->GetAttack();
				CGameObject_Manager::Get_Instance()->Add_GameObject(OBJ::OBJ_DAMAGE, CDamage::Create({ m_tInfo.vPos.x - pTexInfo->tImageInfo.Width / 2,m_tInfo.vPos.y - pTexInfo->tImageInfo.Height/4,0.f }, _TargetObj->GetAttack(), 2));
				m_isSearch = true;
				m_iThunderTimer = 0;
			}
			if (m_HP <= 0) {

			}
		}

		break;
	}
	//case OBJ::OBJ_PLAYER: {
	//	CPlayer* tempPlayer = dynamic_cast<CPlayer*>(_TargetObj);
	//	RECT rc = {};
	//	if (IntersectRect(&rc, tempPlayer->GetRect(), GetRect())) {
	//		m_tInfo.vPos.x += (rc.right - rc.left);
	//		m_tInfo.vPos.y += (rc.bottom - rc.top);
	//	}
	//	break;
	//}
	default:
		break;
	}



}
bool CMonster::Search_Player(float distRange)
{
	if (!CGameObject_Manager::Get_Instance()->Get_Player())
		return false;
	m_tInfo.vPos.x < CGameObject_Manager::Get_Instance()->Get_Player()->GetPos().x ? forceX = 1.f : forceX = -1.f;

	float distanceX = fabsf(CGameObject_Manager::Get_Instance()->Get_Player()->GetPos().x - m_tInfo.vPos.x);
	float distanceY = fabsf(CGameObject_Manager::Get_Instance()->Get_Player()->GetPos().y - m_tInfo.vPos.y);
	if (distanceX < distRange&&distanceY<distRange)
		return true;
	return false;
}