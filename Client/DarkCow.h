#pragma once
#include "Monster.h"
class CDarkCow :
	public CMonster
{
public:
	CDarkCow();
	virtual ~CDarkCow();
public:
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void LateUpdate_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

public:
	void MoveFrame(_float fSpeed = 1.f);
public:
	static CGameObject* Create(LPVOID* pArg = nullptr);
	static CGameObject* Create(_vec3 vpos);
};

