#pragma once
#include "afxwin.h"


// FormContactDetail 对话框

class FormContactDetail : public CDialog
{
	DECLARE_DYNAMIC(FormContactDetail)

public:
	FormContactDetail(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~FormContactDetail();

// 对话框数据
	enum { IDD = IDD_FORMCONTACTDETAIL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	int txtId;
	CString txtName;
	CString txtPhone;
	CString txtEmail;
	CString txtWorkUnit;
	CString txtOfficePhone;
	CString txtHomePhone;
	CString txtHomeAddress;
	CString txtQQ;
	//CComboBox cboGroup;
	CString txtMemo;
	afx_msg void OnBnClickedOk();
private:
	_RecordsetPtr   m_ptrRecordset;     //记录集对象  
	_ConnectionPtr  m_ptrConnection;    //数据库对象  
};
