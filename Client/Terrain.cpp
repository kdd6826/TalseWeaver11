#include "stdafx.h"
#include "Terrain.h"
#include "KeyManager.h"

CTerrain::CTerrain()
{
}


CTerrain::~CTerrain()
{
	Release_GameObject();
}

void CTerrain::CreateGraph_GameObject()
{
	m_vecGraph.resize(TILEX*TILEY);

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			int iIndex = j + (i*TILEX);
			
			// 좌측 상단
			if (0 != i && 0 != iIndex % (TILEX * 2))
			{
				if (0 == i % 2 && 0 == m_vecTile[iIndex - (TILEX + 1)]->iOption)
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex - (TILEX + 1)]);
				else if (0 != i % 2 && 0 == m_vecTile[iIndex - (TILEX)]->iOption)
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex - TILEX]);
			}

			//우측 상단
			if (0 != i && (TILEX * 2) - 1 != iIndex % (TILEX * 2))
			{
				if (0 == i % 2 && 0 == m_vecTile[iIndex - TILEX]->iOption)
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex - (TILEX)]);
				else if (0 != i % 2 && 0 == m_vecTile[iIndex - (TILEX-1)]->iOption)
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex - (TILEX-1)]);
			}

			// 좌측 하단
			if (TILEY-1 != i && 0 != iIndex % (TILEX * 2))
			{
				if (0 == i % 2 && 0 == m_vecTile[iIndex + (TILEX - 1)]->iOption)
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex + (TILEX - 1)]);
				else if (0 != i % 2 && 0 == m_vecTile[iIndex + (TILEX)]->iOption)
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex + TILEX]);
			}

			//우측 하단
			if (TILEY-1 != i && (TILEX * 2) - 1 != iIndex % (TILEX * 2))
			{
				if (0 == i % 2 && 0 == m_vecTile[iIndex + TILEX]->iOption)
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex + (TILEX)]);
				else if (0 != i % 2 && 0 == m_vecTile[iIndex + (TILEX + 1)]->iOption)
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex + (TILEX + 1)]);
			}

			//상단
			if (1 < i)
			{
				if (0 == m_vecTile[iIndex - (TILEX * 2 )]->iOption)
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex - (TILEX * 2)]);
			}
			//하단
			if (TILEY - 2 > i)
			{
				if (0 == m_vecTile[iIndex + (TILEX * 2)]->iOption)
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex + (TILEX * 2)]);
			}
			////좌측
			if (0 != iIndex % (TILEX * 2))
			{
				if (0 == m_vecTile[iIndex  - 1]->iOption)
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex - 1]);
			}
			//우측
			if ((TILEX * 2) - 1 != iIndex % (TILEX * 2))
			{
				if (0 == m_vecTile[iIndex + 1]->iOption)
					m_vecGraph[iIndex].emplace_back(m_vecTile[iIndex + 1]);
			}
		}
	}
}

void CTerrain::ReadTerrinData(const wstring & wstrFilePath)
{
	HANDLE hFile = CreateFile(wstrFilePath.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (INVALID_HANDLE_VALUE == hFile)
		return; 

	DWORD dwByte = 0; 
	TILE tTile = {}; 
	m_vecTile.reserve(TILEX * TILEY);
	while (true)
	{
		ReadFile(hFile, &tTile, sizeof(TILE), &dwByte, nullptr); 
		if(0 == dwByte)
			break;

		m_vecTile.emplace_back(new TILE(tTile)); 
	}
	CloseHandle(hFile); 
	CreateGraph_GameObject();
}

HRESULT CTerrain::Ready_GameObject()
{
	return S_OK;
}

int CTerrain::Update_GameObject()
{
	_float fScrollSpeed = 300.f * CTime_Manager::Get_Instance()->Get_DeltaTime();
	if (GetAsyncKeyState(VK_LEFT))
		CScroll_Manager::Set_Scroll({ 5.f, 0.f, 0.f }); 
	if (GetAsyncKeyState(VK_RIGHT))
		CScroll_Manager::Set_Scroll({ -5.f, 0.f, 0.f });
	if (GetAsyncKeyState(VK_UP))
		CScroll_Manager::Set_Scroll({ 0.f,5.f,  0.f });
	if (GetAsyncKeyState(VK_DOWN))
		CScroll_Manager::Set_Scroll({ 0.f,-5.f,  0.f });

	return 0;
}

void CTerrain::LateUpdate_GameObject()
{
}

void CTerrain::Render_GameObject()
{
	_uint iSize = m_vecTile.size();

	for (_uint i = 0 ; i < iSize; ++i)
	{
		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Terrain", L"Tile", m_vecTile[i]->iDrawID);
		if (nullptr == pTexInfo)
			return; 

		float fCenterX = float(pTexInfo->tImageInfo.Width >> 1); 
		float fCenterY = float(pTexInfo->tImageInfo.Height >> 1); 

		_matrix matScale, matTrans, matWorld; 
		D3DXMatrixScaling(&matScale, m_vecTile[i]->vSize.x, m_vecTile[i]->vSize.y, 0.f); 
		D3DXMatrixTranslation(&matTrans, m_vecTile[i]->vPos.x + CScroll_Manager::Get_Scroll(CScroll_Manager::X), m_vecTile[i]->vPos.y + CScroll_Manager::Get_Scroll(CScroll_Manager::Y), 0.f);
		matWorld = matScale * matTrans; 
		if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_F1))
		{
			if (m_vecTile[i]->vPos.x + CScroll_Manager::Get_Scroll(CScroll_Manager::X) < WINCX + 100 && m_vecTile[i]->vPos.x + CScroll_Manager::Get_Scroll(CScroll_Manager::X) > -100 && m_vecTile[i]->vPos.y + CScroll_Manager::Get_Scroll(CScroll_Manager::Y) > -100 && m_vecTile[i]->vPos.y + CScroll_Manager::Get_Scroll(CScroll_Manager::Y) < WINCY + 100)
			{
				CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
				CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
		}
		
	}
	
}

void CTerrain::Release_GameObject()
{
	for (auto& pTile : m_vecTile)
	{
		Safe_Delete(pTile); 
	}
	m_vecTile.clear(); 
	m_vecTile.swap(vector<TILE*>()); 

// 	for (int i = 0 ; i < m_vecTile.size() ; ++i)
// 	{
// 		[&]()
// 		{
// 			if (nullptr != m_vecTile[i])
// 			{
// 				delete m_vecTile[i]; 
// 				m_vecTile[i] = nullptr; 
// 			}
// 		}();
// 	}
}

CGameObject * CTerrain::Create(wstring PathKeyWord)
{
	CGameObject* pInstnace = new CTerrain; 
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr; 
	
	dynamic_cast<CTerrain*>(pInstnace)->ReadTerrinData(PathKeyWord);
	return pInstnace;
}
