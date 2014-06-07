#pragma once


// MainDlg 对话框
#include "AddlistDemo.h"
class MainDlg : public CDialog
{
	DECLARE_DYNAMIC(MainDlg)

public:
	MainDlg(CWnd* pParent = NULL);   // 标准构造函数

	virtual BOOL OnInitDialog();
	virtual ~MainDlg();
	CMenu  menu;

// 对话框数据
	
	enum {IDD=IDD_DIALOG1};
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	//afx_msg void On32774();
	afx_msg void OnGroplist();
//	afx_msg void OnBnClicked2();
	afx_msg void OnPaint();
	afx_msg void On32772();
};
