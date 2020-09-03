#pragma once
class CGameObject abstract
{
public:
	explicit CGameObject();
	virtual ~CGameObject();

public:
	virtual HRESULT Ready_GameObject() PURE;
	virtual int		Update_GameObject()PURE;
	virtual void	LateUpdate_GameObject()PURE;
	virtual void	Render_GameObject() PURE;
	virtual void	Release_GameObject()PURE;
public:
	void SetName(const TCHAR* _name) {
		lstrcpy(m_tInfo.chName, _name);
	}
	void SetPos(_vec3& _pos) {
		m_tInfo.vPos = _pos;
	}
	const TEXINFO* GetTexInfo() { return pTexInfo; }
	
protected:
	OBJ::ID m_ObjId = OBJ::OBJ_END;
	wstring m_szFrameKey;
	float m_fSpeed = 0.f;
	float m_fAngle = 0.f;
	INFO m_tInfo;
	
	FRAME m_tFrame;
	const TEXINFO* pTexInfo;
};

