#include "stdafx.h"
#include "Damage.h"
#include "Monster.h"
CDamage::CDamage()
{
	m_ObjId = OBJ::OBJ_DAMAGE;
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CDamage::~CDamage()
{
	Release_GameObject();
}

void CDamage::MoveFrame(_float fSpeed)
{
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * CTime_Manager::Get_Instance()->Get_DeltaTime() * fSpeed;
	if (m_tFrame.fFrameStart >= m_tFrame.fFrameEnd)
		m_tFrame.fFrameStart = 0.f;
}

HRESULT CDamage::Ready_GameObject()
{
	
	m_tInfo.vSize = {1.f,1.f,0.f};
	m_iMirror = 0;
	//////
	m_tFrame = { 0,3  };

	return S_OK;
}

int CDamage::Update_GameObject()
{
	m_Alpha -= 10;
	if (m_iMirror == 0)
	{
		++m_iMirror;
		m_tInfo.vRealSize = { m_tInfo.vPos };
	}

	
	if (m_HP <= 0)
	{
		return OBJ_DEAD;
	}
	
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * CTime_Manager::Get_Instance()->Get_DeltaTime() * 2.f;
	if (m_tFrame.fFrameStart >= m_tFrame.fFrameEnd)
		return OBJ_DEAD;


	m_tInfo.vPos.y -= 5.f;


	return OBJ_NOEVENT;
}

void CDamage::LateUpdate_GameObject()
{
}

void CDamage::Render_GameObject()
{

	if (m_fAttack < 10)
	{
		m_iAttackFont[0] = INT(m_fAttack);
	}
	if (m_fAttack >= 10&&m_fAttack<100)
	{
		m_iAttackFont[0] = INT(m_fAttack) % 10;
		m_iAttackFont[1] = INT(m_fAttack) / 10;
	}
	if (m_fAttack >= 100 && m_fAttack<1000)
	{
		m_iAttackFont[0] = INT(m_fAttack) % 10;
		m_iAttackFont[1] = INT(m_fAttack) / 10 % 10;
		m_iAttackFont[2] = INT(m_fAttack) / 100;
	}
	if (m_fAttack >= 100 && m_fAttack<1000)
	{
		m_iAttackFont[0] = INT(m_fAttack) % 10;
		m_iAttackFont[1] = INT(m_fAttack) / 10 %10;
		m_iAttackFont[2] = INT(m_fAttack) / 100%10;
		m_iAttackFont[3] = INT(m_fAttack) / 1000;
	}
	if (m_Hit ==0)
	{
		m_szFrameKey = L"PlayerHNumber";
		//����Ʈ
		pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Effect", L"PlayerHit", DWORD(m_tFrame.fFrameStart));
		if (nullptr == pTexInfo)
			return;
		_matrix matScale, matTrans, matWorld;
		_vec3 vCenter = { _float(pTexInfo->tImageInfo.Width >> 1), _float(pTexInfo->tImageInfo.Height >> 1) , 0.f };


		D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_tInfo.vRealSize.x + 20 + CScroll_Manager::Get_Scroll(CScroll_Manager::X) + 80, m_tInfo.vRealSize.y + 50 + CScroll_Manager::Get_Scroll(CScroll_Manager::Y), 0.f);
		matWorld = matScale * matTrans;
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &vCenter, nullptr, D3DCOLOR_ARGB(m_Alpha, 255, 255, 255));
		
	}
	if (m_Hit == 1)
	{
		m_szFrameKey = L"DmgFont";
		
		//����Ʈ
		pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Effect", L"MonsterHit", DWORD(m_tFrame.fFrameStart));
		if (nullptr == pTexInfo)
			return;
		_matrix matScale, matTrans, matWorld;
		_vec3 vCenter = { _float(pTexInfo->tImageInfo.Width >> 1), _float(pTexInfo->tImageInfo.Height >> 1) , 0.f };


		D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_tInfo.vRealSize.x - 20 + CScroll_Manager::Get_Scroll(CScroll_Manager::X) + 80, m_tInfo.vRealSize.y + 50 + CScroll_Manager::Get_Scroll(CScroll_Manager::Y), 0.f);
		matWorld = matScale * matTrans;
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &vCenter, nullptr, D3DCOLOR_ARGB(m_Alpha, 255, 255, 255));
	}
	if (m_Hit == 2)
	{
		m_szFrameKey = L"MagicDmgFont";
		pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Effect", L"MagicHit", DWORD(m_tFrame.fFrameStart));
		if (nullptr == pTexInfo)
			return;
		_matrix matScale, matTrans, matWorld;
		_vec3 vCenter = { _float(pTexInfo->tImageInfo.Width >> 1), _float(pTexInfo->tImageInfo.Height >> 1) , 0.f };


		D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_tInfo.vRealSize.x-20 + CScroll_Manager::Get_Scroll(CScroll_Manager::X) + 80, m_tInfo.vRealSize.y + 50 + CScroll_Manager::Get_Scroll(CScroll_Manager::Y), 0.f);
		matWorld = matScale * matTrans;
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &vCenter, nullptr, D3DCOLOR_ARGB(m_Alpha, 255, 255, 255));
	}


	


	//1���ڸ�
	if (m_fAttack > 0)
	{

		pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Effect", m_szFrameKey, m_iAttackFont[0]);
		if (nullptr == pTexInfo)
			return;
		_matrix matScale, matTrans, matWorld;
		_vec3 vCenter = { _float(pTexInfo->tImageInfo.Width >> 1), _float(pTexInfo->tImageInfo.Height >> 1) , 0.f };


		D3DXMatrixScaling(&matScale,  m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + CScroll_Manager::Get_Scroll(CScroll_Manager::X) + 100, m_tInfo.vPos.y + CScroll_Manager::Get_Scroll(CScroll_Manager::Y), 0.f);
		matWorld = matScale * matTrans;
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &vCenter, nullptr, D3DCOLOR_ARGB(m_Alpha, 255, 255, 255));
	}
	//10���ڸ�
	if (m_fAttack >= 10)
	{
		pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Effect", m_szFrameKey, m_iAttackFont[1]);
		if (nullptr == pTexInfo)
			return;
		_matrix matScale, matTrans, matWorld;
		_vec3 vCenter = { _float(pTexInfo->tImageInfo.Width >> 1), _float(pTexInfo->tImageInfo.Height >> 1) , 0.f };
		D3DXMatrixScaling(&matScale,  m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + CScroll_Manager::Get_Scroll(CScroll_Manager::X) + 80 , m_tInfo.vPos.y + CScroll_Manager::Get_Scroll(CScroll_Manager::Y), 0.f);
		matWorld = matScale * matTrans;
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &vCenter, nullptr, D3DCOLOR_ARGB(m_Alpha, 255, 255, 255));
	}
	//100���ڸ�
	if (m_fAttack >= 100)
	{
		pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Effect", m_szFrameKey, m_iAttackFont[2]);
		if (nullptr == pTexInfo)
			return;
		_matrix matScale, matTrans, matWorld;
		_vec3 vCenter = { _float(pTexInfo->tImageInfo.Width >> 1), _float(pTexInfo->tImageInfo.Height >> 1) , 0.f };
		D3DXMatrixScaling(&matScale,  m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + CScroll_Manager::Get_Scroll(CScroll_Manager::X) + 60 , m_tInfo.vPos.y + CScroll_Manager::Get_Scroll(CScroll_Manager::Y), 0.f);
		matWorld = matScale * matTrans;
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &vCenter, nullptr, D3DCOLOR_ARGB(m_Alpha, 255, 255, 255));
	}
	//1000���ڸ�
	if (m_fAttack >= 1000)
	{
		pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Effect", m_szFrameKey, m_iAttackFont[3]);
		if (nullptr == pTexInfo)
			return;
		_matrix matScale, matTrans, matWorld;
		_vec3 vCenter = { _float(pTexInfo->tImageInfo.Width >> 1), _float(pTexInfo->tImageInfo.Height >> 1) , 0.f };
		D3DXMatrixScaling(&matScale,  m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + CScroll_Manager::Get_Scroll(CScroll_Manager::X) + 40 , m_tInfo.vPos.y + CScroll_Manager::Get_Scroll(CScroll_Manager::Y), 0.f);
		matWorld = matScale * matTrans;
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &vCenter, nullptr, D3DCOLOR_ARGB(m_Alpha, 255, 255, 255));
	}
}

void CDamage::Release_GameObject()
{
}

void CDamage::OnCollision(CGameObject* _TargetObj)
{
	switch (_TargetObj->GetObjId()) {
	case OBJ::OBJ_MONSTER:
	{
		CMonster* tempCollision = dynamic_cast<CMonster*>(_TargetObj);

		if (tempCollision)
		{


		}

	}


	}
}

CGameObject* CDamage::Create(LPVOID* pArg)
{
	CGameObject* pInstnace = new CDamage;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	return pInstnace;
}

CGameObject* CDamage::Create(_vec3 vpos,float _Attack, int HitChangeNum)
{
	CGameObject* pInstnace = new CDamage;
	if (FAILED(pInstnace->Ready_GameObject()))
		return nullptr;
	pInstnace->SetPos(vpos);
	pInstnace->SetAttack(_Attack);
	dynamic_cast<CDamage*>(pInstnace)->HitChange(HitChangeNum);
	
	return pInstnace;
}
