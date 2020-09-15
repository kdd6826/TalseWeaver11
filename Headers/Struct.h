#pragma once
#include "Enum.h"
typedef struct tagInfo
{
	TCHAR chName[32];
	D3DXVECTOR3 vPos;  // 위치벡터 
	D3DXVECTOR3 vDir; // 방향벡터 
	D3DXVECTOR3 vSize; // 크기 표현할 놈. 
	D3DXVECTOR3 vRealSize; // 실제 크기 표현할 놈. 
	D3DXVECTOR3 vFirstPos; // 젠 당시 위치
	D3DXVECTOR3 vLook;
	D3DXMATRIX mat;
}INFO;


typedef struct tagTexture
{
	LPDIRECT3DTEXTURE9 pTexture; // 이미지 한장을 제어하기 위한 컴객체. 
	D3DXIMAGE_INFO tImageInfo; //이미지의 정보를 담아둘 구조체. 
}TEXINFO;

typedef struct tagTile
{
	_vec3	vPos;
	_vec3	vSize;
	_int	iIndex;
	_int	iParentIndex;
	_uint	iDrawID;
	_int	iOption;
}TILE;

typedef struct tagUnitInfo
{
#ifdef _AFX
	CString strName;
#else
	wstring wstrName;
#endif
	int		iAtt;
	int		iDef;
	BYTE	byJopIndex;
	BYTE	byItem;
}UNITINFO;

typedef struct tagFrame
{
	_float fFrameStart;
	_float fFrameEnd;
}FRAME;

typedef struct tagMonster {
	tagMonster(MONSTER::ID _monster, _vec3 _pos, DWORD _timer) : monster(_monster), pos(_pos), timer(_timer) {}
	MONSTER::ID monster;
	_vec3 pos;
	DWORD timer;
}MONSTERDATA;