
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
	//m_pPlayer1 = nullptr;
	m_nGameWidth = 1;
	m_nGameHeight = 1;
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
	ON_WM_KEYDOWN()
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


	// 加上标题栏及边框大小，让网络大小刚好是客户区大小的整数倍
	int nCyCaption = GetSystemMetrics( SM_CYCAPTION );
	int nCyBorder = GetSystemMetrics( SM_CYBORDER );
	int nCyFrame = GetSystemMetrics( SM_CYFRAME );
	int nCxFrame = GetSystemMetrics( SM_CXFRAME );
	int nCxBorder = GetSystemMetrics( SM_CXBORDER );

	int nWidth =  ( 2 * ::GetSystemMetrics(SM_CXSCREEN) ) / 3; 
	int nHeight = ( 3 * ::GetSystemMetrics(SM_CYSCREEN) ) / 4; 

	


	MoveWindow( 0, 0, nWidth, nHeight );
	CenterWindow();


	CRect clientRect;
	GetClientRect( &clientRect );

	// 信息区初始化
	int nInfoViewWidth = 200;
	int nInfoViewHeigth = clientRect.Height();
	CRect rcGameInfoView(
		clientRect.Width() - nInfoViewWidth,
		0, 
		clientRect.Width(),
		nInfoViewHeigth );
	m_GameInfoView.Create( NULL, NULL, WS_VISIBLE|WS_CHILD, 
		rcGameInfoView, this, 0 );
	m_GameInfoView.SetGamePlayer( &m_GamePlayer );


	//游戏区大小 
	m_nGameWidth = clientRect.Width() - nInfoViewWidth;
	m_nGameHeight = clientRect.Height();

	//按钮创建
// 	m_btnStart.Create(_T("开始"), WS_VISIBLE | BS_PUSHBUTTON,
// 		CRect( 100, 100, 150, 120 ), 
// 		this, IDC_BTN_START );

	// 创建缓冲DC
	CDC* pDC = this->GetDC();
	m_MemoryDc.CreateCompatibleDC( pDC );
	m_MemoryBmp.CreateCompatibleBitmap( pDC,
		m_nGameWidth, m_nGameHeight );
	m_MemoryDc.SelectObject( &m_MemoryBmp );
	this->ReleaseDC(pDC);
	pDC = nullptr;

	// 世界初始化
	if ( !m_World.Initialize( m_nGameWidth / Tank2017::gGridUnitSize,
		m_nGameHeight / Tank2017::gGridUnitSize ) )
	{
		AfxMessageBox( _T("Initialize Map Grid failed!"));
		return FALSE;
	}

	// 创建玩家
	m_GamePlayer.SetWorld( &m_World );
	m_GamePlayer.Respawn();
	//m_pPlayer1 = (PlayerTank*)(m_World.CreateEntity( enPlayerTank, 0, 0, 1, enDirRight));


	SetTimer( IDI_TANK2017_UPDATE, 30, NULL );

	// 播放背景音乐
	int nIndex = 1;//rand() % 2;
	TCHAR szBgFile[128] = { 0 };
	_stprintf_s( szBgFile, _countof(szBgFile), _T("res/bg%d.mp3"), nIndex );
	Tank2017::PlayMusic( szBgFile, true );


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
		CPaintDC dc(this);
		//CDC* dc = this->GetDC();
		dc.BitBlt( 0, 0, m_nGameWidth, m_nGameHeight, &m_MemoryDc,
			0, 0, SRCCOPY );
		//this->ReleaseDC( dc );

// 		CRect clientRect;
// 		GetClientRect( clientRect );
// 		ValidateRect( clientRect );
		//buffDc.SelectObject( pOldBmp );
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


void CTank2017Dlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
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
		//绘制函数
		CRect rect;
		GetClientRect(&rect);
		m_MemoryDc.FillSolidRect( 0, 0, m_nGameWidth, 
			m_nGameHeight, RGB( 0, 0, 0 ) );
		m_World.RunDraw( &m_MemoryDc );
		Invalidate( FALSE );
		//OnPaint();

		//玩家
		m_GamePlayer.RunLogic();

		//逻辑函数
		m_World.RunLogic();

		

	}

	CDialogEx::OnTimer(nIDEvent);
}
