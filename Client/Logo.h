#pragma once
#include "Scene.h"
class CLogo :
	public CScene
{
public:
	CLogo();
	virtual ~CLogo();
public:

	// CScene��(��) ���� ��ӵ�
	virtual HRESULT Ready_Scene() override;
	virtual void Update_Scene() override;
	virtual void LateUpdate_Scene() override;
	virtual void Render_Scene() override;
	virtual void Release_Scene() override;
};

