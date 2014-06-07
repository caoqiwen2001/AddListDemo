#pragma once


// AddListGropDetail 对话框

class AddListGropDetail : public CDialog
{
	DECLARE_DYNAMIC(AddListGropDetail)

public:
	AddListGropDetail(CWnd* pParent = NULL);   // 标准构造函数
   // AddListGropDetail(CWnd* pParent,CString  id);    //如果第一个参数是缺省的，那么第二个参数也必须是缺省的。shit
	virtual ~AddListGropDetail();
	virtual    BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString txtId;
	CString txtGroupName;
	CString txtGroupMemo;
private:
	//int Id;   //传递选中的编号。
	//CString  Id;
	_RecordsetPtr   m_ptrRecordset;     //记录集对象  
	_ConnectionPtr  m_ptrConnection;    //数据库对象  

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
private:
   BOOL checkGroupName(CString  groupName);
public:
	//afx_msg void On32772();
};
