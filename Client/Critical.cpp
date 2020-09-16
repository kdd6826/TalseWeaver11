#include "stdafx.h"
#include "Critical.h"
#include "Monster.h"
#include "KeyManager.h"
CCritical::CCritical()
{
	m_ObjId = OBJ::OBJ_EFFECT;
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CCritical::~CCritical()
{
	Release_GameObject();
}

HRESULT CCritical::Ready_GameObject()
{
	m_tInfo.vSize = { 2.f, 2.f, 0.f };
	m_tInfo.vRealSize = { 60.f,90.f,0.f };
	//////
	m_tInfo.vDir = { 1.f,1.f,0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	//////
	m_tFrame = { 0,0 };
	srand(unsigned(time(nullptr)));
	int iRand = rand() % 10;
	m_Alpha = 100;
	return S_OK;
}

int CCritical::Update_GameObject()
{
	
	if (m_HP <= 0)
	{
		return OBJ_DEAD;
	}
	m_Alpha += 10;
	if (m_tInfo.vSize.x > 1)
	{
		m_tInfo.vSize.x -= 10 * CTime_Manager::Get_Instance()->Get_DeltaTime();
		m_tInfo.vSize.y -= 10 * CTime_Manager::Get_Instance()->Get_DeltaTime();
	}
	if (m_Alpha > 255)
	{
		return OBJ_DEAD;
	}



	return OBJ_NOEVENT;
}

void CCritical::LateUpdate_GameObject()
{
}

void CCritical::Render_GameObject()
{

	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"TextureEtc", L"Critical", DWORD(m_tFrame.fFrameStart));
	if (nullptr == pTexInfo)
		return;

	m_tInfo.vRealSize = { float(pTexInfo->tImageInfo.Width),  float(pTexInfo->tImageInfo.Height), 0.f };

	_vec3 vCenter = { _float(pTexInfo->tImageInfo.Width >> 1), _float(pTexInfo->tImageInfo.Height >> 1) , 0.f };
	_matrix matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, m_iMirror * m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + CScroll_Manager::Get_Scroll(CScroll_Manager::X), m_tInfo.vPos.y + CScroll_Manager::Get_Scroll(CScroll_Manager::Y), 0.f);
	matWorld = matScale * matTrans;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &vCenter, nullptr, D3DCOLOR_ARGB(m_Alpha, 255, 255, 255));

}

void CCritical::Release_GameObject()
{
}

void CCritical::OnCollision(CGameObject* _TargetObj)
{
	switch (_TargetObj->GetObjId()) {
	case OBJ::OBJ_MONSTER:
	{
		CMonster* tempCollision = dynamic_cast<CMonster*>(_TargetObj);

		if (tempCollision)
		{
			/*m_HP -= 1;*/
		}
	}
	}
}

CGameObject* CCritical::Create(LPVOID* pArg)
{
	CGameObject* pInstnace = new CCritical;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	return pInstnace;
}

CGameObject * CCritical::Create(_vec3 vpos)
{
	CGameObject* pInstnace = new CCritical;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	pInstnace->SetPos(vpos);
	pInstnace->SetFirstPos(vpos);
	return pInstnace;
}
