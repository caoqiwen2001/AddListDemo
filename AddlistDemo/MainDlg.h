#pragma once


// MainDlg �Ի���
#include "AddlistDemo.h"
class MainDlg : public CDialog
{
	DECLARE_DYNAMIC(MainDlg)

public:
	MainDlg(CWnd* pParent = NULL);   // ��׼���캯��

	virtual BOOL OnInitDialog();
	virtual ~MainDlg();
	CMenu  menu;

// �Ի�������
	
	enum {IDD=IDD_DIALOG1};
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	//afx_msg void On32774();
	afx_msg void OnGroplist();
//	afx_msg void OnBnClicked2();
	afx_msg void OnPaint();
	afx_msg void On32772();
};
