
// AddlistDemoDlg.h : ͷ�ļ�
//

#pragma once
#include "AddlistDemo.h"

// CAddlistDemoDlg �Ի���
class CAddlistDemoDlg : public CDialog
{
// ����
public:
// 	CString m_useName;
// 	CString m_password;

	CAddlistDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ADDLISTDEMO_DIALOG };
	
	_RecordsetPtr   m_ptrRecordset;     //��¼������  
	_ConnectionPtr  m_ptrConnection;    //���ݿ����  
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
