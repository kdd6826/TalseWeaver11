#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif
#ifdef _AFX
#define ERR_MSG(Message) AfxMessageBox(Message)
#else
#define ERR_MSG(Message) MessageBox(nullptr,Message,L"System_Error",MB_OK)
#endif
extern HWND g_hWND;

#define		KEY_LBUTTON		0x00000001
#define		KEY_RBUTTON		0x00000002
#define		KEY_LEFT		0x00000004
#define		KEY_RIGHT		0x00000008
#define		KEY_UP			0x00000010
#define		KEY_DOWN		0x00000020
#define		KEY_S			0x00000040
#define		KEY_D			0x00000080
#define		KEY_R			0x00000100
#define		KEY_F1			0x00000200
#define		KEY_F2			0x00000400
#define		KEY_F3			0x00000800
#define		KEY_F4			0x00001000
#define		KEY_F5			0x00002000
#define		KEY_F6			0x00004000
#define		KEY_F7			0x00008000
#define		KEY_F8			0x00010000
#define		KEY_F9			0x00020000
#define		KEY_F10			0x00040000

#define OBJ_DEAD 1
#define OBJ_NOEVENT 0 
#define WINCX 800
#define WINCY 600
#define TILECX 100
#define TILECY 60
#define TILEX 30
#define TILEY 60


const _vec3 ShopSize = { 1430.f,867.f,0.f };
const _vec3 Town1Size = { 1600.f,1200.f,0.f };
const _vec3 TutorialSize = { 3222.f,1677.f,0.f };
#define ∞≠√∂∞À	0x01	//0000 0001
#define ¡ˆ∆Œ¿Ã	0x02	//0000 0010 
#define ≥™¿Ã«¡	0x04	//0000 0100

#define DECLARE_SINGLETON(ClassName)							\
public:															\
static ClassName* Get_Instance()								\
{																\
	if (nullptr == m_pInstance)									\
		m_pInstance = new ClassName;							\
	return m_pInstance;											\
}																\
static void Destroy_Instance()									\
{																\
	if (m_pInstance)											\
	{															\
		delete m_pInstance;										\
		m_pInstance = nullptr;									\
	}															\
}																\
private:														\
	static ClassName* m_pInstance;				

#define IMPLEMENT_SINGLETON(ClassName)							\
ClassName* ClassName::m_pInstance = nullptr;