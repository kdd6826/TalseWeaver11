#include "stdafx.h"
#include "Scroll_Manager.h"

_vec3 CScroll_Manager::m_vScroll = {}; 
CScroll_Manager::CScroll_Manager()
{
}


CScroll_Manager::~CScroll_Manager()
{
}

float CScroll_Manager::Get_Scroll(SCROLL eScroll)
{
	switch (eScroll)
	{
	case CScroll_Manager::X:
		return m_vScroll.x; 
	case CScroll_Manager::Y:
		return m_vScroll.y;
	default:
		break;
	}
	return 0.0f;
}

void CScroll_Manager::Scroll_Lock(_vec3 Size)
{
	Size.z = 0.f;
	if (0 < m_vScroll.x)
		m_vScroll.x = 0;
	if (0 < m_vScroll.y)
		m_vScroll.y = 0;
	if (WINCX - (Size.x) > m_vScroll.x)
		m_vScroll.x = WINCX - (Size.x);
	if (WINCY - (Size.y) > m_vScroll.y)
		m_vScroll.y = WINCY - (Size.y);
}
