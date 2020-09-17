#pragma once
class CScene; 
class CScene_Manager
{
public:
	enum SCENE { SCENE_LOGO,SCENE_TUTORIAL, SCENE_SHOP, SCENE_TOWN1, SCENE_BOSS, SCENE_END};
	DECLARE_SINGLETON(CScene_Manager)
private:
	CScene_Manager();
	virtual ~CScene_Manager();
public:
	HRESULT Change_Scene(SCENE eNextScene);
public:
	void Update_Scene();
	void LateUpdate_Scene();
	void Render_Scene();
	void Release_Scene();
public:
	SCENE Get_SCENE() { return m_eCurScene; }
private:
	SCENE m_eCurScene; 
	SCENE m_eNextScene; 
	CScene* m_pScene; 
};

