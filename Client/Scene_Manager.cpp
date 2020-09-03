#include "stdafx.h"
#include "Scene_Manager.h"
#include "Stage.h"
#include "Town1.h"
IMPLEMENT_SINGLETON(CScene_Manager)
CScene_Manager::CScene_Manager()
	:m_eCurScene(SCENE_END)
	, m_eNextScene(SCENE_END)
	, m_pScene(nullptr)
{
}


CScene_Manager::~CScene_Manager()
{
	Release_Scene();
}

HRESULT CScene_Manager::Change_Scene(SCENE eNextScene)
{
	m_eNextScene = eNextScene;
	if (m_eCurScene != m_eNextScene)
	{
		Safe_Delete(m_pScene);
		switch (m_eNextScene)
		{
		case CScene_Manager::SCENE_LOGO:
			// ���� 
			break;
		case CScene_Manager::SCENE_STAGE:
			m_pScene = new CStage;
			break;
		case CScene_Manager::SCENE_TOWN1:
			m_pScene = new CTown1;
			break;


		case CScene_Manager::SCENE_BOSS:
			break;

		default:
			break;
		}
		if (FAILED(m_pScene->Ready_Scene()))
			return E_FAIL;

		m_eCurScene = m_eNextScene;
	}
	return S_OK;
}

void CScene_Manager::Update_Scene()
{
	m_pScene->Update_Scene();
}

void CScene_Manager::LateUpdate_Scene()
{
	m_pScene->LateUpdate_Scene();
}

void CScene_Manager::Render_Scene()
{
	m_pScene->Render_Scene();
}

void CScene_Manager::Release_Scene()
{
	Safe_Delete(m_pScene);
}
