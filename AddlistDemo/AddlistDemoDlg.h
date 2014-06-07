
// AddlistDemoDlg.h : 头文件
//

#pragma once
#include "AddlistDemo.h"

// CAddlistDemoDlg 对话框
class CAddlistDemoDlg : public CDialog
{
// 构造
public:
// 	CString m_useName;
// 	CString m_password;

	CAddlistDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ADDLISTDEMO_DIALOG };
	
	_RecordsetPtr   m_ptrRecordset;     //记录集对象  
	_ConnectionPtr  m_ptrConnection;    //数据库对象  
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
//	afx_msg void OnEnChangeEdit1();
	CString userName;
	CString Password;
	afx_msg void OnBnClickedButton3();
};
