// GameFrame.cpp : 实现文件
//

#include "stdafx.h"
#include "Tank2017.h"
#include "GameFrame.h"
#include "GlobalFunction.h"


#define IDI_TANK2017_UPDATE			(1)		//更新定时器，暂用定时器驱动主逻辑


// GameFrame

IMPLEMENT_DYNAMIC(GameFrame, CFrameWnd)

GameFrame::GameFrame()
{
	m_hIcon = AfxGetApp()->LoadIcon( IDR_MAINFRAME );
}

GameFrame::~GameFrame()
{
}


BEGIN_MESSAGE_MAP(GameFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
END_MESSAGE_MAP()



// GameFrame 消息处理程序




int GameFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//设置大小图标
	SetIcon( m_hIcon, TRUE );
	SetIcon( m_hIcon, FALSE );

	//设置标题
	SetWindowText( _T("Tank2017") );

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
	SetWindowPos( NULL, 0, 0, nWidth + nXBorder, nHeight + nYBorder, SWP_NOMOVE );


	//游戏视图
	m_GameView.Create( NULL, NULL, WS_VISIBLE|WS_CHILD, 
		CRect( 0, 0, nWidth-nGameInfoWidth, nHeight), this, 0 );
	m_GameView.SetWorld( &m_World );
	m_GameView.SetGamePlayer( &m_GamePlayer );

	//信息视图
	m_GameInfoView.Create( NULL, NULL, WS_VISIBLE|WS_CHILD, 
		CRect( nWidth - nGameInfoWidth, 0, nWidth, nHeight), this, 0 );
	m_GameInfoView.SetGamePlayer( &m_GamePlayer );

	//面板
	m_StartPanel.Create( IDD_START_PANEL, this );
	m_PausePanel.Create( IDD_PAUSE_PANEL, this );
	m_EndPanel.Create( IDD_END_PANEL, this );


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

	// 游戏逻辑
	g_GameLogic.Init( this );

	// 播放背景音乐
	int nIndex = 1;//rand() % 2;
	TCHAR szBgFile[128] = { 0 };
	_stprintf_s( szBgFile, _countof(szBgFile), _T("res/bg%d.mp3"), nIndex );
	Tank2017::PlayMusic( szBgFile, true );

	// 主逻辑定时器
	SetTimer( IDI_TANK2017_UPDATE, 30, NULL );

	return 0;
}




void GameFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if ( nIDEvent == IDI_TANK2017_UPDATE )
	{
		//更新游戏视图
		m_GameView.InvalidateRect( NULL, FALSE );

		//更新游戏信息视图
		m_GameInfoView.InvalidateRect( NULL, FALSE );

		if ( g_GameLogic.IsStarted() && !g_GameLogic.IsPaused() )
		{
			//玩家
			m_GamePlayer.RunLogic();

			//逻辑函数
			m_World.RunLogic();
		}
	}


	CWnd::OnTimer(nIDEvent);
}


void GameFrame::OnEventGameStarted()
{
	//隐藏所有面板
	ShowPanel( Panel_All, false );

	//重置得分
	m_GamePlayer.ResetScore();
}

void GameFrame::OnEventGamePaused()
{
	//显示暂停面板，其它隐藏
	ShowPanel( Panel_Start | Panel_End, false );
	ShowPanel( Panel_Pause, true );
}

void GameFrame::OnEventGameContinue()
{
	//隐藏所有面板
	ShowPanel( Panel_All, false );
}

void GameFrame::OnEventGameEnded()
{
	//显示结束面板，其他隐藏
	ShowPanel( Panel_End, true );
	ShowPanel( Panel_Start|Panel_Pause, false );
}


void GameFrame::ShowPanel( PanelType cbPanel, bool bShow )
{
	if ( cbPanel & Panel_Start )
	{
		showPanel( m_StartPanel, bShow );
	}

	if ( cbPanel & Panel_Pause )
	{
		showPanel( m_PausePanel, bShow );
	}

	if ( cbPanel & Panel_End )
	{
		showPanel( m_EndPanel, bShow );
	}
}

void GameFrame::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if ( nChar == VK_ESCAPE )
	{
		if ( g_GameLogic.IsStarted() && !g_GameLogic.IsPaused() )
		{
			//游戏暂停
			g_GameLogic.Pause();
		}
	}
	else
	{
		m_GamePlayer.OnEventKeyDown( nChar );
	}

	__super::OnKeyDown(nChar, nRepCnt, nFlags);
}


void GameFrame::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_GamePlayer.OnEventKeyUp( nChar );
	__super::OnKeyUp(nChar, nRepCnt, nFlags);
}

void GameFrame::showPanel( CWnd& mPanel, bool bShow )
{
	ASSERT( mPanel.m_hWnd != NULL );
	if ( mPanel.m_hWnd == NULL )
	{
		return;
	}

	mPanel.ShowWindow( bShow );

	if ( bShow )
	{
		mPanel.CenterWindow( &m_GameView );
		mPanel.SetActiveWindow();
		mPanel.SetForegroundWindow();
	}
}
