#pragma once
class CGraphic_Device
{
DECLARE_SINGLETON(CGraphic_Device)
private:
	CGraphic_Device();
	~CGraphic_Device();
public:
	LPDIRECT3DDEVICE9 Get_Device() { return m_pDevice;  }
	LPD3DXSPRITE Get_Sprite() { return m_pSprite; }
	LPD3DXFONT Get_Font() { return m_pFont; }
public:
	HRESULT Ready_Graphic_Device();
public:
	void Render_Begin(); 
	void Render_End(HWND hWnd = nullptr); 

public:
	void Release_Graphic_Device(); 
private:
	// ���������� ��ġ�� �ٷ� ��ü. 
	LPDIRECT3DDEVICE9 m_pDevice;
	// ��ġ�� ���� ���� ���� �� ��ġ�� ������ ��ü�� ������ com ��ü .
	LPDIRECT3D9 m_pSDK; 
	// com ��ü!- �׳� �ϳ� �ϳ� ��ǰó�� �����Ѵٶ� �����ϸ� �ǰڴ�. 

	LPD3DXSPRITE m_pSprite;
	LPD3DXFONT	m_pFont; 

};

