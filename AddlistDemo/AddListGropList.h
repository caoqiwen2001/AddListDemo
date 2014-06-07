#pragma once
#include "afxcmn.h"
#include "MyListCtrl.h"
#include "afxwin.h"

// AddListGropList 对话框

class AddListGropList : public CDialog
{
	DECLARE_DYNAMIC(AddListGropList)

public:
	AddListGropList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AddListGropList();
	virtual  BOOL  OnInitDialog();
	

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//CListCtrl m_ListCtrl;
	
	void  Fill();
	void Delete();
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CMyListCtrl  m_CListCtrl;
//	afx_msg UINT OnNotifyFormat(CWnd *pWnd, UINT nCommand);
private:
	_RecordsetPtr   m_ptrRecordset1;     //记录集对象  
	_ConnectionPtr  m_ptrConnection1;    //数据库对象  
public:
	afx_msg void OnBnClickedButton1();
//	afx_msg void OnBnClickedButton2();
	CButton btn_Delete;
//	afx_msg void OnBnClickedButton2();
	afx_msg void btnDelete();
private:
	int id;     //获得选择行号
public:
	afx_msg void OnBnClickedButton3();
};