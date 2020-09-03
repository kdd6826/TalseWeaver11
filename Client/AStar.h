#pragma once

class CAStar
{
	DECLARE_SINGLETON(CAStar)
public:
	CAStar();
	~CAStar();
public:
	list<TILE*>& Get_BestList() { return m_BestList; }
private:
	_int Get_TileIndex(const _vec3& vPos);
	bool IsPicking(const _vec3& vPos, const _int& i);
	bool PathFinding(_int iStartIndex, int iGoalIndex);
	void Make_BestList(int iStartIndex, int iGoalIndex);
	bool Check_OpenList(int iIndex);
	bool Check_CloseList(int iIndex);

public:
	void Start_AStar(const _vec3& vStart, const _vec3& vGoal);

private:
	list<_int> m_OpenList;
	list<_int> m_CloseList;
	list<TILE*> m_BestList;

	_int m_iStartIndex;
};

