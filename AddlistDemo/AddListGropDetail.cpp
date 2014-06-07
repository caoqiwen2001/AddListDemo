// AddListGropDetail.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AddlistDemo.h"
#include "AddListGropDetail.h"


// AddListGropDetail �Ի���

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


// AddListGropDetail ��Ϣ�������

void AddListGropDetail::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		//�޸���һ��bug�����ڸı䱸��¼��ֵʱ����%s���ϵ����ţ�������id��˵����Ҫ�ı䡣
		Sql.Format(_T("Update ContactGroup set [GropName]='%s',[Memo]='%s' where [Id]=%d"),txtGroupName,txtGroupMemo,_ttoi(txtId));
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

void AddListGropDetail::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}
BOOL AddListGropDetail::OnInitDialog()
{
	//int id1=this->id;
	CDialog::OnInitDialog();
	SetDlgItemText(IDC_EDIT1,txtId);    //�������ı�ţ����Թ��ڹ��캯���д���id��ֵ���д��ݣ�����û�ɹ�����֪��Ϊʲô�����ܴ�һ��ʼ��ֱ�Ӹ�ֵ������
	
	try
	{
		m_ptrConnection->Open("","","", adConnectUnspecified);
		//_bstr_t  SqlConnection=_T("select * from ContactGroup where Id="+ _ttoi(txtId) +""); //��䲻����
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
		AfxMessageBox(_T("�������Ʋ���Ϊ��"));
	    GetDlgItem(IDC_EDIT1)->SetFocus();
		check=FALSE;
	}
     return  check;
}

