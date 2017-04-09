#include "stdafx.h"
#include "GameView.h"
#include "BattleWorld.h"
#include "GamePlayer.h"


BEGIN_MESSAGE_MAP(GameView, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

GameView::GameView(void)
{
	m_pWorld = nullptr;
	m_pGamePlayer = nullptr;
}


GameView::~GameView(void)
{
}

void GameView::SetWorld( BattleWorld* pWorld )
{
	m_pWorld = pWorld;
}

void GameView::SetGamePlayer( GamePlayer* pPlayer)
{
	m_pGamePlayer = pPlayer;
}

int GameView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}


	// 创建缓冲DC
	CRect clientRect;
	GetClientRect( clientRect );
	CDC* pDC = this->GetDC();
	m_MemoryDc.CreateCompatibleDC( pDC );
	m_MemoryBmp.CreateCompatibleBitmap( pDC,
		clientRect.Width(), clientRect.Height() );
	m_MemoryDc.SelectObject( &m_MemoryBmp );
	this->ReleaseDC(pDC);
	pDC = nullptr;

	return 0;
}


void GameView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	draw( &dc );
}


void GameView::draw( CDC* pDC )
{
	if ( m_pWorld && pDC )
	{	
		//绘制函数
		CRect rect;
		GetClientRect(&rect);
		m_MemoryDc.FillSolidRect( 0, 0, rect.Width(), 
			rect.Height(), RGB( 0, 0, 0 ) );
		m_pWorld->RunDraw( &m_MemoryDc );
		pDC->BitBlt( 0, 0, rect.Width(), rect.Height(), &m_MemoryDc, 0, 0, SRCCOPY );

	}
}