#pragma once


// AddListGropDetail �Ի���

class AddListGropDetail : public CDialog
{
	DECLARE_DYNAMIC(AddListGropDetail)

public:
	AddListGropDetail(CWnd* pParent = NULL);   // ��׼���캯��
   // AddListGropDetail(CWnd* pParent,CString  id);    //�����һ��������ȱʡ�ģ���ô�ڶ�������Ҳ������ȱʡ�ġ�shit
	virtual ~AddListGropDetail();
	virtual    BOOL OnInitDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString txtId;
	CString txtGroupName;
	CString txtGroupMemo;
private:
	//int Id;   //����ѡ�еı�š�
	//CString  Id;
	_RecordsetPtr   m_ptrRecordset;     //��¼������  
	_ConnectionPtr  m_ptrConnection;    //���ݿ����  

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
private:
   BOOL checkGroupName(CString  groupName);
public:
	//afx_msg void On32772();
};
