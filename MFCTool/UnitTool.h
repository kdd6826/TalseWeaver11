#pragma once
#include "afxwin.h"


// CUnitTool 企鉢 雌切脊艦陥.

class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

public:
	CUnitTool(CWnd* pParent = NULL);   // 妊層 持失切脊艦陥.
	virtual ~CUnitTool();

// 企鉢 雌切 汽戚斗脊艦陥.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 走据脊艦陥.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedPush();
	// 仙幾精 嬢恐神軒昔亜?せせせせせせせ
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
