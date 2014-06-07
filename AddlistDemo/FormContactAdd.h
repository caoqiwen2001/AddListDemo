#pragma once
#include "afxwin.h"


// FormContactAdd �Ի���

class FormContactAdd : public CDialog
{
	DECLARE_DYNAMIC(FormContactAdd)

public:
	FormContactAdd(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~FormContactAdd();
	virtual BOOL OnInitDialog();

// �Ի�������
	enum { IDD = IDD_FORMCONTACTADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	_RecordsetPtr   m_ptrRecordset;     //��¼������  
	_ConnectionPtr  m_ptrConnection;    //���ݿ����  
public:
	afx_msg void OnBnClickedOk();
};
