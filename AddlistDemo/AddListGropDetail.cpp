// AddListGropDetail.cpp : 实现文件
//

#include "stdafx.h"
#include "AddlistDemo.h"
#include "AddListGropDetail.h"


// AddListGropDetail 对话框

IMPLEMENT_DYNAMIC(AddListGropDetail, CDialog)

AddListGropDetail::AddListGropDetail(CWnd* pParent)
	: CDialog(AddListGropDetail::IDD, pParent)
	, txtId(_T(""))
	, txtGroupName(_T(""))
	, txtGroupMemo(_T(""))
{
	CoInitialize(NULL);
	m_ptrRecordset.CreateInstance(__uuidof(Recordset));  
	m_ptrConnection.CreateInstance(__uuidof(Connection));  
	m_ptrConnection->ConnectionString=_T("provider=Microsoft.Jet.OLEDB.4.0;Data Source=caoqiwen.mdb;");
}

AddListGropDetail::~AddListGropDetail()
{
}

void AddListGropDetail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, txtId);
	DDX_Text(pDX, IDC_EDIT3, txtGroupName);
	DDX_Text(pDX, IDC_EDIT4, txtGroupMemo);
}


BEGIN_MESSAGE_MAP(AddListGropDetail, CDialog)
	ON_BN_CLICKED(IDOK, &AddListGropDetail::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &AddListGropDetail::OnBnClickedCancel)
	//ON_COMMAND(ID_32772, &AddListGropDetail::On32772)
END_MESSAGE_MAP()


// AddListGropDetail 消息处理程序

void AddListGropDetail::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);
	if (checkGroupName(txtId)==FALSE)
	{
		return;
	}
	variant_t   vRecordsAffected;
	try
	{
		m_ptrConnection->Open("","","", adConnectUnspecified);
		CString  Sql;
		//修改了一个bug，我在改变备忘录的值时忘对%s加上单引号，而对于id来说不需要改变。
		Sql.Format(_T("Update ContactGroup set [GropName]='%s',[Memo]='%s' where [Id]=%d"),txtGroupName,txtGroupMemo,_ttoi(txtId));
		m_ptrRecordset=	m_ptrConnection->Execute((_bstr_t)Sql, &vRecordsAffected, adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	if(vRecordsAffected.lVal>0)
	{
		AfxMessageBox(_T("更新成功"));
	}
	else
	{
		AfxMessageBox(_T("更新失败"));
	}

	if (m_ptrRecordset->State!=adStateClosed)
	{
		m_ptrRecordset->Close();
	}

	if (m_ptrConnection->State!=adStateClosed)
	{
		m_ptrConnection->Close();
	}

	OnOK();
}

void AddListGropDetail::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}
BOOL AddListGropDetail::OnInitDialog()
{
	//int id1=this->id;
	CDialog::OnInitDialog();
	SetDlgItemText(IDC_EDIT1,txtId);    //设置它的编号，我试过在构造函数中传递id的值进行传递，但是没成功，不知道为什么好像不能从一开始就直接赋值给他。
	
	try
	{
		m_ptrConnection->Open("","","", adConnectUnspecified);
		//_bstr_t  SqlConnection=_T("select * from ContactGroup where Id="+ _ttoi(txtId) +""); //这句不能少
		CString  sqlConnection;
		sqlConnection.Format(_T("select * from ContactGroup where Id=%d"),_ttoi(txtId));
		m_ptrRecordset->Open(_bstr_t(sqlConnection),m_ptrConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	if (!m_ptrRecordset->adoBOF)
	{
		variant_t  temp1,temp2;
		//CString  str1,str2;
		temp1=m_ptrRecordset->GetCollect(_T("GropName"));
		txtGroupName=temp1.bstrVal;
		SetDlgItemText(IDC_EDIT3,txtGroupName);
		temp2=m_ptrRecordset->GetCollect(_T("Memo"));
		txtGroupMemo=temp2.bstrVal;
		SetDlgItemText(IDC_EDIT4,txtGroupMemo);
    }
   if (m_ptrRecordset->State!=adStateClosed)
	{
		m_ptrRecordset->Close();
	}
	if (m_ptrConnection->State!=adStateClosed)
	{
		m_ptrConnection->Close();
	}
	UpdateData(FALSE);   
	return TRUE;
}
BOOL AddListGropDetail::checkGroupName(CString groupName)
{
	BOOL check=TRUE;
	if (groupName=="")
	{
		AfxMessageBox(_T("分组名称不能为空"));
	    GetDlgItem(IDC_EDIT1)->SetFocus();
		check=FALSE;
	}
     return  check;
}

