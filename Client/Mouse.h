#pragma once
#include "GameObject.h"
class CMouse final : public CGameObject
{
private:
	CMouse();
public:
	~CMouse();
public:
	void MoveFrame(_float fSpeed = 1.f);
	void Animaition_Change();
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
private:
};

