// AddListGropList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AddlistDemo.h"
#include "AddListGropList.h"
#include "AddlistGroupAdd.h"
#include "AddListGropDetail.h"


// AddListGropList �Ի���

IMPLEMENT_DYNAMIC(AddListGropList, CDialog)

AddListGropList::AddListGropList(CWnd* pParent /*=NULL*/)
: CDialog(AddListGropList::IDD, pParent)
{

	id=0;
	CoInitialize(NULL);
	m_ptrRecordset1.CreateInstance(__uuidof(Recordset));  
	m_ptrConnection1.CreateInstance(__uuidof(Connection));  
	m_ptrConnection1->ConnectionString=_T("provider=Microsoft.Jet.OLEDB.4.0;Data Source=caoqiwen.mdb;");
}

AddListGropList::~AddListGropList()
{

}

void AddListGropList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_LIST4, m_ListCtrl);
	DDX_Control(pDX, IDC_LIST1, m_CListCtrl);
	DDX_Control(pDX, IDC_BUTTON2, btn_Delete);
}


BEGIN_MESSAGE_MAP(AddListGropList, CDialog)
	ON_WM_CREATE()
	//	ON_WM_NOTIFYFORMAT()
	ON_BN_CLICKED(IDC_BUTTON1, &AddListGropList::OnBnClickedButton1)
	//ON_BN_CLICKED(IDC_BUTTON2, &AddListGropList::OnBnClickedButton2)
	//ON_BN_CLICKED(IDC_BUTTON2, &AddListGropList::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON2, &AddListGropList::btnDelete)
	ON_BN_CLICKED(IDC_BUTTON3, &AddListGropList::OnBnClickedButton3)
END_MESSAGE_MAP()


// AddListGropList ��Ϣ�������

BOOL  AddListGropList::OnInitDialog()
{
	CDialog::OnInitDialog();
	DWORD dwStyle = m_CListCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��


	m_CListCtrl.SetExtendedStyle(dwStyle);
	m_CListCtrl.InsertColumn(0,_T("ID"),HDS_DRAGDROP,0);
	m_CListCtrl.InsertColumn(1,_T("����"),HDS_DRAGDROP,100); //������
	m_CListCtrl.InsertColumn(2,_T("��ע"),LVCFMT_LEFT,100);
	Fill();

	return TRUE;
}
int AddListGropList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}

//UINT AddListGropList::OnNotifyFormat(CWnd *pWnd, UINT nCommand)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//
//	return CDialog::OnNotifyFormat(pWnd, nCommand);
//}
//���ݿ����亯��
void AddListGropList::Fill()
{
	
	try
	{
		m_ptrConnection1->Open("","","", adConnectUnspecified);
		_bstr_t  SqlConnection=_T("select * from ContactGroup"); //��䲻����
		m_ptrRecordset1->Open((SqlConnection),m_ptrConnection1.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	_variant_t temp1,temp2,temp3;
	CString str1,str2,str3;
	int n=0,nRow=0;
	while(!m_ptrRecordset1->adoEOF)
	{
		temp3=m_ptrRecordset1->GetCollect("Id");
		temp1=m_ptrRecordset1->GetCollect("GropName");
		temp2=m_ptrRecordset1->GetCollect("Memo");
		str1=(LPCTSTR)(_bstr_t)temp1;
		str2=(LPCTSTR)(_bstr_t)temp2;
		str3=(LPCTSTR)(_bstr_t)temp3;
		//�����ݿ��е���Ӧ��Ϣ����
		nRow=m_CListCtrl.InsertItem(n,_bstr_t(str3));
		m_CListCtrl.SetItemText(nRow,1,_bstr_t(str1));
		m_CListCtrl.SetItemText(nRow,2,_bstr_t(str2));
		m_ptrRecordset1->MoveNext();
		++n;
	}
	m_ptrRecordset1->Close();
	m_ptrConnection1->Close();
}
void AddListGropList::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	AddlistGroupAdd f=new AddlistGroupAdd;
	f.DoModal();
	//clistctrl��ֵ����Ҫɾ���������²��룬������뿼��
	m_CListCtrl.DeleteAllItems();
	Fill();
}
void AddListGropList::btnDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str,midString;
	for(int i=0; i<m_CListCtrl.GetItemCount(); i++)
	{
		if( m_CListCtrl.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{

			midString=m_CListCtrl.GetItemText(i,0);
			id=_ttoi(midString);   //ת����i;
			break;
		}
	}
	if(MessageBox(_T("ȷ��Ҫɾ����"),_T("����"),MB_ICONEXCLAMATION|MB_OKCANCEL)!=IDOK)
		return;
	variant_t vRecordsAffected1 ;
	try                 
	{     
		m_ptrConnection1->Open("","","", adConnectUnspecified);
		CString  Sql;
		Sql.Format(_T("select count(*) as total from  Contact where GroupId=%d"),id);
		m_ptrRecordset1=m_ptrConnection1->Execute((_bstr_t)Sql, &vRecordsAffected1, adCmdText);
	} 
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}

	if (!m_ptrRecordset1->adoBOF)
	{
		_variant_t Count = m_ptrRecordset1->GetCollect(_T("total"));
		int  nCount=Count.iVal;
		if (nCount>=1)
		{
			AfxMessageBox(_T("�÷����´�����ϵ����Ϣ��������ɾ����"));
			//return;
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

	//ɾ������,�������д��һ������
	Delete();
	return;
}void  AddListGropList::Delete()
{ 

_variant_t  vRecordsAffected1;
	try
	{
		m_ptrConnection1->Open("","","", adConnectUnspecified);
		CString  sql1;
		sql1.Format(_T("delete  from  ContactGroup where  Id=%d"),id); 
		m_ptrRecordset1=m_ptrConnection1->Execute((_bstr_t)sql1, &vRecordsAffected1, adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	if (vRecordsAffected1.lVal>0)
	{
		AfxMessageBox(_T("ɾ���ɹ�"));
	}
	else
	{
		AfxMessageBox(_T("ɾ��ʧ��"));
	}
	if (m_ptrRecordset1->State!=adStateClosed)
	{
		m_ptrRecordset1->Close();
	}
    if (m_ptrConnection1->State!=adStateClosed)
	{
		m_ptrConnection1->Close();
	}
	m_CListCtrl.DeleteAllItems();
	Fill();   //�������fill�Ļ�������m_prtConnection1,ԭ�������ݿ⻹û�йر�
}
void AddListGropList::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString  midString;
	for(int i=0; i<m_CListCtrl.GetItemCount(); i++)
	{
		if( m_CListCtrl.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{

			midString=m_CListCtrl.GetItemText(i,0);
			//id=_ttoi(midString);   //ת����i;
			break;
		}
	}
	AddListGropDetail f=new AddListGropDetail(0);
	f.txtId=midString;    //���id��
	f.DoModal();
	m_CListCtrl.DeleteAllItems();
	Fill();

}
