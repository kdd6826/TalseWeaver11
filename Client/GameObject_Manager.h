#pragma once
class CGameObject;
class CGameObject_Manager
{
	DECLARE_SINGLETON(CGameObject_Manager)
private:
	CGameObject_Manager();
	~CGameObject_Manager();
public:
	CGameObject* Get_Terrain() { return m_listGameObject[OBJ::OBJ_TERRAIN].front(); }
	CGameObject* Get_Player() { return m_listGameObject[OBJ::OBJ_PLAYER].front(); }
	
	CGameObject* Get_Mouse() { return m_listGameObject[OBJ::OBJ_MOUSE].front(); }
	list <CGameObject*>* GetList(OBJ::ID eID) { return &m_listGameObject[eID]; }
public:
	HRESULT Add_GameObject(OBJ::ID eID, CGameObject* pObject);
public:
	HRESULT Ready_GameObject();
	int		Update_GameObject();
	void	LateUpdate_GameObject();
	void	Render_GameObject();
	void	Release_GameObject();
	void	Release_GameObject(OBJ::ID OBJ_ID);
private:
	typedef list<CGameObject*> OBJLIST;
	typedef list<CGameObject*>::iterator OBJITER;
	OBJLIST m_listGameObject[OBJ::OBJ_END];
};

