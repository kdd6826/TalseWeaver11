#pragma once
#include "GameObject.h"
class CHpBar final : public CGameObject
{
private:
	CHpBar();
public:
	~CHpBar();
public:

public:
	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void LateUpdate_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;
	virtual void OnCollision(CGameObject* _TargetObj) override;

public:
	static CGameObject* Create(LPVOID* pArg = nullptr);
	static CGameObject* Create(_vec3 vpos);
private:


};

