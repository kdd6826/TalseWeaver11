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

void CCollisionManager::CollisionAbsorb(list<CGameObject*>& rDstList, list<CGameObject*>& rSrcList)
{
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
	float fRadiusSum = static_cast<float>((rDstObj->GetInfo()->iCX >> 1) + (rSrCGameObject->GetInfo()->iCX >> 1));
	float fX = rDstObj->GetInfo()->fX - rSrCGameObject->GetInfo()->fX;
	float fY = rDstObj->GetInfo()->fY - rSrCGameObject->GetInfo()->fY;
	float fDist = sqrtf(fX * fX + fY * fY);
	return fDist < fRadiusSum;
}
void CCollisionManager::CollisionRectEX(list<CGameObject*>& rDstList, list<CGameObject*>& rSrcList) {
	float fMoveX = 0.f, fMoveY = 0.f;
	for (auto& rDstObject : rDstList) {
		BOOL isCollsion = false;
		for (auto& rSrCGameObjectect : rSrcList) {
			if (CheckRect(rDstObject, *rSrCGameObjectect, &fMoveX, &fMoveY)) {
				float fX = rDstObject->GetInfo()->fX;
				float fY = rDstObject->GetInfo()->fY;
				isCollsion = true;
				if (fMoveX > fMoveY) {
					if (fY < rSrCGameObjectect->GetInfo()->fY)
						fMoveY *= -1.f;
					rDstObject->SetPos(fX, fY + fMoveY);
					switch (rDstObject->GetObjId()) {
					case OBJ::MONSTER: {
						CMonster* tempMonster = dynamic_cast<CMonster*>(rDstObject);
						if (tempMonster)
							tempMonster->SetIsJump(false);

						break;
					}
					case OBJ::PLAYER: {
						CPlayer* tempPlayer = dynamic_cast<CPlayer*>(rDstObject);
						if (tempPlayer)
						{
							tempPlayer->SetIsJump(false);

						}
						break;
					}
					case OBJ::ITEM: {
						CItem* tempItem = dynamic_cast<CItem*>(rDstObject);
						if (tempItem)
							tempItem->SetIsJump(false);
						break;
					}
					default:
						break;
					}
				}
				else {
					if (fX < rSrCGameObjectect->GetInfo()->fX)
						fMoveX *= -1.f;
					rDstObject->SetPos(fX + fMoveX, fY);
				}

			}
		}
		if (!isCollsion) {
			switch (rDstObject->GetObjId()) {
			case OBJ::MONSTER: {
				CMonster* tempMonster = dynamic_cast<CMonster*>(rDstObject);
				if (tempMonster)
					tempMonster->SetIsJump(true);
				break;
			}
			case OBJ::PLAYER: {
				CPlayer* tempPlayer = dynamic_cast<CPlayer*>(rDstObject);
				if (tempPlayer)
					tempPlayer->SetIsJump(true);
				break;
			}
			case OBJ::ITEM: {
				CItem* tempItem = dynamic_cast<CItem*>(rDstObject);
				if (tempItem)
					tempItem->SetIsJump(true);
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
				float fX = rDstObject->GetInfo()->fX;
				float fY = rDstObject->GetInfo()->fY;
				isCollsion = true;
				if (fMoveX > fMoveY) {
					if (fY < rSrCGameObjectect->GetInfo()->fY)
						fMoveY *= -1.f;
					rDstObject->SetPos(fX, fY + fMoveY);
					switch (rDstObject->GetObjId()) {
					case OBJ::MONSTER: {
						CMonster* tempMonster = dynamic_cast<CMonster*>(rDstObject);
						if (tempMonster)
						{
						}

						break;
					}
					case OBJ::PLAYER: {
						CPlayer* tempPlayer = dynamic_cast<CPlayer*>(rDstObject);
						if (tempPlayer)
						{


						}
						break;
					}
					case OBJ::ITEM: {
						CItem* tempItem = dynamic_cast<CItem*>(rDstObject);
						if (tempItem)

							break;
					}
					default:
						break;
					}
				}
				else {
					if (fX < rSrCGameObjectect->GetInfo()->fX)
						fMoveX *= -1.f;
					rDstObject->SetPos(fX + fMoveX, fY);
				}

			}
		}
		if (!isCollsion) {
			switch (rDstObject->GetObjId()) {
			case OBJ::MONSTER: {
				CMonster* tempMonster = dynamic_cast<CMonster*>(rDstObject);
				if (tempMonster)
					tempMonster->SetIsJump(true);
				break;
			}
			case OBJ::PLAYER: {
				CPlayer* tempPlayer = dynamic_cast<CPlayer*>(rDstObject);
				if (tempPlayer)
					tempPlayer->SetIsJump(true);
				break;
			}
			case OBJ::ITEM: {
				CItem* tempItem = dynamic_cast<CItem*>(rDstObject);
				if (tempItem)
					tempItem->SetIsJump(true);
				break;
			}
			default:
				break;
			}
		}
	}
}

bool CCollisionManager::CheckRect(CGameObject* pDstObject, CGameObject& rSrCGameObjectect, float* pMoveX, float* pMoveY) {
	float fRadiusSumX = static_cast<float>((pDstObject->GetInfo()->iCX >> 1) + (rSrCGameObjectect.GetInfo()->iCX >> 1));
	float fRadiusSumY = static_cast<float>((pDstObject->GetInfo()->iCY >> 1) + (rSrCGameObjectect.GetInfo()->iCY >> 1));

	float fDistX = fabsf(pDstObject->GetInfo()->fX - rSrCGameObjectect.GetInfo()->fX);
	float fDistY = fabsf(pDstObject->GetInfo()->fY - rSrCGameObjectect.GetInfo()->fY);

	if (fDistX <= fRadiusSumX && fDistY <= fRadiusSumY) {
		*pMoveX = fRadiusSumX - fDistX;
		*pMoveY = fRadiusSumY - fDistY;
		return true;
	}
	// 두개의 거리가 더 짧다라면 ? 충돌. 
	return false;
}
