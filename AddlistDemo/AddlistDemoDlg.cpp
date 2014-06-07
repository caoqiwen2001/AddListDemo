
// AddlistDemoDlg.cpp : ʵ���ļ�
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


// CAddlistDemoDlg �Ի���




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
	DDX_Text(pDX, IDC_EDIT1, userName);    //����textbox�ؼ�������
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


// CAddlistDemoDlg ��Ϣ�������

BOOL CAddlistDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAddlistDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		
	
	
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
		
	}
	else
	{
		CPaintDC dc(this);
        CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CAddlistDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CAddlistDemoDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

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
	//ֱ�ӷ��رȽϺá��д��޸ġ�
	
}

if (!m_ptrRecordset->adoBOF)
{
	variant_t  temp1;
	CString  str1,str2;
	temp1=m_ptrRecordset->GetCollect(_T("password"));
	str1=temp1.bstrVal;
    if (Password!=str1)
	{
		AfxMessageBox(_T("�������"));
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
	AfxMessageBox(_T("û�п����˻�"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DestroyWindow();
}
