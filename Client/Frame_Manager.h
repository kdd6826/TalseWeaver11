#pragma once
class CFrame_Manager
{
public:
	CFrame_Manager();
	~CFrame_Manager();
public:
	void Ready_FrameManager(const _float& fFPS);
	bool Look_FrameManager();
	void Render_FrameManager();
	
public:
	_float m_fSPF;
	_float m_fFPS;
	_float m_fDeltaTime;

	LARGE_INTEGER m_CpuTick;
	LARGE_INTEGER m_StartTime;
	LARGE_INTEGER m_EndTime;

	_int m_iFPS;
	TCHAR m_szFPS[32];
};

