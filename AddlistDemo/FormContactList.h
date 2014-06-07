#pragma once
#include "mylistctrl.h"
#include "afxwin.h"


// FormContactList �Ի���

class FormContactList : public CDialog
{
	DECLARE_DYNAMIC(FormContactList)

public:
	FormContactList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~FormContactList();
    virtual  BOOL  OnInitDialog();
// �Ի�������
	enum { IDD  = IDD_FORMCONTACTLIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnBnClickedButton1();
	CMyListCtrl dgvContactList;
	void Fill();
	CComboBox cboCondition;
	CString txtSearch;

private:
	_RecordsetPtr   m_ptrRecordset;     //��¼������  
	_ConnectionPtr  m_ptrConnection;    //���ݿ����  
	int id;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBtnDelete();
	afx_msg void OnBnClickedOk();
};
