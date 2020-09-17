#pragma once
#include "GameObject.h"
class CPlayer final : public CGameObject
{
private:
	CPlayer();
public:
	~CPlayer();
public:
	void RouteTrack();
	void MoveFrame(_float fSpeed = 1.f);
	void StopAStar();
	
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
	/*INFO m_tInfo; */

	//FRAME m_tFrame;
	_matrix m_matRotate;
	bool isAStar;

	wstring m_Normal;

	
	bool isEvolution = false;
	bool isEvoluting = false;
	bool isThunderBolt = false;
	bool isChainAttack = false;
	bool isMultiAttack = false;
	_float m_fAttackTime = 0;
	bool isMovingCount = false;

	// CGameObject을(를) 통해 상속됨

};

