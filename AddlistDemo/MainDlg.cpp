// MainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MainDlg.h"
#include "AddlistDemo.h"
#include "AddListGropList.h"
#include "FormContactList.h"


// MainDlg 对话框

IMPLEMENT_DYNAMIC(MainDlg, CDialog)

MainDlg::MainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(MainDlg::IDD, pParent)
{
    
}

MainDlg::~MainDlg()
{
    
}

BOOL MainDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

	menu.LoadMenu(IDR_MENU1);  //  IDR_MENU1为你加入的菜单的ID，在Resource视图的Menu文件夹下可以找到
	SetMenu(&menu);
	return  TRUE;
  
}
void MainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MainDlg, CDialog)
	ON_BN_CLICKED(IDOK, &MainDlg::OnBnClickedOk)
	//ON_COMMAND(ID_32774, &MainDlg::On32774)
	ON_COMMAND(ID_GropList, &MainDlg::OnGroplist)
//	ON_BN_CLICKED(2, &MainDlg::OnBnClicked2)
ON_WM_PAINT()
ON_COMMAND(ID_32772, &MainDlg::On32772)
END_MESSAGE_MAP()


// MainDlg 消息处理程序

void MainDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}


void MainDlg::OnGroplist()
{
	// TODO: 在此添加命令处理程序代码
     AddListGropList   addListGropList;
	 addListGropList.DoModal();
	
}

//void MainDlg::OnBnClicked2()
//{
//	// TODO: 在此添加控件通知处理程序代码
//}

void MainDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255,0,0));
	dc.TextOut(50,50,_T("联系你我他，沟通无极限"));
}

void MainDlg::On32772()
{
	// TODO: 在此添加命令处理程序代码
	FormContactList formContactList;
	formContactList.DoModal();
}
