#pragma once


// AddlistGroupAdd �Ի���
#include<afxdb.h>
class AddlistGroupAdd : public CDialog
{
	DECLARE_DYNAMIC(AddlistGroupAdd)

public:
	AddlistGroupAdd(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AddlistGroupAdd();

// �Ի�������
	enum { IDD = IDD_ADDLISTGROUPADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClicked2();
	
	
private:
	CString lblGroupName;
	CString lblGroupMemo;
   
	_RecordsetPtr   m_ptrRecordset;     //��¼������  
	_ConnectionPtr  m_ptrConnection;    //���ݿ����  
	//�����ж������Ƿ�Ϊ��
	bool CheckGroupName(CString groupName);

	_RecordsetPtr   m_ptrRecordset1;     //��¼������  
	_ConnectionPtr  m_ptrConnection1;    //���ݿ����  
};
