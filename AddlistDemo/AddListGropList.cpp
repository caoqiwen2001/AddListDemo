// AddListGropList.cpp : 实现文件
//

#include "stdafx.h"
#include "AddlistDemo.h"
#include "AddListGropList.h"
#include "AddlistGroupAdd.h"
#include "AddListGropDetail.h"


// AddListGropList 对话框

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


// AddListGropList 消息处理程序

BOOL  AddListGropList::OnInitDialog()
{
	CDialog::OnInitDialog();
	DWORD dwStyle = m_CListCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;//选中某行使整行高亮（只适用与report风格的listctrl）


	m_CListCtrl.SetExtendedStyle(dwStyle);
	m_CListCtrl.InsertColumn(0,_T("ID"),HDS_DRAGDROP,0);
	m_CListCtrl.InsertColumn(1,_T("名称"),HDS_DRAGDROP,100); //插入列
	m_CListCtrl.InsertColumn(2,_T("备注"),LVCFMT_LEFT,100);
	Fill();

	return TRUE;
}
int AddListGropList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}

//UINT AddListGropList::OnNotifyFormat(CWnd *pWnd, UINT nCommand)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	return CDialog::OnNotifyFormat(pWnd, nCommand);
//}
//数据库的填充函数
void AddListGropList::Fill()
{
	
	try
	{
		m_ptrConnection1->Open("","","", adConnectUnspecified);
		_bstr_t  SqlConnection=_T("select * from ContactGroup"); //这句不能少
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
		//把数据库中的相应信息表中
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
	// TODO: 在此添加控件通知处理程序代码
	AddlistGroupAdd f=new AddlistGroupAdd;
	f.DoModal();
	//clistctrl的值首先要删除掉在重新插入，这里必须考虑
	m_CListCtrl.DeleteAllItems();
	Fill();
}
void AddListGropList::btnDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str,midString;
	for(int i=0; i<m_CListCtrl.GetItemCount(); i++)
	{
		if( m_CListCtrl.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{

			midString=m_CListCtrl.GetItemText(i,0);
			id=_ttoi(midString);   //转换成i;
			break;
		}
	}
	if(MessageBox(_T("确定要删除吗"),_T("标题"),MB_ICONEXCLAMATION|MB_OKCANCEL)!=IDOK)
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
			AfxMessageBox(_T("该分组下存在联系人信息，不允许删除！"));
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

	//删除分组,这里可以写成一个函数
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
		AfxMessageBox(_T("删除成功"));
	}
	else
	{
		AfxMessageBox(_T("删除失败"));
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
	Fill();   //这里调用fill的话不能用m_prtConnection1,原因是数据库还没有关闭
}
void AddListGropList::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CString  midString;
	for(int i=0; i<m_CListCtrl.GetItemCount(); i++)
	{
		if( m_CListCtrl.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{

			midString=m_CListCtrl.GetItemText(i,0);
			//id=_ttoi(midString);   //转换成i;
			break;
		}
	}
	AddListGropDetail f=new AddListGropDetail(0);
	f.txtId=midString;    //获得id号
	f.DoModal();
	m_CListCtrl.DeleteAllItems();
	Fill();

}
