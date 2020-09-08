#include "stdafx.h"
#include "Monster.h"
#include "BlueWolf.h"
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
	return 0;
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
}
