#pragma once
#include "Texture.h"
class CMultiTex final :
	public CTexture
{
public:
	explicit CMultiTex();
	virtual ~CMultiTex();
public:
	// CTexture��(��) ���� ��ӵ�
	virtual HRESULT Insert_Texture(const wstring & wstrFilePath, const wstring & wstrStateKey = L"", const DWORD & rCount = 0) override;
	virtual const TEXINFO * Get_Texture(const wstring & wstrStateKey = L"", const DWORD & rIndex = 0) override;
	virtual void Release_Texture() override;

private:
	// StateKey 
	// �ϳ��� STateKey(�ൿ)�� �������� �׸��� �� �� �ֱ� ����. 
	// ���� ��� �����̶� StateKey ���� 20���� �׸��� �ְ� 
	//���� �ε����� ������ �������� ��ġ �ִϸ��̼� ���ư��� ��� �� ��. 
	map<wstring, vector<TEXINFO*>> m_mapMultiTex; 
};

