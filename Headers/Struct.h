#pragma once
#include "Enum.h"
typedef struct tagInfo
{
	TCHAR chName[32];
	D3DXVECTOR3 vPos;  // ��ġ���� 
	D3DXVECTOR3 vDir; // ���⺤�� 
	D3DXVECTOR3 vSize; // ũ�� ǥ���� ��. 
	D3DXVECTOR3 vRealSize; // ���� ũ�� ǥ���� ��. 
	D3DXVECTOR3 vFirstPos; // �� ��� ��ġ
	D3DXVECTOR3 vLook;
	D3DXMATRIX mat;
}INFO;


typedef struct tagTexture
{
	LPDIRECT3DTEXTURE9 pTexture; // �̹��� ������ �����ϱ� ���� �İ�ü. 
	D3DXIMAGE_INFO tImageInfo; //�̹����� ������ ��Ƶ� ����ü. 
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