#pragma once


// AddlistGroupAdd 对话框
#include<afxdb.h>
class AddlistGroupAdd : public CDialog
{
	DECLARE_DYNAMIC(AddlistGroupAdd)

public:
	AddlistGroupAdd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AddlistGroupAdd();

// 对话框数据
	enum { IDD = IDD_ADDLISTGROUPADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClicked2();
	
	
private:
	CString lblGroupName;
	CString lblGroupMemo;
   
	_RecordsetPtr   m_ptrRecordset;     //记录集对象  
	_ConnectionPtr  m_ptrConnection;    //数据库对象  
	//用来判断输入是否为空
	bool CheckGroupName(CString groupName);

	_RecordsetPtr   m_ptrRecordset1;     //记录集对象  
	_ConnectionPtr  m_ptrConnection1;    //数据库对象  
};
