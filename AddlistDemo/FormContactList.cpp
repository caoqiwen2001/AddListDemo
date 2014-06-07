// FormContactList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AddlistDemo.h"
#include "FormContactList.h"
#include "FormContactAdd.h"
#include "FormContactDetail.h"


// FormContactList �Ի���

IMPLEMENT_DYNAMIC(FormContactList, CDialog)

FormContactList::FormContactList(CWnd* pParent /*=NULL*/)
	: CDialog(FormContactList::IDD, pParent)
	, txtSearch(_T(""))
{
	//���ڹ��캯���г�ʼ��
CoInitialize(NULL);
m_ptrRecordset.CreateInstance(__uuidof(Recordset));  
m_ptrConnection.CreateInstance(__uuidof(Connection));  
m_ptrConnection->ConnectionString=_T("provider=Microsoft.Jet.OLEDB.4.0;Data Source=caoqiwen.mdb;");

}

FormContactList::~FormContactList()
{
}

void FormContactList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, dgvContactList);
	DDX_Control(pDX, IDC_COMBO1, cboCondition);
	DDX_Text(pDX, IDC_EDIT1, txtSearch);
}


BEGIN_MESSAGE_MAP(FormContactList, CDialog)
//	ON_BN_CLICKED(IDC_BUTTON1, &FormContactList::OnBnClickedButton1)
ON_BN_CLICKED(IDC_BUTTON1, &FormContactList::OnBnClickedButton1)
ON_BN_CLICKED(IDOK2, &FormContactList::OnBnClickedOk2)
ON_BN_CLICKED(IDOK3, &FormContactList::OnBtnDelete)
ON_BN_CLICKED(IDOK, &FormContactList::OnBnClickedOk)
END_MESSAGE_MAP()


// FormContactList ��Ϣ�������

