#pragma once
#include "afxcmn.h"
#include "MyListCtrl.h"
#include "afxwin.h"

// AddListGropList �Ի���

class AddListGropList : public CDialog
{
	DECLARE_DYNAMIC(AddListGropList)

public:
	AddListGropList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AddListGropList();
	virtual  BOOL  OnInitDialog();
	

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//CListCtrl m_ListCtrl;
	
	void  Fill();
	void Delete();
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CMyListCtrl  m_CListCtrl;
//	afx_msg UINT OnNotifyFormat(CWnd *pWnd, UINT nCommand);
private:
	_RecordsetPtr   m_ptrRecordset1;     //��¼������  
	_ConnectionPtr  m_ptrConnection1;    //���ݿ����  
public:
	afx_msg void OnBnClickedButton1();
//	afx_msg void OnBnClickedButton2();
	CButton btn_Delete;
//	afx_msg void OnBnClickedButton2();
	afx_msg void btnDelete();
private:
	int id;     //���ѡ���к�
public:
	afx_msg void OnBnClickedButton3();
};