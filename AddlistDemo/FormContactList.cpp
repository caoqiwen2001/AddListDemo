// FormContactList.cpp : 实现文件
//

#include "stdafx.h"
#include "AddlistDemo.h"
#include "FormContactList.h"
#include "FormContactAdd.h"
#include "FormContactDetail.h"


// FormContactList 对话框

IMPLEMENT_DYNAMIC(FormContactList, CDialog)

FormContactList::FormContactList(CWnd* pParent /*=NULL*/)
	: CDialog(FormContactList::IDD, pParent)
	, txtSearch(_T(""))
{
	//放在构造函数中初始化
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


// FormContactList 消息处理程序

//void FormContactList::OnBnClickedButton1()
//{
//	// TODO: 在此添加控件通知处理程序代码
//}
void FormContactList::Fill()
{
	UpdateData(TRUE);
	CString  str;
	((CComboBox*)GetDlgItem(IDC_COMBO1))->GetWindowText(str);//获取当前对话框中的值
	try
	{
		m_ptrConnection->Open("","","", adConnectUnspecified);
		_bstr_t  SqlConnection=_T("select Contact.id,name,phone,email,qq,GropName  from Contact,Contactgroup where contact.groupid=contactgroup.id"); 
         if(str==_T("手机"))
         {
              SqlConnection+=_T(" and phone like '%" + txtSearch + "%'");
         }
		 else if (str==_T("姓名"))
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

		//把数据库中的相应信息表中
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
	dwStyle |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;//选中某行使整行高亮（只适用与report风格的listctrl）
    dgvContactList.SetExtendedStyle(dwStyle);
	dgvContactList.InsertColumn(0,_T("ID"),HDS_DRAGDROP,0);
	dgvContactList.InsertColumn(1,_T("姓名"),HDS_DRAGDROP,100); //插入列
	dgvContactList.InsertColumn(2,_T("电话"),LVCFMT_LEFT,100);
	dgvContactList.InsertColumn(3,_T("电子邮件"),LVCFMT_LEFT,100);
	dgvContactList.InsertColumn(4,_T("QQ"),LVCFMT_LEFT,100);
	dgvContactList.InsertColumn(5,_T("所在分组"),LVCFMT_LEFT,100);
    ((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("手机"));  //初始化一个手机 和姓名
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("姓名"));
     Fill();
     return TRUE;
 }
 void FormContactList::OnBnClickedButton1()
 {
	 // TODO: 在此添加控件通知处理程序代码
	 dgvContactList.DeleteAllItems();
	 Fill();
 }

 void FormContactList::OnBnClickedOk2()
 {
	 // TODO: 在此添加控件通知处理程序代码
	 FormContactAdd  formContactAdd;
	 formContactAdd.DoModal();
	 dgvContactList.DeleteAllItems();
	 Fill();
 }

 
 //删除通讯录中信息
 void FormContactList::OnBtnDelete()
 {
	 // TODO: 在此添加控件通知处理程序代码
	 CString str,midString;
	 for(int i=0; i<dgvContactList.GetItemCount(); i++)
	 {
		 if( dgvContactList.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		 {

			 midString=dgvContactList.GetItemText(i,0);
			 id=_ttoi(midString);   //转换成i;
			 break;
		 }
	 }
	 if(MessageBox(_T("确定要删除吗"),_T("标题"),MB_ICONEXCLAMATION|MB_OKCANCEL)!=IDOK)
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
		 AfxMessageBox(_T("删除成功"));
		 
	 }
	 else
	 {
		 AfxMessageBox(_T("删除失败"));
	 }
	 if (m_ptrRecordset->State!=adStateClosed)
	 {
		 m_ptrRecordset->Close();
	 }

	 if (m_ptrConnection->State!=adStateClosed)
	 {
		  m_ptrConnection->Close();
	 }
	 //删除，重新加载
	 dgvContactList.DeleteAllItems();
	 Fill();
	 return;
 }

 void FormContactList::OnBnClickedOk()
 {
	 // TODO: 在此添加控件通知处理程序代码
	 CString  midString;
	 for(int i=0; i<dgvContactList.GetItemCount(); i++)
	 {
		 if( dgvContactList.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		 {

			 midString=dgvContactList.GetItemText(i,0);
			 id=_ttoi(midString);   //转换成i;
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
