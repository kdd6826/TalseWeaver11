#pragma once
#include "GameObject_Manager.h"
class CMonsterManager {
public:
	CMonsterManager();
	~CMonsterManager();
public:
	void ReadyMonster();
	void InsterMonster(MONSTERDATA* _newMonster);
	void CreateMonster();
private:
	list<MONSTERDATA*> m_ListMonsterData;
	CGameObject_Manager* GameObject_Manager = CGameObject_Manager::Get_Instance();
	DWORD m_Timer = GetTickCount();

};