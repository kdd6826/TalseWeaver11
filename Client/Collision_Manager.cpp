#include "stdafx.h"
#include "GameObject.h"
#include "Player.h"
#include "Monster.h"
#include "Collision_Manager.h"

CCollisionManager::CCollisionManager() {
}

CCollisionManager::~CCollisionManager() {
}

void CCollisionManager::CollisionRect(list<CGameObject*>& rDstList, list<CGameObject*>& rSrcList) {
	RECT rc = {};
	for (auto DstObj : rDstList) {
		for (auto SrCGameObject : rSrcList) {
			if (IntersectRect(&rc, DstObj->GetRect(), SrCGameObject->GetRect())) {
				DstObj->OnCollision(SrCGameObject);
				SrCGameObject->OnCollision(DstObj);
			}
		}
	}
}

void CCollisionManager::CollisionSphere(list<CGameObject*>& rDstList, list<CGameObject*>& rSrcList) {

	for (auto DstObj : rDstList) {
		for (auto SrCGameObject : rSrcList) {
			if (CheckSphere(DstObj, SrCGameObject)) {
				DstObj->OnCollision(SrCGameObject);
				SrCGameObject->OnCollision(DstObj);
			}
		}
	}
}

bool CCollisionManager::CheckSphere(CGameObject* rDstObj, CGameObject* rSrCGameObject) {
	

		float fRadiusSum = (rDstObj->GetInfo()->vRealSize.x / 2) + (rSrCGameObject->GetInfo()->vRealSize.x / 2);
		float fX = rDstObj->GetInfo()->vPos.x - rSrCGameObject->GetInfo()->vPos.x;
		float fY = rDstObj->GetInfo()->vPos.y - rSrCGameObject->GetInfo()->vPos.y;
		float fDist = sqrtf(fX * fX + fY * fY);
		return fDist < fRadiusSum;
}
void CCollisionManager::CollisionRectEX(list<CGameObject*>& rDstList, list<CGameObject*>& rSrcList) {
	float fMoveX = 0.f, fMoveY = 0.f;
	for (auto& rDstObject : rDstList) {
		BOOL isCollsion = false;
		for (auto& rSrCGameObjectect : rSrcList) {
			if (CheckRect(rDstObject, *rSrCGameObjectect, &fMoveX, &fMoveY)) {
				float fX = rDstObject->GetInfo()->vPos.x;
				float fY = rDstObject->GetInfo()->vPos.y;
				isCollsion = true;
				if (fMoveX > fMoveY) {
					if (fY < rSrCGameObjectect->GetInfo()->vPos.y)
						fMoveY *= -1.f;
					rDstObject->SetPos(_vec3 {fX,fY+fMoveY,0.f});
					switch (rDstObject->GetObjId()) {
					case OBJ::OBJ_MONSTER: {
						CMonster* tempMonster = dynamic_cast<CMonster*>(rDstObject);
						if (tempMonster)
							/*tempMonster->SetIsJump(false);*/

						break;
					}
					case OBJ::OBJ_PLAYER: {
						CPlayer* tempPlayer = dynamic_cast<CPlayer*>(rDstObject);
						if (tempPlayer)
						{
							/*tempPlayer->SetIsJump(false);*/

						}
						break;
					}
					default:
						break;
					}
				}
				else {
					//if (fX < rSrCGameObjectect->GetInfo()->fX)
					//	fMoveX *= -1.f;
					rDstObject->SetPos(_vec3{ fX+ fMoveX,fY ,0.f });
				}

			}
		}
		if (!isCollsion) {
			switch (rDstObject->GetObjId()) {
			case OBJ::OBJ_MONSTER: {
				CMonster* tempMonster = dynamic_cast<CMonster*>(rDstObject);
				if (tempMonster)
			/*		tempMonster->SetIsJump(true);*/
				break;
			}
			case OBJ::OBJ_PLAYER: {
				CPlayer* tempPlayer = dynamic_cast<CPlayer*>(rDstObject);
				if (tempPlayer)
					/*tempPlayer->SetIsJump(true);*/
				break;
			}

			default:
				break;
			}
		}
	}

}

void CCollisionManager::CollisionRectCeiling(list<CGameObject*>& rDstList, list<CGameObject*>& rSrcList)
{
	float fMoveX = 0.f, fMoveY = 0.f;
	for (auto& rDstObject : rDstList) {
		BOOL isCollsion = false;
		for (auto& rSrCGameObjectect : rSrcList) {
			if (CheckRect(rDstObject, *rSrCGameObjectect, &fMoveX, &fMoveY)) {
				float fX = rDstObject->GetInfo()->vPos.x;
				float fY = rDstObject->GetInfo()->vPos.y;
				isCollsion = true;
				if (fMoveX > fMoveY) {
					if (fY < rSrCGameObjectect->GetInfo()->vPos.y)
						fMoveY *= -1.f;
					rDstObject->SetPos(_vec3{ fX, fY + fMoveY ,0.f});
					switch (rDstObject->GetObjId()) {
					case OBJ::OBJ_MONSTER: {
						CMonster* tempMonster = dynamic_cast<CMonster*>(rDstObject);
						if (tempMonster)
						{
						}

						break;
					}
					case OBJ::OBJ_PLAYER: {
						CPlayer* tempPlayer = dynamic_cast<CPlayer*>(rDstObject);
						if (tempPlayer)
						{


						}
						break;
					}

					default:
						break;
					}
				}
				else {
					if (fX < rSrCGameObjectect->GetInfo()->vPos.x)
						fMoveX *= -1.f;
					rDstObject->SetPos(_vec3{ fX + fMoveX, fY,0.f });
				}

			}
		}
		if (!isCollsion) {
			switch (rDstObject->GetObjId()) {
			case OBJ::OBJ_MONSTER: {
				CMonster* tempMonster = dynamic_cast<CMonster*>(rDstObject);
				if (tempMonster)
					
				break;
			}
			case OBJ::OBJ_PLAYER: {
				CPlayer* tempPlayer = dynamic_cast<CPlayer*>(rDstObject);
				if (tempPlayer)
					
				break;
			}
			
			default:
				break;
			}
		}
	}
}

bool CCollisionManager::CheckRect(CGameObject* pDstObject, CGameObject& rSrCGameObjectect, float* pMoveX, float* pMoveY) {
	float fRadiusSumX = static_cast<float>((pDstObject->GetTexInfo()->tImageInfo.Width/2) + (rSrCGameObjectect.GetTexInfo()->tImageInfo.Width/2));
	float fRadiusSumY = static_cast<float>((pDstObject->GetTexInfo()->tImageInfo.Height/2) + (rSrCGameObjectect.GetTexInfo()->tImageInfo.Height/2));

	float fDistX = fabsf(pDstObject->GetInfo()->vPos.x - rSrCGameObjectect.GetInfo()->vPos.x);
	float fDistY = fabsf(pDstObject->GetInfo()->vPos.y - rSrCGameObjectect.GetInfo()->vPos.y);

	if (fDistX <= fRadiusSumX && fDistY <= fRadiusSumY) {
		*pMoveX = fRadiusSumX - fDistX;
		*pMoveY = fRadiusSumY - fDistY;
		return true;
	}
	// 두개의 거리가 더 짧다라면 ? 충돌. 
	return false;
}