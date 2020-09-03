#pragma once
class CKey_Manager
{
public:
	static CKey_Manager* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CKey_Manager;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	CKey_Manager();
	~CKey_Manager();
public:
	void Update_KeyManager();
	bool Key_UP(DWORD dwKey);
	bool Key_DOWN(DWORD dwKey);
	bool Key_Pressing(DWORD dwKey);
private:
	static CKey_Manager* m_pInstance;
	DWORD m_dwKey = 0;
	DWORD m_dwKeyUP = 0;
	DWORD m_dwKeyDOWN = 0;
};

