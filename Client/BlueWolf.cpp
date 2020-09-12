#include "stdafx.h"
#include "BlueWolf.h"

CBlueWolf::CBlueWolf()
{
	m_ObjId = OBJ::OBJ_MONSTER;
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CBlueWolf::~CBlueWolf()
{
	Release_GameObject();
}

HRESULT CBlueWolf::Ready_GameObject()
{
	m_tInfo.vPos = { 1100.f, 600.f, 0.f };

	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	m_tInfo.vRealSize = { 60.f,90.f,0.f };
	//////
	m_tInfo.vDir = { 1.f,1.f,0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	///////
	m_szFrameKey = L"Stand_LUp";
	m_tFrame = { 0.f, 5.f };
	m_fSpeed = 2.f;
	m_fAngle = 0.f;

	m_HP = 10;
	return S_OK;
}

int CBlueWolf::Update_GameObject()
{
	CGameObject::Update_Rect_Object();
	MoveFrame(m_fSpeed);
	m_szFrameKey = L"Stand_LDown";
	if (m_HP <= 0)
	{
		return OBJ_DEAD;
	}
	return OBJ_NOEVENT;
}

void CBlueWolf::LateUpdate_GameObject()
{
}

void CBlueWolf::Render_GameObject()
{

	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"BlueWolf", m_szFrameKey, DWORD(m_tFrame.fFrameStart));

	if (nullptr == pTexInfo)
		return;
	_vec3 vCenter = { _float(pTexInfo->tImageInfo.Width >> 1), _float(pTexInfo->tImageInfo.Height >> 1) , 0.f };


	_matrix matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + CScroll_Manager::Get_Scroll(CScroll_Manager::X), m_tInfo.vPos.y + CScroll_Manager::Get_Scroll(CScroll_Manager::Y), 0.f);

	matWorld = matScale * matTrans;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &vCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


}

void CBlueWolf::Release_GameObject()
{
}


void CBlueWolf::MoveFrame(_float fSpeed)
{
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * CTime_Manager::Get_Instance()->Get_DeltaTime() * fSpeed;
	if (m_tFrame.fFrameStart >= m_tFrame.fFrameEnd)
		m_tFrame.fFrameStart = 0.f;
}

CGameObject* CBlueWolf::Create(LPVOID* pArg)
{
	CGameObject* pInstnace = new CBlueWolf;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	return pInstnace;
}

CGameObject* CBlueWolf::Create(_vec3 vpos)
{
	CGameObject* pInstnace = new CBlueWolf;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	pInstnace->SetPos(vpos);
	return pInstnace;
}
