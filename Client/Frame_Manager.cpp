#include "stdafx.h"
#include "Frame_Manager.h"
#include "Player.h"

CFrame_Manager::CFrame_Manager()
	: m_iFPS(0)
	, m_fFPS(0.f)
	, m_szFPS(L"")
	, m_fDeltaTime(0.f)
{
	ZeroMemory(&m_CpuTick, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_StartTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_EndTime, sizeof(LARGE_INTEGER));

}


CFrame_Manager::~CFrame_Manager()
{
}

void CFrame_Manager::Ready_FrameManager(const _float & fFPS)
{
	m_fSPF = 1.f / fFPS;
	QueryPerformanceCounter(&m_StartTime);
	QueryPerformanceCounter(&m_EndTime);
	QueryPerformanceFrequency(&m_CpuTick);
}

bool CFrame_Manager::Look_FrameManager()
{
	QueryPerformanceFrequency(&m_CpuTick);
	QueryPerformanceCounter(&m_EndTime);

	m_fDeltaTime += float(m_EndTime.QuadPart - m_StartTime.QuadPart) / m_CpuTick.QuadPart;
	if (m_fSPF < m_fDeltaTime)
	{
		m_fDeltaTime = 0.f;
		++m_iFPS;
		m_StartTime.QuadPart = m_EndTime.QuadPart;
		return true;
	}
	m_StartTime.QuadPart = m_EndTime.QuadPart;
	return false;
}

void CFrame_Manager::Render_FrameManager()
{
	m_fFPS += CTime_Manager::Get_Instance()->Get_DeltaTime();
	int i = CGameObject_Manager::Get_Instance()->Get_Player()->GetHp();
	if (1.f < m_fFPS)
	{
		//프레임표시
		wsprintf(m_szFPS, L"FPS: %d", m_iFPS);
		/*wsprintf(m_szFPS, L"HP: %d", i);*/
		m_iFPS = 0;
		m_fFPS = 0.f;
	}

	_matrix matTrans;
	D3DXMatrixTranslation(&matTrans, 100.f, 100.f, 0.f);

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matTrans);
	CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), m_szFPS, lstrlen(m_szFPS), nullptr, 0, D3DCOLOR_ARGB(255, 0, 0, 0));

}
