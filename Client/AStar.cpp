#include "stdafx.h"
#include "AStar.h"
#include "GameObject_Manager.h"
#include "Terrain.h"
IMPLEMENT_SINGLETON(CAStar)

CAStar::CAStar()
	:m_iStartIndex(0)
{
}


CAStar::~CAStar()
{
}
_int CAStar::Get_TileIndex(const _vec3 & vPos)
{
	vector<TILE*>& vecTile = dynamic_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain())->Get_Tile();

	_int iSize = vecTile.size();
	for (size_t i = 0; i < iSize; ++i)
	{
		if (IsPicking(vPos, i))
			return i;
	}
	return _int(-1);
}

bool CAStar::IsPicking(const _vec3 & vPos, const _int & i)
{
	vector<TILE*>& vecTile = dynamic_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain())->Get_Tile();
	_vec3 vRhombusPoint[4] =
	{
		{ vecTile[i]->vPos.x, vecTile[i]->vPos.y + TILECY * 0.5f, 0.f },
		{ vecTile[i]->vPos.x + TILECX * 0.5f, vecTile[i]->vPos.y, 0.f },
		{ vecTile[i]->vPos.x, vecTile[i]->vPos.y - TILECY * 0.5f, 0.f },
		{ vecTile[i]->vPos.x - TILECX * 0.5f, vecTile[i]->vPos.y, 0.f }
	};

	//2. 마름모꼴 정점의 방향벡터 구하기. 
	_vec3 vRhombusDir[4] =
	{
		vRhombusPoint[1] - vRhombusPoint[0],
		vRhombusPoint[2] - vRhombusPoint[1],
		vRhombusPoint[3] - vRhombusPoint[2],
		vRhombusPoint[0] - vRhombusPoint[3],
	};

	//3. 마름모꼴 방향벡터의 법선백터 뽑아내기. 
	_vec3 vRhombusNormal[4] =
	{
		{ -vRhombusDir[0].y, vRhombusDir[0].x, 0.f },
		{ -vRhombusDir[1].y, vRhombusDir[1].x, 0.f },
		{ -vRhombusDir[2].y, vRhombusDir[2].x, 0.f },
		{ -vRhombusDir[3].y, vRhombusDir[3].x, 0.f }

	};
	_vec3 vMouseDir[4] =
	{
		vPos - vRhombusPoint[0],
		vPos - vRhombusPoint[1],
		vPos - vRhombusPoint[2],
		vPos - vRhombusPoint[3],
	};

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3Normalize(&vRhombusNormal[i], &vRhombusNormal[i]);
		D3DXVec3Normalize(&vMouseDir[i], &vMouseDir[i]);
		if (0 < D3DXVec3Dot(&vRhombusNormal[i], &vMouseDir[i]))
			return false;
	}
	return true;
}

bool CAStar::PathFinding(_int iStartIndex, int iGoalIndex)
{
	CTerrain* pTerrain = dynamic_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());
	vector<TILE*>& vecTile = pTerrain->Get_Tile();
	vector<list<TILE*>>& vecGraph = pTerrain->Get_Graph();

	if (!m_OpenList.empty())
		m_OpenList.pop_front();

	m_CloseList.emplace_back(iStartIndex);

	for (auto& pTile : vecGraph[iStartIndex])
	{
		if (iGoalIndex == pTile->iIndex)
		{
			pTile->iParentIndex = iStartIndex;
			return true;
		}

		if (true == Check_OpenList(pTile->iIndex) || true == Check_CloseList(pTile->iIndex))
			continue;

		pTile->iParentIndex = iStartIndex;

		m_OpenList.emplace_back(pTile->iIndex);
	}

	if (m_OpenList.empty())
		return false;

	m_OpenList.sort([&](int iPreIndex, int iNextIndex)
	{
		_vec3 v1 = vecTile[m_iStartIndex]->vPos - vecTile[iPreIndex]->vPos;
		_vec3 v2 = vecTile[iGoalIndex]->vPos - vecTile[iPreIndex]->vPos;
		float fDist1 = D3DXVec3Length(&v1) + D3DXVec3Length(&v2);

		_vec3 v3 = vecTile[m_iStartIndex]->vPos - vecTile[iNextIndex]->vPos;
		_vec3 v4 = vecTile[iGoalIndex]->vPos - vecTile[iNextIndex]->vPos;
		float fDist2 = D3DXVec3Length(&v3) + D3DXVec3Length(&v4);

		return fDist1 < fDist2;
	});

	return PathFinding(m_OpenList.front(), iGoalIndex);
}

void CAStar::Make_BestList(int iStartIndex, int iGoalIndex)
{
	CTerrain* pTerrain = dynamic_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());
	vector<TILE*>& vecTile = pTerrain->Get_Tile();

	m_BestList.emplace_back(vecTile[iGoalIndex]);
	int iParentIndex = vecTile[iGoalIndex]->iParentIndex;

	while (true)
	{
		if (iStartIndex == iParentIndex)
			break;

		m_BestList.emplace_front(vecTile[iParentIndex]);
		iParentIndex = vecTile[iParentIndex]->iParentIndex;
	}
}

bool CAStar::Check_OpenList(int iIndex)
{
	auto& iter_find = find(m_OpenList.begin(), m_OpenList.end(), iIndex);
	if (m_OpenList.end() != iter_find)
		return true;

	return false;
}

bool CAStar::Check_CloseList(int iIndex)
{
	auto& iter_find = find(m_CloseList.begin(), m_CloseList.end(), iIndex);
	if (m_CloseList.end() != iter_find)
		return true;

	return false;
}

void CAStar::Start_AStar(const _vec3 & vStart, const _vec3 & vGoal)
{
	m_BestList.clear();
	m_OpenList.clear();
	m_CloseList.clear();

	m_iStartIndex = Get_TileIndex(vStart);
	int iGoal = Get_TileIndex(vGoal);

	if (-1 == m_iStartIndex || -1 == iGoal)
		return;
	if (m_iStartIndex == iGoal)
		return;

	vector<TILE*>& vecTile = dynamic_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain())->Get_Tile();

	if (0 != vecTile[iGoal]->iOption)
		return;

	if (true == PathFinding(m_iStartIndex, iGoal))
		Make_BestList(m_iStartIndex, iGoal);
	
}

