#pragma once
#include "GameObject.h"
class CDamage final : public CGameObject
{
private:
	CDamage();
public:
	~CDamage();
	void MoveFrame(_float fSpeed = 1.f);
public:
	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void LateUpdate_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;
	virtual void OnCollision(CGameObject* _TargetObj) override;
public:
	void HitChange(_int HitNumber) { m_Hit = HitNumber; }
	static CGameObject* Create(LPVOID* pArg = nullptr);
	static CGameObject* Create(_vec3 vpos, float _Attack,int HitChangeNum);
	
private:
	int m_iAttackFont[5];
	int m_Hit = 0;
	
};

