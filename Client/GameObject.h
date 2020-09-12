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
	RECT* GetRect() { return &m_tRect; }
	INFO* GetInfo() { return &m_tInfo; }
	OBJ::ID GetObjId() { return m_ObjId; }
	const TEXINFO* GetTexInfo() { return pTexInfo; }
	
	void Update_Rect_Object();

protected:
	RECT m_tRect;
	OBJ::ID m_ObjId = OBJ::OBJ_END;
	wstring m_szFrameKey;
	float m_fSpeed = 0.f;
	float m_fAngle = 0.f;
	INFO m_tInfo;
	
	FRAME m_tFrame;
	const TEXINFO* pTexInfo;
};

