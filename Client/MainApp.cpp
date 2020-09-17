#include "stdafx.h"
#include "MainApp.h"
#include "Scene_Manager.h"
#include "KeyManager.h"
#include "Frame_Manager.h"
#include "AStar.h"
#include "SoundMgr.h"
CMainApp::CMainApp()
	: m_pGraphic_Device(CGraphic_Device::Get_Instance())
	, m_pTime_Manager(CTime_Manager::Get_Instance())
{
}


CMainApp::~CMainApp()
{
	Release_MainApp();
}

void CMainApp::Ready_MainApp()
{
	CSoundMgr::Get_Instance()->Initialize();
	m_pTime_Manager->Ready_TimeManager();
	if (FAILED(CGraphic_Device::Get_Instance()->Ready_Graphic_Device()))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Terrain/Tile/Tile%d.png", L"Terrain", L"Tile", 11)))
		return;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../TextureEtc/Map/Map%d.png", L"TextureEtc", L"Map", 5)))
		return;

	//UI
	//PLAYER STATUS
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../TextureEtc/Interface/PlayerStatus%d.png", L"UI", L"PlayerStatus", 1)))
		return;
	//HPBAR
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../TextureEtc/Interface/Status/HpBar%d.png", L"UI", L"HpBar", 1)))
		return;
	//MPBAR
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../TextureEtc/Interface/Status/MpBar%d.png", L"UI", L"MpBar", 1)))
		return;
	//SPBAR
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../TextureEtc/Interface/Status/SpBar%d.png", L"UI", L"SpBar", 1)))
		return;
	//QuickSlot
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../TextureEtc/Interface/UI/QuickSlot%d.png", L"UI", L"QuickSlot", 3)))
		return;
	//ICON
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../TextureEtc/Skill/ThunderBoltIcon%d.png", L"UI", L"ThunderBoltIcon", 1)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../TextureEtc/Skill/CoolTimeIcon%d.png", L"UI", L"CoolTimeIcon", 1)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../TextureEtc/Skill/ASBuffIcon%d.png", L"UI", L"ASBuffIcon", 1)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../TextureEtc/Skill/MultiAttackIcon%d.png", L"UI", L"MultiAttackIcon", 1)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../TextureEtc/Skill/ChainAttackIcon%d.png", L"UI", L"ChainAttackIcon", 1)))
		return;

	//Button
	//캐릭터
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../TextureEtc/Interface/Button/StatusBarUp%d.png", L"UI", L"StatusBarUp", 1)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../TextureEtc/Interface/Button/StatusBarDown%d.png", L"UI", L"StatusBarDown", 1)))
		return;
	//장비
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../TextureEtc/Interface/Button/EquipBarUp%d.png", L"UI", L"EquipBarUp", 1)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../TextureEtc/Interface/Button/EquipBarDown%d.png", L"UI", L"EquipBarDown", 1)))
		return;
	//인벤토리
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../TextureEtc/Interface/Button/InvenBarUp%d.png", L"UI", L"InvenBarUp", 1)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../TextureEtc/Interface/Button/InvenBarDown%d.png", L"UI", L"InvenBarDown", 1)))
		return;

	//상태창
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../TextureEtc/Interface/Status/StatusWindow%d.png", L"UI", L"StatusWindow", 1)))
		return;
	//플레이어
	//STAND
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/STAND_DOWN/STAND_DOWN%d.png", L"Player", L"STAND_DOWN", 10)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/STAND_LDOWN/STAND_LDOWN%d.png", L"Player", L"STAND_LDOWN", 10)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/STAND_LEFT/STAND_LEFT%d.png", L"Player", L"STAND_LEFT", 10)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/STAND_LUP/STAND_LUP%d.png", L"Player", L"STAND_LUP", 10)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/STAND_UP/STAND_UP%d.png", L"Player", L"STAND_UP", 10)))
		return;

	//RUN
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/RUN_DOWN/RUN_DOWN%d.png", L"Player", L"RUN_DOWN", 8)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/RUN_LDOWN/RUN_LDOWN%d.png", L"Player", L"RUN_LDOWN", 8)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/RUN_LEFT/RUN_LEFT%d.png", L"Player", L"RUN_LEFT", 8)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/RUN_LUP/RUN_LUP%d.png", L"Player", L"RUN_LUP", 8)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/RUN_UP/RUN_UP%d.png", L"Player", L"RUN_UP", 8)))
		return;

	//ATTACK
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/ATTACK1_DOWN/ATTACK1_DOWN%d.png", L"Player", L"ATTACK1_DOWN", 13)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/ATTACK1_LDOWN/ATTACK1_LDOWN%d.png", L"Player", L"ATTACK1_LDOWN", 13)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/ATTACK1_LEFT/ATTACK1_LEFT%d.png", L"Player", L"ATTACK1_LEFT", 13)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/ATTACK1_LUP/ATTACK1_LUP%d.png", L"Player", L"ATTACK1_LUP", 13)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/ATTACK1_UP/ATTACK1_UP%d.png", L"Player", L"ATTACK1_UP", 13)))
		return;

	//RANGE
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/ATTACK1_LEFT_RANGE/ATTACK1_LEFT_RANGE%d.png", L"Player", L"ATTACK1_UP_RANGE", 1)))
		return;
	//REST
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/REST_DOWN/REST_DOWN%d.png", L"Player", L"REST_DOWN", 1)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/REST_LDOWN/REST_LDOWN%d.png", L"Player", L"REST_LDOWN", 1)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/REST_LEFT/REST_LEFT%d.png", L"Player", L"REST_LEFT", 1)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/REST_LUP/REST_LUP%d.png", L"Player", L"REST_LUP", 1)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/REST_UP/REST_UP%d.png", L"Player", L"REST_UP", 1)))
		return;

	//EVOLUTION
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Stage/Player/EVOLUTION/Evolution0%d.png", L"Player", L"EVOLUTION", 11)))
		return;

	//마우스
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Mouse/Battle/Battle_%d.png", L"Mouse", L"Battle", 7)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Mouse/Click/Click%d.png", L"Mouse", L"Click", 2)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Mouse/Gate/Gate%d.png", L"Mouse", L"Gate", 4)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Mouse/Magic/%d.png", L"Mouse", L"Magic", 9)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Mouse/NoPass/NoPass_%d.png", L"Mouse", L"NoPass", 12)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Mouse/Normal/Normal_%d.png", L"Mouse", L"Normal", 13)))
		return;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Mouse/NpcCol/NpcCol%d.png", L"Mouse", L"NpcCol", 2)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Mouse/Pick/Pick%d.png", L"Mouse", L"Battle", 3)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Mouse/Target/Target%d.png", L"Mouse", L"Target", 4)))
		return;

	//포탈
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/WARPGATE/WarpGate/WarpGate%d.png", L"WARPGATE", L"WarpGate", 24)))
		return;


	//이펙트
	//데미지 폰트
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Effect/PlayerHNumber/%d.png", L"Effect", L"PlayerHNumber", 10)))
		return;

	//마법데미지폰트
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Effect/MagicDmgFont/MagicDmgFont%d.png", L"Effect", L"MagicDmgFont", 10)))
		return;

	//물리데미지폰트
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Effect/HitNumber/DmgFont%d.png", L"Effect", L"DmgFont", 10)))
		return;

	//크리티컬
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../TextureEtc/Critical/Critical%d.png", L"TextureEtc", L"Critical", 1)))
		return;

	//공격 스킬
	//썬더볼트
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Effect/ThunderBolt/Storm%d.png", L"Effect", L"ThunderBolt", 12)))
		return;

	//멀티어택
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Effect/MultiAttack/MultiAttack%d.png", L"Effect", L"MultiAttack", 41)))
		return;

	//체인어택
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Effect/ChainD/Chain%d.png", L"Effect", L"ChainD", 10)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Effect/ChainL/Chain%d.png", L"Effect", L"ChainL", 10)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Effect/ChainLD/Chain%d.png", L"Effect", L"ChainLD", 10)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Effect/ChainLU/Chain%d.png", L"Effect", L"ChainLU", 10)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Effect/ChainR/RChain%d.png", L"Effect", L"ChainR", 10)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Effect/ChainRD/RChain%d.png", L"Effect", L"ChainRD", 10)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Effect/ChainRU/RChain%d.png", L"Effect", L"ChainRU", 10)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Effect/ChainU/Chain%d.png", L"Effect", L"ChainU", 10)))
		return;


	//공격 이펙트
	//플레이어 공격
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Effect/PlayerHit/PlayerHit%d.png", L"Effect", L"PlayerHit", 4)))
		return;
	//몬스터공격
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Effect/MonsterHit/MonsterHit%d.png", L"Effect", L"MonsterHit", 4)))
		return;

	//마법공격
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Effect/MagicHit/MAgicHit%d.png", L"Effect", L"MagicHit", 4)))
		return;

	

	//몬스터
	//소환이펙트
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/Effect/Summon/Sumon%d.png", L"Effect", L"Summon", 3)))
		return;

	//BLUEWOLF
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/BlueWolf/STAND_LDOWN/Stand_LDown%d.png", L"BlueWolf", L"Stand_LDown", 6)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/BlueWolf/STAND_LUP/Stand_LUp%d.png", L"BlueWolf", L"Stand_LUp", 6)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/BlueWolf/ATT_LDOWN/Attack_LDown%d.png", L"BlueWolf", L"Attack_LDown", 8)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/BlueWolf/ATT_LUP/Attack_LUp%d.png", L"BlueWolf", L"Attack_LUp", 8)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/BlueWolf/WALK_LDOWN/Walk_LDown%d.png", L"BlueWolf", L"Walk_LDown", 6)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/BlueWolf/WALK_LUP/Walk_LUp%d.png", L"BlueWolf", L"Walk_LUp", 6)))
		return;


	//DARKCOW
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/DarkCow/STAND_LDOWN/Stand_LDown%d.png", L"DarkCow", L"Stand_LDown", 6)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/DarkCow/STAND_LUP/Stand_LUp%d.png", L"DarkCow", L"Stand_LUp", 6)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/DarkCow/ATT_LDOWN/Attack_LDown%d.png", L"DarkCow", L"Attack_LDown", 10)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/DarkCow/ATT_LUP/Attack_LUp%d.png", L"DarkCow", L"Attack_LUp", 10)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/DarkCow/WALK_LDOWN/Walk_LDown%d.png", L"DarkCow", L"Walk_LDown", 8)))
		return;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::TEX_MULTI, L"../Texture/DarkCow/WALK_LUP/Walk_LUp%d.png", L"DarkCow", L"Walk_LUp", 8)))
		return;

	CScene_Manager::Get_Instance()->Change_Scene(CScene_Manager::SCENE_TUTORIAL);

}

void CMainApp::Update_MainApp()
{
	m_pTime_Manager->Update_TimeManager();
	CScene_Manager::Get_Instance()->Update_Scene();
	CKey_Manager::Get_Instance()->Update_KeyManager();
}

void CMainApp::Late_Update_MainApp()
{
	CScene_Manager::Get_Instance()->LateUpdate_Scene();
}

void CMainApp::Render_MainApp(CFrame_Manager* pFrameManager)
{
	m_pGraphic_Device->Render_Begin();
	CScene_Manager::Get_Instance()->Render_Scene();
	pFrameManager->Render_FrameManager();
	m_pGraphic_Device->Render_End();
}

void CMainApp::Release_MainApp()
{
	CAStar::Destroy_Instance();
	m_pTime_Manager->Destroy_Instance();
	CGameObject_Manager::Destroy_Instance();
	CScene_Manager::Destroy_Instance();
	CTexture_Manager::Destroy_Instance();
	m_pGraphic_Device->Destroy_Instance();
	CSoundMgr::Destroy_Instance();
}
