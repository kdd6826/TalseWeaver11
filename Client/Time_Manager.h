#pragma once
class CTime_Manager
{
	DECLARE_SINGLETON(CTime_Manager);
public:
	CTime_Manager();
	~CTime_Manager();
public:
	_float Get_DeltaTime() { return m_fDeltaTime; }
public:
	void Ready_TimeManager();
	void Update_TimeManager();
private:
	LARGE_INTEGER m_CpuTick;
	LARGE_INTEGER m_StartTime;
	LARGE_INTEGER m_EndTime;

	_float m_fDeltaTime;
};

