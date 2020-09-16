#include "stdafx.h"
#include "GameObject.h"


CGameObject::CGameObject()
{
}


CGameObject::~CGameObject()
{
}

void CGameObject::Update_Rect_Object()
{
	/*int iScrollX = CScroll_Manager::Get_Scroll().x;
	int iScrollY = CScroll_Manager::Get_Scroll().y;
	*/
	if (nullptr == pTexInfo)
		return;
		m_tRect.left = LONG(m_tInfo.vPos.x - (m_tInfo.vRealSize.x / 2));
		m_tRect.top = LONG(m_tInfo.vPos.y - (m_tInfo.vRealSize.y / 2));
		m_tRect.right = LONG(m_tInfo.vPos.x + (m_tInfo.vRealSize.x / 2));
		m_tRect.bottom = LONG(m_tInfo.vPos.y + (m_tInfo.vRealSize.y / 2));
	
}
