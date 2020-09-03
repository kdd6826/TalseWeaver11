#include "stdafx.h"
#include "Time_Manager.h"

IMPLEMENT_SINGLETON(CTime_Manager)
CTime_Manager::CTime_Manager()
	:m_fDeltaTime(0.0)
{
	ZeroMemory(&m_CpuTick,sizeof(LARGE_INTEGER));
	ZeroMemory(&m_StartTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_EndTime, sizeof(LARGE_INTEGER));

}


CTime_Manager::~CTime_Manager()
{
}

void CTime_Manager::Ready_TimeManager()
{
	QueryPerformanceFrequency(&m_CpuTick);
	QueryPerformanceCounter(&m_StartTime);
	QueryPerformanceCounter(&m_EndTime);
}

void CTime_Manager::Update_TimeManager()
{
	QueryPerformanceFrequency(&m_CpuTick);
	QueryPerformanceCounter(&m_EndTime);
	m_fDeltaTime = _float(m_EndTime.QuadPart - m_StartTime.QuadPart )/ m_CpuTick.QuadPart;
	m_StartTime.QuadPart = m_EndTime.QuadPart;
}
