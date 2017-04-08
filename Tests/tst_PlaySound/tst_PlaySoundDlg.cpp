
// tst_PlaySoundDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "tst_PlaySound.h"
#include "tst_PlaySoundDlg.h"
#include "afxdialogex.h"
#include "../../Tank2017/MCIPlaySndManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Ctst_PlaySoundDlg 对话框



Ctst_PlaySoundDlg::Ctst_PlaySoundDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Ctst_PlaySoundDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ctst_PlaySoundDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Ctst_PlaySoundDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_PLAY1, &Ctst_PlaySoundDlg::OnBnClickedBtnPlay1)
	ON_BN_CLICKED(IDC_BTN_STOP1, &Ctst_PlaySoundDlg::OnBnClickedBtnStop1)
	ON_BN_CLICKED(IDC_BTN_PLAY2, &Ctst_PlaySoundDlg::OnBnClickedBtnPlay2)
	ON_BN_CLICKED(IDC_BTN_STOP2, &Ctst_PlaySoundDlg::OnBnClickedBtnStop2)
END_MESSAGE_MAP()


// Ctst_PlaySoundDlg 消息处理程序

BOOL Ctst_PlaySoundDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Ctst_PlaySoundDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Ctst_PlaySoundDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Ctst_PlaySoundDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Ctst_PlaySoundDlg::OnBnClickedBtnPlay1()
{
	// TODO: 在此添加控件通知处理程序代码
	MCIPlaySndManager::GetInstance().PlayGameSound( _T("res/bg0.mp3"));
}


void Ctst_PlaySoundDlg::OnBnClickedBtnStop1()
{
	// TODO: 在此添加控件通知处理程序代码
	MCIPlaySndManager::GetInstance().StopGameSound( _T("res/bg0.mp3"));
}


void Ctst_PlaySoundDlg::OnBnClickedBtnPlay2()
{
	// TODO: 在此添加控件通知处理程序代码
	MCIPlaySndManager::GetInstance().PlayGameSound( _T("res/bg1.wav"), true );
}


void Ctst_PlaySoundDlg::OnBnClickedBtnStop2()
{
	// TODO: 在此添加控件通知处理程序代码
	MCIPlaySndManager::GetInstance().StopGameSound( _T("res/bg1.wav"));
}
