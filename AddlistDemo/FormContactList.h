#pragma once
#include "mylistctrl.h"
#include "afxwin.h"


// FormContactList 对话框

class FormContactList : public CDialog
{
	DECLARE_DYNAMIC(FormContactList)

public:
	FormContactList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~FormContactList();
    virtual  BOOL  OnInitDialog();
// 对话框数据
	enum { IDD  = IDD_FORMCONTACTLIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnBnClickedButton1();
	CMyListCtrl dgvContactList;
	void Fill();
	CComboBox cboCondition;
	CString txtSearch;

private:
	_RecordsetPtr   m_ptrRecordset;     //记录集对象  
	_ConnectionPtr  m_ptrConnection;    //数据库对象  
	int id;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBtnDelete();
	afx_msg void OnBnClickedOk();
};
