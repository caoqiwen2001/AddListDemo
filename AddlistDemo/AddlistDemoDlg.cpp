
// AddlistDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AddlistDemoDlg.h"
#include "MainDlg.h";
#include "AddlistDemo.h"
#include "UsrHelp.h"
#include "MyListCtrl.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAddlistDemoDlg 对话框




CAddlistDemoDlg::CAddlistDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddlistDemoDlg::IDD, pParent)
	, userName(_T(""))
	, Password(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	userName=_T(""); 
	Password=_T("");
	CoInitialize(NULL);
	m_ptrRecordset.CreateInstance(__uuidof(Recordset));  
	m_ptrConnection.CreateInstance(__uuidof(Connection));  
	m_ptrConnection->ConnectionString=_T("provider=Microsoft.Jet.OLEDB.4.0;Data Source=caoqiwen.mdb;");
}

void CAddlistDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, userName);    //两个textbox控件的属性
	DDX_Text(pDX, IDC_EDIT2, Password);
}

BEGIN_MESSAGE_MAP(CAddlistDemoDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON2, &CAddlistDemoDlg::OnBnClickedButton2)
	//ON_EN_CHANGE(IDC_EDIT1, &CAddlistDemoDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON3, &CAddlistDemoDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CAddlistDemoDlg 消息处理程序

BOOL CAddlistDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAddlistDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		
	
	
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
		
	}
	else
	{
		CPaintDC dc(this);
        CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAddlistDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CAddlistDemoDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

   UpdateData(TRUE);
try
{
	 m_ptrConnection->Open("","","", adConnectUnspecified);
	_bstr_t  Sql=_T("select * from LOG where UserName='"+userName+"'");
	 m_ptrRecordset->Open((Sql),m_ptrConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);

}
catch(_com_error e)
{
	AfxMessageBox(e.Description());
	//直接返回比较好。有待修改。
	
}

if (!m_ptrRecordset->adoBOF)
{
	variant_t  temp1;
	CString  str1,str2;
	temp1=m_ptrRecordset->GetCollect(_T("password"));
	str1=temp1.bstrVal;
    if (Password!=str1)
	{
		AfxMessageBox(_T("密码错误"));
	}
	else
	{
		UsrHelp::usrName=userName;
		UsrHelp::password=Password;
	MainDlg  *mainDlg=new MainDlg;
	mainDlg->Create(IDD_DIALOG1,this);
	mainDlg->ShowWindow(SW_SHOW);
	
	}
}
else
{
	AfxMessageBox(_T("没有可用账户"));
	m_ptrRecordset->Close();
	m_ptrConnection->Close();
	return ;
}

 CoUninitialize(); 
 m_ptrRecordset->Close();
 m_ptrConnection->Close();
}


void CAddlistDemoDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	DestroyWindow();
}
