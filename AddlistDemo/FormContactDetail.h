#pragma once
#include "afxwin.h"


// FormContactDetail �Ի���

class FormContactDetail : public CDialog
{
	DECLARE_DYNAMIC(FormContactDetail)

public:
	FormContactDetail(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~FormContactDetail();

// �Ի�������
	enum { IDD = IDD_FORMCONTACTDETAIL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
	_RecordsetPtr   m_ptrRecordset;     //��¼������  
	_ConnectionPtr  m_ptrConnection;    //���ݿ����  
};
