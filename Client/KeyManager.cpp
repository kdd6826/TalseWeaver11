#include "stdafx.h"
#include "KeyManager.h"
CKey_Manager* CKey_Manager::m_pInstance = nullptr;

CKey_Manager::CKey_Manager()
{
}


CKey_Manager::~CKey_Manager()
{
}

void CKey_Manager::Update_KeyManager()
{
	m_dwKey = 0;
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		m_dwKey |= KEY_LBUTTON;
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		m_dwKey |= KEY_RBUTTON;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_dwKey |= KEY_LEFT;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_dwKey |= KEY_RIGHT;
	if (GetAsyncKeyState(VK_UP) & 0x8000)
		m_dwKey |= KEY_UP;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		m_dwKey |= KEY_DOWN;
	if (GetAsyncKeyState('S') & 0x8000)
		m_dwKey |= KEY_S;
	if (GetAsyncKeyState('D') & 0x8000)
		m_dwKey |= KEY_D;
	if (GetAsyncKeyState('R') & 0x8000)
		m_dwKey |= KEY_R;
	if (GetAsyncKeyState(VK_F1) & 0x8000)
		m_dwKey |= KEY_F1;
	if (GetAsyncKeyState(VK_F2) & 0x8000)
		m_dwKey |= KEY_F2;
	if (GetAsyncKeyState(VK_F3) & 0x8000)
		m_dwKey |= KEY_F3;
	if (GetAsyncKeyState(VK_F4) & 0x8000)
		m_dwKey |= KEY_F4;
	if (GetAsyncKeyState(VK_F5) & 0x8000)
		m_dwKey |= KEY_F5;
	if (GetAsyncKeyState(VK_F6) & 0x8000)
		m_dwKey |= KEY_F6;
	if (GetAsyncKeyState(VK_F7) & 0x8000)
		m_dwKey |= KEY_F7;
	if (GetAsyncKeyState(VK_F8) & 0x8000)
		m_dwKey |= KEY_F8;
	if (GetAsyncKeyState(VK_F8) & 0x8000)
		m_dwKey |= KEY_F8;
	if (GetAsyncKeyState(VK_F9) & 0x8000)
		m_dwKey |= KEY_F9;
	if (GetAsyncKeyState(VK_F10) & 0x8000)
		m_dwKey |= KEY_F10;


}

bool CKey_Manager::Key_UP(DWORD dwKey)
{
	if (m_dwKey & dwKey)
	{
		m_dwKeyUP |= dwKey;
		return false;
	}
	else if (m_dwKeyUP & dwKey)
	{
		m_dwKeyUP ^= dwKey;
		return true;
	}

	return false;
}

bool CKey_Manager::Key_DOWN(DWORD dwKey)
{
	if ((m_dwKey & dwKey) && !(m_dwKeyDOWN & dwKey))
	{
		m_dwKeyDOWN |= dwKey;
		return true;
	}
	else if (!(m_dwKey & dwKey) && (m_dwKeyDOWN & dwKey))
	{
		m_dwKeyDOWN ^= dwKey;
		return false;
	}
	return false;
}

bool CKey_Manager::Key_Pressing(DWORD dwKey)
{
	if (m_dwKey & dwKey)
	{
		return true;
	}
	return false;
}
