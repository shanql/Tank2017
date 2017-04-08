// GameInfoView.cpp : 实现文件
//

#include "stdafx.h"
#include "Tank2017.h"
#include "GameInfoView.h"
#include "GamePlayer.h"


// GameInfoView

IMPLEMENT_DYNAMIC(GameInfoView, CWnd)

GameInfoView::GameInfoView()
{
	m_pGamePlayer = nullptr;
}

GameInfoView::~GameInfoView()
{
}


BEGIN_MESSAGE_MAP(GameInfoView, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// GameInfoView 消息处理程序




void GameInfoView::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rect;
	GetClientRect( &rect );

	dc.FillSolidRect( rect.left, rect.top, rect.right, 
		rect.bottom, RGB( 125, 255, 255 ) );

	if ( m_pGamePlayer != nullptr )
	{
		CString strScore;
		strScore.Format( _T("当前得分：%d"), m_pGamePlayer->GetScore() );
		dc.TextOut( 50, rect.Height() / 2, strScore );
	}

	// TODO: 在此处添加消息处理程序代码
	//不为绘图消息调用 CWnd::OnPaint()
}


void GameInfoView::SetGamePlayer( GamePlayer* pGamePlayer )
{
	m_pGamePlayer = pGamePlayer;
}