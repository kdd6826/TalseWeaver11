#pragma once
#include "GameObject.h"
class CTerrain final :
	public CGameObject
{
private:
	explicit CTerrain();
public:
	virtual ~CTerrain();
public:
	vector<TILE*>& Get_Tile() { return m_vecTile; }
	vector<list<TILE*>>& Get_Graph() { return m_vecGraph; }
public:
	void CreateGraph_GameObject();
public:
	// CGameObject을(를) 통해 상속됨
	void ReadTerrinData(const wstring& wstrFilePath); 
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void LateUpdate_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;
	virtual void OnCollision(CGameObject* _TargetObj) override;
public:
	static CGameObject* Create(wstring PathKeyWord); 
private:
	vector<TILE*> m_vecTile; 
	vector<list<TILE*>> m_vecGraph;
	

	// CGameObject을(를) 통해 상속됨


};

