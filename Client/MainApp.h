#pragma once
class CTime_Manager;
class CGraphic_Device;
class CFrame_Manager;
class CMainApp
{
public:
	explicit CMainApp();
	~CMainApp();

public:
	void Ready_MainApp();
	void Update_MainApp();
	void Late_Update_MainApp();
	void Render_MainApp(CFrame_Manager* pFrameManager);
	void Release_MainApp();
private:
	CGraphic_Device* m_pGraphic_Device;
	CTime_Manager* m_pTime_Manager;
};

