#include "stdafx.h"
#include "GameObject_Manager.h"
#include "GameObject.h"

IMPLEMENT_SINGLETON(CGameObject_Manager)
CGameObject_Manager::CGameObject_Manager()
{
}


CGameObject_Manager::~CGameObject_Manager()
{
	Release_GameObject();
}

HRESULT CGameObject_Manager::Add_GameObject(OBJ::ID eID, CGameObject* pObject)
{
	if (nullptr == pObject || OBJ::OBJ_END <= eID)
		return E_FAIL;

	m_listGameObject[eID].emplace_back(pObject);
	return S_OK;
}

HRESULT CGameObject_Manager::Ready_GameObject()
{
	return S_OK;
}

int CGameObject_Manager::Update_GameObject()
{
	for (int i = 0; i < OBJ::OBJ_END; ++i)
	{
		for (OBJITER iter = m_listGameObject[i].begin(); iter != m_listGameObject[i].end(); )
		{
			int iEvent = (*iter)->Update_GameObject();
			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete(*iter);
				iter = m_listGameObject[i].erase(iter);
			}
			else
				++iter;
		}
	}
	return 0;
}

void CGameObject_Manager::LateUpdate_GameObject()
{
	for (int i = 0; i < OBJ::OBJ_END; ++i)
	{
		for (auto& pObj : m_listGameObject[i])
		{
			pObj->LateUpdate_GameObject();
		}
	}
}

void CGameObject_Manager::Render_GameObject()
{
	for (int i = 0; i < OBJ::OBJ_END; ++i)
	{
		for (auto& pObj : m_listGameObject[i])
		{
			pObj->Render_GameObject();
		}
	}
}

void CGameObject_Manager::Release_GameObject()
{
	for (int i = 0; i < OBJ::OBJ_END; ++i)
	{
		for (auto& pObj : m_listGameObject[i])
		{
			Safe_Delete(pObj);
		}
		m_listGameObject[i].clear();
	}
}

void CGameObject_Manager::Release_GameObject(OBJ::ID OBJ_ID)
{
	for (int i = OBJ_ID; i < OBJ_ID+1; ++i)
	{
		for (auto& pObj : m_listGameObject[i])
		{
			Safe_Delete(pObj);
		}
		m_listGameObject[i].clear();
	}
}
