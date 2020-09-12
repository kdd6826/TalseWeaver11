#include "stdafx.h"
#include "Monster.h"
#include "BlueWolf.h"
#include "Player.h"
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
			m_HP -= 1;
		
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
