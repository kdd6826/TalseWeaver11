#include "stdafx.h"
#include "PlayerStatus.h"
#include "Monster.h"
#include "KeyManager.h"
CPlayerStatus::CPlayerStatus()
{
	m_ObjId = OBJ::OBJ_UI;
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CPlayerStatus::~CPlayerStatus()
{
	Release_GameObject();
}

HRESULT CPlayerStatus::Ready_GameObject()
{
	m_tInfo.vPos = { 130.f, 70.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	//////
	m_tInfo.vDir = { 1.f,1.f,0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };

	//////
	m_tFrame = { 0,1};

	return S_OK;
}

int CPlayerStatus::Update_GameObject()
{
	return OBJ_NOEVENT;
}

void CPlayerStatus::LateUpdate_GameObject()
{
}

void CPlayerStatus::Render_GameObject()
{

	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"UI", L"PlayerStatus", 0);
	if (nullptr == pTexInfo)
		return;


	_vec3 vCenter = { _float(pTexInfo->tImageInfo.Width >> 1), _float(pTexInfo->tImageInfo.Height >> 1) , 0.f };
	_matrix matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, m_iMirror * m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x , m_tInfo.vPos.y, 0.f);
	matWorld = matScale * matTrans;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &vCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	//이하 텍스트
	//공격력
	int Att = CGameObject_Manager::Get_Instance()->Get_Player()->GetAttack();
	wsprintf(m_Stat, L"공격력              %d", Att);
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x / 3, m_tInfo.vSize.y / 2, 0.f);
	D3DXMatrixTranslation(&matTrans, 465.f, 240.f, 0.f);
	matWorld = matScale * matTrans;
	if (CGameObject_Manager::Get_Instance()->GetList(OBJ::OBJ_STATUS)->size() == 1)
	{
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), m_Stat, lstrlen(m_Stat), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	//방어력
	int Def = CGameObject_Manager::Get_Instance()->Get_Player()->GetDef();
	wsprintf(m_Stat, L"방어력              %d", Def);
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x / 3, m_tInfo.vSize.y / 2, 0.f);
	D3DXMatrixTranslation(&matTrans, 465.f, 255.f, 0.f);
	matWorld = matScale * matTrans;
	if (CGameObject_Manager::Get_Instance()->GetList(OBJ::OBJ_STATUS)->size() == 1)
	{
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), m_Stat, lstrlen(m_Stat), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	//크리티컬
	int Cri = CGameObject_Manager::Get_Instance()->Get_Player()->GetCritical();
	wsprintf(m_Stat, L"치명타확률       %d%%", Cri);
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x / 3, m_tInfo.vSize.y / 2, 0.f);
	D3DXMatrixTranslation(&matTrans, 465.f, 270.f, 0.f);
	matWorld = matScale * matTrans;
	if (CGameObject_Manager::Get_Instance()->GetList(OBJ::OBJ_STATUS)->size() == 1)
	{
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), m_Stat, lstrlen(m_Stat), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	//크리티컬데미지
	int CriDmg = CGameObject_Manager::Get_Instance()->Get_Player()->GetCriticalDamage()*100;
	wsprintf(m_Stat, L"치명타데미지    %d%%", CriDmg);
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x / 3, m_tInfo.vSize.y / 2, 0.f);
	D3DXMatrixTranslation(&matTrans, 465.f, 285.f, 0.f);
	matWorld = matScale * matTrans;
	if (CGameObject_Manager::Get_Instance()->GetList(OBJ::OBJ_STATUS)->size() == 1)
	{
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), m_Stat, lstrlen(m_Stat), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	int Hp = CGameObject_Manager::Get_Instance()->Get_Player()->GetHp();
	wsprintf(m_Stat, L"%d", Hp);
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x/3, m_tInfo.vSize.y/2, 0.f);
	D3DXMatrixTranslation(&matTrans, 665.f, 240.f, 0.f);
	matWorld = matScale * matTrans;
	if (CGameObject_Manager::Get_Instance()->GetList(OBJ::OBJ_STATUS)->size() == 1)
	{
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), m_Stat, lstrlen(m_Stat), nullptr, 0, D3DCOLOR_ARGB(255, 0, 0, 0));
	}

	int MaxHp = CGameObject_Manager::Get_Instance()->Get_Player()->GetMaxHp();
	wsprintf(m_Stat, L"/ %d", MaxHp);
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x / 3, m_tInfo.vSize.y / 2, 0.f);
	D3DXMatrixTranslation(&matTrans, 715.f, 240.f, 0.f);
	matWorld = matScale * matTrans;
	if (CGameObject_Manager::Get_Instance()->GetList(OBJ::OBJ_STATUS)->size() == 1)
	{
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), m_Stat, lstrlen(m_Stat), nullptr, 0, D3DCOLOR_ARGB(255, 0, 0, 0));
	}

	//MP
	int Mp = CGameObject_Manager::Get_Instance()->Get_Player()->GetMp();
	wsprintf(m_Stat, L"%d", Mp);
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x / 3, m_tInfo.vSize.y / 2, 0.f);
	D3DXMatrixTranslation(&matTrans, 665.f, 255.f, 0.f);
	matWorld = matScale * matTrans;
	if (CGameObject_Manager::Get_Instance()->GetList(OBJ::OBJ_STATUS)->size() == 1)
	{
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), m_Stat, lstrlen(m_Stat), nullptr, 0, D3DCOLOR_ARGB(255, 0, 0, 0));
	}

	int MaxMp = CGameObject_Manager::Get_Instance()->Get_Player()->GetMaxMp();
	wsprintf(m_Stat, L"/ %d", MaxMp);
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x / 3, m_tInfo.vSize.y / 2, 0.f);
	D3DXMatrixTranslation(&matTrans, 715.f, 255.f, 0.f);
	matWorld = matScale * matTrans;
	if (CGameObject_Manager::Get_Instance()->GetList(OBJ::OBJ_STATUS)->size() == 1)
	{
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), m_Stat, lstrlen(m_Stat), nullptr, 0, D3DCOLOR_ARGB(255, 0, 0, 0));
	}


	//SP
	int Sp = CGameObject_Manager::Get_Instance()->Get_Player()->GetSp();
	wsprintf(m_Stat, L"%d", Sp);
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x / 3, m_tInfo.vSize.y / 2, 0.f);
	D3DXMatrixTranslation(&matTrans, 665.f, 270.f, 0.f);
	matWorld = matScale * matTrans;
	if (CGameObject_Manager::Get_Instance()->GetList(OBJ::OBJ_STATUS)->size() == 1)
	{
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), m_Stat, lstrlen(m_Stat), nullptr, 0, D3DCOLOR_ARGB(255, 0, 0, 0));
	}

	int MaxSp = CGameObject_Manager::Get_Instance()->Get_Player()->GetMaxSp();
	wsprintf(m_Stat, L"/ %d", MaxSp);
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x / 3, m_tInfo.vSize.y / 2, 0.f);
	D3DXMatrixTranslation(&matTrans, 715.f, 270.f, 0.f);
	matWorld = matScale * matTrans;
	if (CGameObject_Manager::Get_Instance()->GetList(OBJ::OBJ_STATUS)->size() == 1)
	{
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), m_Stat, lstrlen(m_Stat), nullptr, 0, D3DCOLOR_ARGB(255, 0, 0, 0));
	}
}

void CPlayerStatus::Release_GameObject()
{
}

void CPlayerStatus::OnCollision(CGameObject* _TargetObj)
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


CGameObject* CPlayerStatus::Create(LPVOID* pArg)
{
	CGameObject* pInstnace = new CPlayerStatus;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	return pInstnace;
}

CGameObject * CPlayerStatus::Create(_vec3 vpos)
{
	CGameObject* pInstnace = new CPlayerStatus;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	pInstnace->SetPos(vpos);
	pInstnace->SetFirstPos(vpos);
	return pInstnace;
}
