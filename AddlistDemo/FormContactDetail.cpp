// FormContactDetail.cpp : 实现文件
//

#include "stdafx.h"
#include "AddlistDemo.h"
#include "FormContactDetail.h"


// FormContactDetail 对话框

IMPLEMENT_DYNAMIC(FormContactDetail, CDialog)

FormContactDetail::FormContactDetail(CWnd* pParent /*=NULL*/)
	: CDialog(FormContactDetail::IDD, pParent)
	, txtId(0)
	, txtName(_T(""))
	, txtPhone(_T(""))
	, txtEmail(_T(""))
	, txtWorkUnit(_T(""))
	, txtOfficePhone(_T(""))
	, txtHomePhone(_T(""))
	, txtHomeAddress(_T(""))
	, txtQQ(_T(""))
	, txtMemo(_T(""))
{
	CoInitialize(NULL);
	m_ptrRecordset.CreateInstance(__uuidof(Recordset));  
	m_ptrConnection.CreateInstance(__uuidof(Connection));  
	m_ptrConnection->ConnectionString=_T("provider=Microsoft.Jet.OLEDB.4.0;Data Source=caoqiwen.mdb;");
}

FormContactDetail::~FormContactDetail()
{
}

void FormContactDetail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, txtId);
	DDX_Text(pDX, IDC_EDIT2, txtName);
	DDX_Text(pDX, IDC_EDIT3, txtPhone);
	DDX_Text(pDX, IDC_EDIT4, txtEmail);
	DDX_Text(pDX, IDC_EDIT5, txtWorkUnit);
	DDX_Text(pDX, IDC_EDIT6, txtOfficePhone);
	DDX_Text(pDX, IDC_EDIT7, txtHomePhone);
	DDX_Text(pDX, IDC_EDIT8, txtHomeAddress);
	DDX_Text(pDX, IDC_EDIT10, txtQQ);
//	DDX_Control(pDX, IDC_COMBO1, cboGroup);
	DDX_Text(pDX, IDC_EDIT9, txtMemo);
}


BEGIN_MESSAGE_MAP(FormContactDetail, CDialog)
	ON_BN_CLICKED(IDOK, &FormContactDetail::OnBnClickedOk)
END_MESSAGE_MAP()


// FormContactDetail 消息处理程序

BOOL FormContactDetail::OnInitDialog()
{
	CDialog::OnInitDialog();
	try
	{
		m_ptrConnection->Open("","","", adConnectUnspecified);
		CString  sqlConnection;
		sqlConnection.Format(_T("select * from Contact where Id=%d"),txtId);
		m_ptrRecordset->Open(_bstr_t(sqlConnection),m_ptrConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	if (!m_ptrRecordset->adoBOF)
	{
		variant_t  temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8,temp9;
		temp1=m_ptrRecordset->GetCollect(_T("name"));
		temp2=m_ptrRecordset->GetCollect(_T("phone"));
		temp3=m_ptrRecordset->GetCollect(_T("email"));
		temp4=m_ptrRecordset->GetCollect(_T("qq"));
		temp5=m_ptrRecordset->GetCollect(_T("workInit"));
		temp6=m_ptrRecordset->GetCollect(_T("officePhone"));
        temp7=m_ptrRecordset->GetCollect(_T("HomeAddress"));
		temp8=m_ptrRecordset->GetCollect(_T("homephone"));
		temp9=m_ptrRecordset->GetCollect(_T("memo"));
	txtName=(LPCTSTR)(_bstr_t)temp1;
	txtPhone=(LPCTSTR)(_bstr_t)temp2;
	txtEmail=(LPCTSTR)(_bstr_t)temp3;
	txtQQ=(LPCTSTR)(_bstr_t)temp4;
	txtWorkUnit=(LPCTSTR)(_bstr_t)temp5;
	txtOfficePhone=(LPCTSTR)(_bstr_t)temp6;
	txtHomeAddress=(LPCTSTR)(_bstr_t)temp7;
	txtHomePhone=(LPCTSTR)(_bstr_t)temp8;
	txtMemo=(LPCTSTR)(_bstr_t)temp9;
	UpdateData(FALSE);
	}
	if (m_ptrRecordset->State!=adStateClosed)
	{
		m_ptrRecordset->Close();
	}
	if (m_ptrConnection->State!=adStateClosed)
	{
		m_ptrConnection->Close();
	}
	return  TRUE;
}

void FormContactDetail::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	variant_t   vRecordsAffected;
	m_ptrConnection->Open("","","", adConnectUnspecified);
		//  _bstr_t  SqlConnection=_T("select id from ContactGroup where gropName=str"); //这句不能少
		CString  sqlConnection;
		if (txtName==""||txtPhone==""||txtEmail==""||txtQQ==""||txtWorkUnit==""||txtOfficePhone==""||txtHomePhone==""||txtMemo=="")
		{
			AfxMessageBox(_T("值不能为空"));
			OnOK();
		}
		else
		{
try
{
        sqlConnection.Format(_T("Update Contact set [name]='%s',[phone]='%s', [email]='%s',[qq]='%s',[workInit]='%s',[officePhone]='%s',[HomeAddress]='%s',[homephone]='%s',[memo]='%s'where [id]=%d"),txtName,txtPhone,txtEmail,txtQQ,txtWorkUnit,txtOfficePhone,txtHomeAddress,txtHomePhone,txtMemo,txtId);
		m_ptrRecordset->Open(_bstr_t(sqlConnection),m_ptrConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		m_ptrRecordset=	m_ptrConnection->Execute((_bstr_t)sqlConnection, &vRecordsAffected, adCmdText);
}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	if(vRecordsAffected.lVal>0)
	{
		AfxMessageBox(_T("更新成功"));
	}	else
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
    }
    
	OnOK();    //退出程序
}
