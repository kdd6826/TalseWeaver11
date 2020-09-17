#pragma once
#include "GameObject.h"
class CPlayerStatus final : public CGameObject
{
private:
	CPlayerStatus();
public:
	~CPlayerStatus();
public:

public:
	// CGameObject��(��) ���� ��ӵ�
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
	TCHAR m_Stat[32];

};

