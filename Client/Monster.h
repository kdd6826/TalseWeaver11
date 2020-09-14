#pragma once
#include "GameObject.h"
class CMonster :
    public CGameObject
{
public:
    CMonster();
    CMonster(float _forceX, float _forceY);
    virtual ~CMonster();
public:

    // CGameObject��(��) ���� ��ӵ�
    virtual HRESULT Ready_GameObject() override;
    virtual int Update_GameObject() override;
    virtual void LateUpdate_GameObject() override;
    virtual void Render_GameObject() override;
    virtual void Release_GameObject() override;
    virtual void OnCollision(CGameObject* _TargetObj) override;
public:
    static CGameObject* Create(LPVOID* pArg = nullptr);
protected:


    // CGameObject��(��) ���� ��ӵ�
 
};

