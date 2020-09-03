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
public:
	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void LateUpdate_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

public:
	static CGameObject* Create(LPVOID* pArg = nullptr);
private:
	/*INFO m_tInfo; */

	//FRAME m_tFrame;
	_matrix m_matRotate;
	int m_iMirror = 1;
	wstring m_StateKey;
	wstring m_DirectionKey;


	bool isMoving = false;
	bool isAttack = false;
	_float m_fAttackTime = 0;
	bool isMovingCount = false;
};

