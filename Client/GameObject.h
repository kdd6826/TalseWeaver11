#pragma once
#include "GameObject_Manager.h"
class CGameObject abstract
{
public:
	explicit CGameObject();
	virtual ~CGameObject();

public:
	virtual HRESULT Ready_GameObject() =0;
	virtual int		Update_GameObject()=0;
	virtual void	LateUpdate_GameObject()=0;
	virtual void	Render_GameObject() =0;
	virtual void	Release_GameObject()=0;
	virtual void OnCollision(CGameObject* _TargetObj)=0;
public:
	_vec3 GetPos() { return m_tInfo.vPos; }
	void SetName(const TCHAR* _name) {
		lstrcpy(m_tInfo.chName, _name);
	}
	void SetPos(_vec3& _pos) {
		m_tInfo.vPos = _pos;
	}
	void SetFirstPos(_vec3& _pos) {
		FirstPos = _pos;
	}
	void SetAttack(float& _attack) {
		m_fAttack = _attack;
	}
	float GetAttack(){ return m_fAttack; }
	int GetHp() { return m_HP; }
	RECT* GetRect() { return &m_tRect; }
	INFO* GetInfo() { return &m_tInfo; }
	int* GetMirror() { return &m_iMirror; }
	wstring GetState() { return m_szFrameKey; }
	OBJ::ID GetObjId() { return m_ObjId; }
	const TEXINFO* GetTexInfo() { return pTexInfo; }
	
	void Update_Rect_Object();

protected:
	INT m_Lv = 0;
	INT m_Exp = 0;
	INT m_MaxExp = 0;
	INT  m_HP = 1;
	INT  m_MaxHP = 1;
	INT  m_MP = 1;
	INT  m_MaxMP = 1;
	INT  m_SP = 1;
	INT  m_MaxSP = 1;
	INT m_iMirror = 1;
	float m_fAttackCount = 0;
	float m_fAttack = 0.f;
	float m_fDef = 0.f;
	float m_fCritical = 0.f;
	float m_fCriticalDamage = 0.f;
	FLOAT forceX=0.f;
	FLOAT forceY=0.f;
	bool isMoving = false;
	bool isAttack = false;
	RECT m_tRect;
	OBJ::ID m_ObjId = OBJ::OBJ_END;
	wstring m_StateKey;
	wstring m_DirectionKey;
	wstring m_szFrameKey;
	float m_fSpeed = 0.f;
	float m_fAngle = 0.f;
	INFO m_tInfo;
	_vec3 FirstPos;
	FRAME m_tFrame;
	const TEXINFO* pTexInfo;
};

