#include "stdafx.h"
#include "Monster_Manager.h"
#include "BlueWolf.h"
CMonsterManager::CMonsterManager()
{
}

CMonsterManager::~CMonsterManager()
{
}

void CMonsterManager::ReadyMonster()
{
}

void CMonsterManager::InsterMonster(MONSTERDATA* _newMonster)
{
	m_ListMonsterData.emplace_back(_newMonster);
}

void CMonsterManager::CreateMonster()
{

	if (m_ListMonsterData.size()) {
		auto iterList = m_ListMonsterData.begin();
		if ((*iterList)->timer + m_Timer < GetTickCount()) {

			CGameObject* tempMonster = nullptr;

			switch ((*iterList)->monster) {
			case MONSTER::BLUEWOLF:
				tempMonster = new CBlueWolf();
				tempMonster->SetName(L"BlueWolf");
				break;
			default:

				tempMonster = new CMonster();
				break;
			}
			tempMonster->SetPos((*iterList)->pos);
			tempMonster->Ready_GameObject();
			GameObject_Manager->Add_GameObject(OBJ::OBJ_MONSTER, tempMonster);
			m_ListMonsterData.erase(iterList);
		}
	}
}
