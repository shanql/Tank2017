// GameFrame.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tank2017.h"
#include "GameFrame.h"
#include "GlobalFunction.h"


#define IDI_TANK2017_UPDATE			(1)		//���¶�ʱ�������ö�ʱ���������߼�


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



// GameFrame ��Ϣ�������




int GameFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//���ô�Сͼ��
	SetIcon( m_hIcon, TRUE );
	SetIcon( m_hIcon, FALSE );

	//���ñ���
	SetWindowText( _T("Tank2017") );

	//����߿��С
	CRect windowRect;
	CRect clientRect;
	GetWindowRect( windowRect );
	GetClientRect( clientRect );
	int nXBorder = windowRect.Width() - clientRect.Width();
	int nYBorder = windowRect.Height() - clientRect.Height();

	//���ô��ڴ�С
	int nWidth = 940;		//���ڿ�
	int nHeight = 680;		//���ڸ�
	int nGameInfoWidth = 204; //��Ϸ��Ϣ��ͼ
	SetWindowPos( NULL, 0, 0, nWidth + nXBorder, nHeight + nYBorder, SWP_NOMOVE );


	//��Ϸ��ͼ
	m_GameView.Create( NULL, NULL, WS_VISIBLE|WS_CHILD, 
		CRect( 0, 0, nWidth-nGameInfoWidth, nHeight), this, 0 );
	m_GameView.SetWorld( &m_World );
	m_GameView.SetGamePlayer( &m_GamePlayer );

	//��Ϣ��ͼ
	m_GameInfoView.Create( NULL, NULL, WS_VISIBLE|WS_CHILD, 
		CRect( nWidth - nGameInfoWidth, 0, nWidth, nHeight), this, 0 );
	m_GameInfoView.SetGamePlayer( &m_GamePlayer );

	//���
	m_StartPanel.Create( IDD_START_PANEL, this );
	m_PausePanel.Create( IDD_PAUSE_PANEL, this );
	m_EndPanel.Create( IDD_END_PANEL, this );


	// �����ʼ��
	if ( !m_World.Initialize( (nWidth - nGameInfoWidth) / Tank2017::gGridUnitSize,
		nHeight / Tank2017::gGridUnitSize ) )
	{
		AfxMessageBox( _T("Initialize Map Grid failed!"));
		return FALSE;
	}

	// �������
	m_GamePlayer.SetWorld( &m_World );
	m_GamePlayer.Respawn();

	// ��Ϸ�߼�
	g_GameLogic.Init( this );

	// ���ű�������
	int nIndex = 1;//rand() % 2;
	TCHAR szBgFile[128] = { 0 };
	_stprintf_s( szBgFile, _countof(szBgFile), _T("res/bg%d.mp3"), nIndex );
	Tank2017::PlayMusic( szBgFile, true );

	// ���߼���ʱ��
	SetTimer( IDI_TANK2017_UPDATE, 30, NULL );

	return 0;
}




void GameFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if ( nIDEvent == IDI_TANK2017_UPDATE )
	{
		//������Ϸ��ͼ
		m_GameView.InvalidateRect( NULL, FALSE );

		//������Ϸ��Ϣ��ͼ
		m_GameInfoView.InvalidateRect( NULL, FALSE );

		if ( g_GameLogic.IsStarted() && !g_GameLogic.IsPaused() )
		{
			//���
			m_GamePlayer.RunLogic();

			//�߼�����
			m_World.RunLogic();
		}
	}


	CWnd::OnTimer(nIDEvent);
}


void GameFrame::OnEventGameStarted()
{
	//�����������
	ShowPanel( Panel_All, false );

	//���õ÷�
	m_GamePlayer.ResetScore();
}

void GameFrame::OnEventGamePaused()
{
	//��ʾ��ͣ��壬��������
	ShowPanel( Panel_Start | Panel_End, false );
	ShowPanel( Panel_Pause, true );
}

void GameFrame::OnEventGameContinue()
{
	//�����������
	ShowPanel( Panel_All, false );
}

void GameFrame::OnEventGameEnded()
{
	//��ʾ������壬��������
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if ( nChar == VK_ESCAPE )
	{
		if ( g_GameLogic.IsStarted() && !g_GameLogic.IsPaused() )
		{
			//��Ϸ��ͣ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
