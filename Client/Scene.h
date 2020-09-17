#pragma once
#include "GameObject.h"
class CScene abstract
{
public:
	explicit CScene();
	virtual ~CScene();
public:
	virtual HRESULT Ready_Scene()PURE; 
	virtual void Update_Scene()PURE;
	virtual void LateUpdate_Scene()PURE;
	virtual void Render_Scene()PURE;
	virtual void Release_Scene()PURE;
public:
	void ReScroll() {
		if (!m_bCount)
		{
			CScroll_Manager::Init_ScrollXY();
			CScroll_Manager::Set_Scroll({ -CGameObject_Manager::Get_Instance()->Get_Player()->GetPos().x / 2,
	   -CGameObject_Manager::Get_Instance()->Get_Player()->GetPos().y / 2,
	   0.f });
			m_bCount = true;
		}
	};
protected:
	float m_fSummonDelay = 0.f;
	float iRandX;
	float iRandY;
	bool m_bCount=false;
	CGameObject_Manager* ObjManager = CGameObject_Manager::Get_Instance();
};

