#pragma once
#include "afxwin.h"


// FormContactAdd 对话框

class FormContactAdd : public CDialog
{
	DECLARE_DYNAMIC(FormContactAdd)

public:
	FormContactAdd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~FormContactAdd();
	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_FORMCONTACTADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString txtName;
	CString txtPhone;
	CString txtQQ;
	CString txtEmail;
	CString txtWorkUnit;
	CString txtOfficePhone;
	CString txtHomePhone;
	CString txtHomeAddress;
	CComboBox cboGroup;
	CString txtMemo;
private:
	_RecordsetPtr   m_ptrRecordset;     //记录集对象  
	_ConnectionPtr  m_ptrConnection;    //数据库对象  
public:
	afx_msg void OnBnClickedOk();
};
