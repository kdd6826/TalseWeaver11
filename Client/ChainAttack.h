#pragma once
#include "GameObject.h"
class CChainAttack final : public CGameObject
{
private:
	CChainAttack();
public:
	~CChainAttack();

public:
	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void LateUpdate_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;
	virtual void OnCollision(CGameObject* _TargetObj) override;

public:
	void MoveFrame(_float fSpeed = 1.f);
	static CGameObject* Create(LPVOID* pArg = nullptr);
	static CGameObject* Create(_vec3 vpos, WCHAR* _name);
private:

};

