// AddlistGroupAdd.cpp : 实现文件
//

#include "stdafx.h"
#include "AddlistDemo.h"
#include "AddlistGroupAdd.h"


// AddlistGroupAdd 对话框

IMPLEMENT_DYNAMIC(AddlistGroupAdd, CDialog)

AddlistGroupAdd::AddlistGroupAdd(CWnd* pParent /*=NULL*/)
: CDialog(AddlistGroupAdd::IDD, pParent)
, lblGroupName(_T(""))
, lblGroupMemo(_T(""))
{
	CoInitialize(NULL);
	m_ptrRecordset1.CreateInstance(__uuidof(Recordset));  
	m_ptrConnection1.CreateInstance(__uuidof(Connection));  
	m_ptrConnection1->ConnectionString=_T("provider=Microsoft.Jet.OLEDB.4.0;Data Source=caoqiwen.mdb;");
}

AddlistGroupAdd::~AddlistGroupAdd()
{
}

void AddlistGroupAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, lblGroupName);
	DDX_Text(pDX, IDC_EDIT2, lblGroupMemo);
}


BEGIN_MESSAGE_MAP(AddlistGroupAdd, CDialog)
	ON_BN_CLICKED(IDOK, &AddlistGroupAdd::OnBnClickedOk)
	ON_BN_CLICKED(2, &AddlistGroupAdd::OnBnClicked2)
END_MESSAGE_MAP()


// AddlistGroupAdd 消息处理程序

void AddlistGroupAdd::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	variant_t vRecordsAffected ;
	UpdateData(TRUE);
	CString  groupName=lblGroupName; 
	CString memo=lblGroupMemo;
	try
	{
        if (!CheckGroupName(groupName))
		{
			return ;
		}
	}
	catch(_com_error ex)
	{
		AfxMessageBox(ex.Description());
	}
     try
	{
		m_ptrConnection1->Open("","","", adConnectUnspecified);
		CString  Sql;
		Sql.Format(_T("insert into ContactGroup([GropName],[MeMo]) Values(\'%s\',\'%s\')"),groupName,memo);
		m_ptrRecordset1=m_ptrConnection1->Execute((_bstr_t)Sql, &vRecordsAffected, adCmdText);

	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}

	if(vRecordsAffected.lVal>0)
	{
		AfxMessageBox(_T("添加分组成功"));
	}

	if (m_ptrRecordset1->State!=adStateClosed)
	{
		m_ptrRecordset1->Close();
	}

	if (m_ptrConnection1->State!=adStateClosed)
	{
		m_ptrConnection1->Close();
	}
	EndDialog(0);
}

void AddlistGroupAdd::OnBnClicked2()
{
	// TODO: 在此添加控件通知处理程序代码
	//OnOK();
	EndDialog(0);
}
bool AddlistGroupAdd::CheckGroupName(CString groupName)
{
	int nCount=0;
	bool check=true;
	variant_t vRecordsAffected1 ;
	if (groupName=="")
	{
		AfxMessageBox(_T("分组名称不能为空"));
		GetDlgItem(IDC_EDIT1)->SetFocus();
		check=false;
	}
	else
	{
        try
		{
            m_ptrConnection1->Open("","","", adConnectUnspecified);
			_bstr_t  Sql=_T("select count(*) as total from  ContactGroup where GropName='"+groupName+"'");
			//m_ptrRecordset->Open((Sql),m_ptrConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
			m_ptrRecordset1=m_ptrConnection1->Execute(Sql, &vRecordsAffected1, adCmdText);
		}
		catch(_com_error e)
		{			
			AfxMessageBox(e.Description());
		}
		if (!m_ptrRecordset1->adoEOF)
		{
			_variant_t Count = m_ptrRecordset1->GetCollect(_T("total"));
			nCount=Count.iVal;
			if (nCount>=1)
		 {
			 AfxMessageBox(_T("分组重复，请重新分组"));
			 GetDlgItem(IDC_EDIT1)->SetFocus();
			 check=false;
		 }
		}
		if (m_ptrRecordset1->State!=adStateClosed)
		{
			m_ptrRecordset1->Close();
		}
		if (m_ptrConnection1->State!=adStateClosed)
		{
			m_ptrConnection1->Close();
		}
	}
	return  check;
} 