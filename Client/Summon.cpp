#include "stdafx.h"
#include "Summon.h"
#include "Monster.h"
#include "KeyManager.h"
CSummon::CSummon()
{
	m_ObjId = OBJ::OBJ_SUMMON;
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CSummon::~CSummon()
{
	Release_GameObject();
}

HRESULT CSummon::Ready_GameObject()
{
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	m_tInfo.vRealSize = { 60.f,90.f,0.f };
	//////
	m_tInfo.vDir = { 1.f,1.f,0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	//////
	m_tFrame = { 0,2 };
	srand(unsigned(time(nullptr)));
	int iRand = rand() % 10;
	m_Alpha = 100;
	return S_OK;
}

int CSummon::Update_GameObject()
{
	MoveFrame(2.f);

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

void CSummon::LateUpdate_GameObject()
{
}

void CSummon::Render_GameObject()
{

	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Effect", L"Summon", DWORD(m_tFrame.fFrameStart));
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

void CSummon::Release_GameObject()
{
}

void CSummon::OnCollision(CGameObject* _TargetObj)
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

void CSummon::MoveFrame(_float fSpeed)
{
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * CTime_Manager::Get_Instance()->Get_DeltaTime() * fSpeed;
	if (m_tFrame.fFrameStart >= m_tFrame.fFrameEnd)
		m_tFrame.fFrameStart = 0.f;
}

CGameObject* CSummon::Create(LPVOID* pArg)
{
	CGameObject* pInstnace = new CSummon;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	return pInstnace;
}

CGameObject * CSummon::Create(_vec3 vpos)
{
	CGameObject* pInstnace = new CSummon;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	pInstnace->SetPos(vpos);
	pInstnace->SetFirstPos(vpos);
	return pInstnace;
}
