#pragma once
#include "Scene.h"
#include "Monster_Manager.h"
class CShop :
	public CScene
{
public:
	CShop();
	virtual ~CShop();
public:
	// CScene��(��) ���� ��ӵ�
	virtual HRESULT Ready_Scene() override;
	virtual void Update_Scene() override;
	virtual void LateUpdate_Scene() override;
	virtual void Render_Scene() override;
	virtual void Release_Scene() override;
public:
	CGameObject_Manager* ObjManager = CGameObject_Manager::Get_Instance();
	CMonsterManager MonsterManager;
};