//void FormContactList::OnBnClickedButton1()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//}
void FormContactList::Fill()
{
	UpdateData(TRUE);
	CString  str;
	((CComboBox*)GetDlgItem(IDC_COMBO1))->GetWindowText(str);//��ȡ��ǰ�Ի����е�ֵ
	try
	{
		m_ptrConnection->Open("","","", adConnectUnspecified);
		_bstr_t  SqlConnection=_T("select Contact.id,name,phone,email,qq,GropName  from Contact,Contactgroup where contact.groupid=contactgroup.id"); 
         if(str==_T("�ֻ�"))
         {
              SqlConnection+=_T(" and phone like '%" + txtSearch + "%'");
         }
		 else if (str==_T("����"))
		 {
			  SqlConnection+=_T(" and name like '%" + txtSearch + "%'");
		 }
      m_ptrRecordset->Open((SqlConnection),m_ptrConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	_variant_t temp1,temp2,temp3,temp4,temp5,temp6;
	CString str1,str2,str3,str4,str5,str6;
	int n=0,nRow=0;
	while(!m_ptrRecordset->adoEOF)
	{
		temp3=m_ptrRecordset->GetCollect("Id");
		temp1=m_ptrRecordset->GetCollect("Name");
		temp2=m_ptrRecordset->GetCollect("Phone");
		temp4=m_ptrRecordset->GetCollect("Email");
        temp5=m_ptrRecordset->GetCollect("QQ");
		temp6=m_ptrRecordset->GetCollect("GropName");

		str1=(LPCTSTR)(_bstr_t)temp1;
		str2=(LPCTSTR)(_bstr_t)temp2;
		str3=(LPCTSTR)(_bstr_t)temp3;
		str4=(LPCTSTR)(_bstr_t)temp4;
		str5=(LPCTSTR)(_bstr_t)temp5;
		str6=(LPCTSTR)(_bstr_t)temp6;

		//�����ݿ��е���Ӧ��Ϣ����
		nRow=dgvContactList.InsertItem(n,_bstr_t(str3));
		dgvContactList.SetItemText(nRow,1,_bstr_t(str1));
		dgvContactList.SetItemText(nRow,2,_bstr_t(str2));
		dgvContactList.SetItemText(nRow,3,_bstr_t(str4));
	    dgvContactList.SetItemText(nRow,4,_bstr_t(str5));
        dgvContactList.SetItemText(nRow,5,_bstr_t(str6));
		m_ptrRecordset->MoveNext();
		++n;
	}
	m_ptrRecordset->Close();
	m_ptrConnection->Close();

}
 BOOL FormContactList::OnInitDialog()
{
	CDialog::OnInitDialog();
	DWORD dwStyle = dgvContactList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
    dgvContactList.SetExtendedStyle(dwStyle);
	dgvContactList.InsertColumn(0,_T("ID"),HDS_DRAGDROP,0);
	dgvContactList.InsertColumn(1,_T("����"),HDS_DRAGDROP,100); //������
	dgvContactList.InsertColumn(2,_T("�绰"),LVCFMT_LEFT,100);
	dgvContactList.InsertColumn(3,_T("�����ʼ�"),LVCFMT_LEFT,100);
	dgvContactList.InsertColumn(4,_T("QQ"),LVCFMT_LEFT,100);
	dgvContactList.InsertColumn(5,_T("���ڷ���"),LVCFMT_LEFT,100);
    ((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("�ֻ�"));  //��ʼ��һ���ֻ� ������
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("����"));
     Fill();
     return TRUE;
 }
 void FormContactList::OnBnClickedButton1()
 {
	 // TODO: �ڴ���ӿؼ�֪ͨ����������
	 dgvContactList.DeleteAllItems();
	 Fill();
 }

 void FormContactList::OnBnClickedOk2()
 {
	 // TODO: �ڴ���ӿؼ�֪ͨ����������
	 FormContactAdd  formContactAdd;
	 formContactAdd.DoModal();
	 dgvContactList.DeleteAllItems();
	 Fill();
 }

 
 //ɾ��ͨѶ¼����Ϣ
 void FormContactList::OnBtnDelete()
 {
	 // TODO: �ڴ���ӿؼ�֪ͨ����������
	 CString str,midString;
	 for(int i=0; i<dgvContactList.GetItemCount(); i++)
	 {
		 if( dgvContactList.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		 {

			 midString=dgvContactList.GetItemText(i,0);
			 id=_ttoi(midString);   //ת����i;
			 break;
		 }
	 }
	 if(MessageBox(_T("ȷ��Ҫɾ����"),_T("����"),MB_ICONEXCLAMATION|MB_OKCANCEL)!=IDOK)
		 return;
	 variant_t vRecordsAffected1 ;
    try                 
	 {     
		 m_ptrConnection->Open("","","", adConnectUnspecified);
		 CString  Sql;
		 Sql.Format(_T("delete  from  Contact where Id=%d"),id);
		 m_ptrRecordset=m_ptrConnection->Execute((_bstr_t)Sql, &vRecordsAffected1, adCmdText);
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
	 if (m_ptrRecordset->State!=adStateClosed)
	 {
		 m_ptrRecordset->Close();
	 }

	 if (m_ptrConnection->State!=adStateClosed)
	 {
		  m_ptrConnection->Close();
	 }
	 //ɾ�������¼���
	 dgvContactList.DeleteAllItems();
	 Fill();
	 return;
 }

 void FormContactList::OnBnClickedOk()
 {
	 // TODO: �ڴ���ӿؼ�֪ͨ����������
	 CString  midString;
	 for(int i=0; i<dgvContactList.GetItemCount(); i++)
	 {
		 if( dgvContactList.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		 {

			 midString=dgvContactList.GetItemText(i,0);
			 id=_ttoi(midString);   //ת����i;
			 break;
		 }
	 }
	 FormContactDetail  formContactDetail;
	 formContactDetail.txtId=id;
	 formContactDetail.DoModal();
	 dgvContactList.DeleteAllItems();
	 Fill();
	// OnOK();
 }
