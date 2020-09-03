#pragma once
class CScroll_Manager
{
public:
	enum SCROLL {X, Y};

private:
	CScroll_Manager();
	~CScroll_Manager();
public:
	static _vec3 Get_Scroll() { return m_vScroll; }
	static float Get_Scroll(SCROLL eScroll);
public:
	static void Set_Scroll(const _vec3& vScroll) { m_vScroll += vScroll; }
	static void Scroll_Lock(_vec3 Size);
private:
	static _vec3 m_vScroll;
};

