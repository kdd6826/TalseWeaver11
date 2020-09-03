#pragma once
#include "afxwin.h"


// CUnitTool ��ȭ �����Դϴ�.

class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

public:
	CUnitTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CUnitTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedPush();
	// ����� ������ΰ�?��������������
	CString m_strData1;
	CString m_strData2;

	// UnitData
	CString m_strName;
	int m_iAtt;
	int m_iDef;
	CListBox m_ListBox;
	map<CString, UNITINFO*> m_mapUnitData; 

	afx_msg void OnBnClickedAddUnitData();
	afx_msg void OnLbnSelChangeClass();
	CButton m_JopIndex[3];
	CButton m_CheckBox[3];
	virtual BOOL OnInitDialog();
	
	afx_msg void OnBnClickedDelect();
	afx_msg void OnEnChangeFindName();
	CString m_strFindName;
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();
};
