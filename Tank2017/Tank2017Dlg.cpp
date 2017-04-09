
// Tank2017Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Tank2017.h"
#include "Tank2017Dlg.h"
#include "afxdialogex.h"
#include "MapGrid.h"
#include "AiObject.h"
#include "OpposingTank.h"
#include "GlobalFunction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define IDI_TANK2017_UPDATE			1			//

//按钮
#define IDC_BTN_START				100			//开始按钮


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


// CTank2017Dlg 对话框



CTank2017Dlg::CTank2017Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTank2017Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTank2017Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTank2017Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CTank2017Dlg 消息处理程序

BOOL CTank2017Dlg::OnInitDialog()
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

	//设置窗口固定大小 
	//ModifyStyle( WS_THICKFRAME, WS_CLIPCHILDREN );
	ModifyStyle( WS_THICKFRAME, 0 );


	//计算边框大小
	CRect windowRect;
	CRect clientRect;
	GetWindowRect( windowRect );
	GetClientRect( clientRect );
	int nXBorder = windowRect.Width() - clientRect.Width();
	int nYBorder = windowRect.Height() - clientRect.Height();

	//设置窗口大小
	int nWidth = 940;		//窗口宽
	int nHeight = 680;		//窗口高
	int nGameInfoWidth = 204; //游戏信息视图
	MoveWindow( 0, 0, nWidth + nXBorder, nHeight + nYBorder );
	CenterWindow();

	//游戏视图
	m_GameView.Create( NULL, NULL, WS_VISIBLE|WS_CHILD, 
		CRect( 0, 0, nWidth-nGameInfoWidth, nHeight), this, 0 );
	m_GameView.SetWorld( &m_World );
	m_GameView.SetGamePlayer( &m_GamePlayer );

	//信息视图
	m_GameInfoView.Create( NULL, NULL, WS_VISIBLE|WS_CHILD, 
		CRect( nWidth - nGameInfoWidth, 0, nWidth, nHeight), this, 0 );
	m_GameInfoView.SetGamePlayer( &m_GamePlayer );


	// 世界初始化
	if ( !m_World.Initialize( (nWidth - nGameInfoWidth) / Tank2017::gGridUnitSize,
		nHeight / Tank2017::gGridUnitSize ) )
	{
		AfxMessageBox( _T("Initialize Map Grid failed!"));
		return FALSE;
	}

	// 创建玩家
	m_GamePlayer.SetWorld( &m_World );
	m_GamePlayer.Respawn();
	
	

	// 播放背景音乐
	int nIndex = 1;//rand() % 2;
	TCHAR szBgFile[128] = { 0 };
	_stprintf_s( szBgFile, _countof(szBgFile), _T("res/bg%d.mp3"), nIndex );
	Tank2017::PlayMusic( szBgFile, true );


	// 主逻辑定时器
	SetTimer( IDI_TANK2017_UPDATE, 30, NULL );

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTank2017Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTank2017Dlg::OnPaint()
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
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTank2017Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTank2017Dlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnCancel();
}


void CTank2017Dlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CTank2017Dlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	EndDialog(IDCANCEL);

	//CDialogEx::OnClose();
}


BOOL CTank2017Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if ( pMsg->message == WM_KEYDOWN )
	{
		m_GamePlayer.OnEventKeyDown( pMsg->wParam );
	}
	else if ( pMsg->message == WM_KEYUP )
	{
		m_GamePlayer.OnEventKeyUp( pMsg->wParam );
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CTank2017Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if ( nIDEvent == IDI_TANK2017_UPDATE )
	{
		//更新游戏视图
		m_GameView.InvalidateRect( NULL, FALSE );

		//更新游戏信息视图
		m_GameInfoView.InvalidateRect( NULL, FALSE );

		//玩家
		m_GamePlayer.RunLogic();

		//逻辑函数
		m_World.RunLogic();
	}

	CDialogEx::OnTimer(nIDEvent);
}
