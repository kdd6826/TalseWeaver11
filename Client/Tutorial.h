#pragma once
#include "Scene.h"
class CTutorial :
	public CScene
{
public:
	CTutorial();
	virtual ~CTutorial();
public:
	// CScene��(��) ���� ��ӵ�
	virtual HRESULT Ready_Scene() override;
	virtual void Update_Scene() override;
	virtual void LateUpdate_Scene() override;
	virtual void Render_Scene() override;
	virtual void Release_Scene() override;
public:
	CGameObject_Manager* ObjManager = CGameObject_Manager::Get_Instance();
};

