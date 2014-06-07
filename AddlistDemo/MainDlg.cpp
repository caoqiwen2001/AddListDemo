// MainDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainDlg.h"
#include "AddlistDemo.h"
#include "AddListGropList.h"
#include "FormContactList.h"


// MainDlg �Ի���

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

	menu.LoadMenu(IDR_MENU1);  //  IDR_MENU1Ϊ�����Ĳ˵���ID����Resource��ͼ��Menu�ļ����¿����ҵ�
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


// MainDlg ��Ϣ�������

void MainDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}


void MainDlg::OnGroplist()
{
	// TODO: �ڴ���������������
     AddListGropList   addListGropList;
	 addListGropList.DoModal();
	
}

//void MainDlg::OnBnClicked2()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//}

void MainDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255,0,0));
	dc.TextOut(50,50,_T("��ϵ����������ͨ�޼���"));
}

void MainDlg::On32772()
{
	// TODO: �ڴ���������������
	FormContactList formContactList;
	formContactList.DoModal();
}
