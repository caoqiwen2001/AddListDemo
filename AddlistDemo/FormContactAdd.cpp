// FormContactAdd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AddlistDemo.h"
#include "FormContactAdd.h"


// FormContactAdd �Ի���

IMPLEMENT_DYNAMIC(FormContactAdd, CDialog)

FormContactAdd::FormContactAdd(CWnd* pParent /*=NULL*/)
	: CDialog(FormContactAdd::IDD, pParent)
	, txtName(_T(""))
	, txtPhone(_T(""))
	, txtQQ(_T(""))
	, txtEmail(_T(""))
	, txtWorkUnit(_T(""))
	, txtOfficePhone(_T(""))	, txtHomePhone(_T(""))
	, txtHomeAddress(_T(""))
	, txtMemo(_T(""))
{

}

FormContactAdd::~FormContactAdd()
{
}

void FormContactAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, txtName);
	DDX_Text(pDX, IDC_EDIT2, txtPhone);
	DDX_Text(pDX, IDC_EDIT3, txtQQ);
	DDX_Text(pDX, IDC_EDIT5, txtEmail);
	DDX_Text(pDX, IDC_EDIT4, txtWorkUnit);
	DDX_Text(pDX, IDC_EDIT6, txtOfficePhone);
	DDX_Text(pDX, IDC_EDIT7,txtHomePhone);
	DDX_Text(pDX, IDC_EDIT8, txtHomeAddress);
	DDX_Control(pDX, IDC_COMBO1, cboGroup);
	DDX_Text(pDX, IDC_EDIT9, txtMemo);
}


BEGIN_MESSAGE_MAP(FormContactAdd, CDialog)
	ON_BN_CLICKED(IDOK, &FormContactAdd::OnBnClickedOk)
END_MESSAGE_MAP()


// FormContactAdd ��Ϣ�������
BOOL FormContactAdd::OnInitDialog()
{

	 CDialog::OnInitDialog();
	CoInitialize(NULL);
	UpdateData(TRUE);
	m_ptrRecordset.CreateInstance(__uuidof(Recordset));  
	m_ptrConnection.CreateInstance(__uuidof(Connection));  
	m_ptrConnection->ConnectionString=_T("provider=Microsoft.Jet.OLEDB.4.0;Data Source=caoqiwen.mdb;");
	try
	{
		m_ptrConnection->Open("","","", adConnectUnspecified);
		_bstr_t  SqlConnection=_T("select * from ContactGroup"); //��䲻����
		m_ptrRecordset->Open((SqlConnection),m_ptrConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	_variant_t temp1,temp2,temp3;
	CString str1,str2,str3;
	int n=0,nRow=0;
	while(!m_ptrRecordset->adoEOF)
	{
		temp3=m_ptrRecordset->GetCollect("Id");
		temp1=m_ptrRecordset->GetCollect("GropName");
		temp2=m_ptrRecordset->GetCollect("Memo");
		str1=(LPCTSTR)(_bstr_t)temp1;
		str2=(LPCTSTR)(_bstr_t)temp2;
		str3=(LPCTSTR)(_bstr_t)temp3;
        ((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(str1);
        m_ptrRecordset->MoveNext();
		++n;
	}
	m_ptrRecordset->Close();
	m_ptrConnection->Close();
  return  TRUE;
}

void FormContactAdd::OnBnClickedOk()
{
	int id;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
   CoInitialize(NULL);
   UpdateData(TRUE);   //�󶨵�������
   m_ptrRecordset.CreateInstance(__uuidof(Recordset));  
   m_ptrConnection.CreateInstance(__uuidof(Connection));  
   m_ptrConnection->ConnectionString=_T("provider=Microsoft.Jet.OLEDB.4.0;Data Source=caoqiwen.mdb;");
    CString  str;
   ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetWindowText(str);//��ȡ��ǰ�Ի����е�ֵ  //ѡ��ccombox�е�ֵ������id��
try
   {
	   m_ptrConnection->Open("","","", adConnectUnspecified);
	 //  _bstr_t  SqlConnection=_T("select id from ContactGroup where gropName=str"); //��䲻����
	  CString  sqlConnection;
	   sqlConnection.Format(_T("select id from ContactGroup where gropname='%s'"),str);
	   m_ptrRecordset->Open(_bstr_t(sqlConnection),m_ptrConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
   }
 catch(_com_error e)
   {
	   AfxMessageBox(e.Description());
   }
   if (!m_ptrRecordset->adoBOF)
   {
	   variant_t  temp1;
	   temp1=m_ptrRecordset->GetCollect(_T("id"));
	   id=temp1.intVal;     //ת����id��
   }
   if (m_ptrRecordset->State!=adStateClosed)
   {
	   m_ptrRecordset->Close();
   }
   if (m_ptrConnection->State!=adStateClosed)
   {
	   m_ptrConnection->Close();
   }



//���뵽Contact�����µ�����
   variant_t   vRecordsAffected;
   try
   {
	   m_ptrConnection->Open("","","", adConnectUnspecified);
	   CString  Sql;
	   //�޸���һ��bug�����ڸı䱸��¼��ֵʱ����%s���ϵ����ţ�������id��˵����Ҫ�ı䡣
	   Sql.Format(_T("insert into Contact([Name],[Phone],[email],[qq],[workInit],[officephone],[homeaddress],[homephone],[memo],[groupid]) Values(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%d\')"),txtName,txtPhone,txtEmail,txtQQ,txtWorkUnit,txtOfficePhone,txtHomeAddress,txtHomePhone,txtMemo,id);
	   m_ptrRecordset=	m_ptrConnection->Execute((_bstr_t)Sql, &vRecordsAffected, adCmdText);
   }
   catch(_com_error e)
   {
	   AfxMessageBox(e.Description());
   }
   if(vRecordsAffected.lVal>0)
   {
	   AfxMessageBox(_T("���³ɹ�"));
   }
   else
   {
	   AfxMessageBox(_T("����ʧ��"));
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
