#include "stdafx.h"
#include "StatusWindow.h"

#include "KeyManager.h"
CStatusWindow::CStatusWindow()
{
	m_ObjId = OBJ::OBJ_STATUS;
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CStatusWindow::~CStatusWindow()
{
	Release_GameObject();
}

HRESULT CStatusWindow::Ready_GameObject()
{
	m_tInfo.vPos = { 610.f, 210.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	//////
	m_tInfo.vDir = { 1.f,1.f,0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };

	//////
	m_tFrame = { 0,1 };

	return S_OK;
}

int CStatusWindow::Update_GameObject()
{

	

		/*return OBJ_DEAD;*/
	
	return OBJ_NOEVENT;
}

void CStatusWindow::LateUpdate_GameObject()
{

}

void CStatusWindow::Render_GameObject()
{

	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"UI", L"StatusWindow", 0);
	if (nullptr == pTexInfo)
		return;


	_vec3 vCenter = { _float(pTexInfo->tImageInfo.Width >> 1), _float(pTexInfo->tImageInfo.Height >> 1) , 0.f };
	_matrix matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	matWorld = matScale * matTrans;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &vCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


	//이하 텍스트
}

void CStatusWindow::Release_GameObject()
{
}

void CStatusWindow::OnCollision(CGameObject* _TargetObj)
{
	switch (_TargetObj->GetObjId()) {

	}
}


CGameObject* CStatusWindow::Create(LPVOID* pArg)
{
	CGameObject* pInstnace = new CStatusWindow;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	return pInstnace;
}

CGameObject* CStatusWindow::Create(_vec3 vpos)
{
	CGameObject* pInstnace = new CStatusWindow;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	pInstnace->SetPos(vpos);
	pInstnace->SetFirstPos(vpos);
	return pInstnace;
}
