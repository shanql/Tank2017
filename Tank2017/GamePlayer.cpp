#include "stdafx.h"
#include "GamePlayer.h"
#include "PlayerTank.h"
#include "GlobalFunction.h"
#include "Resource.h"
#include "MsgDefine.h"


GamePlayer::GamePlayer(void)
{
	m_pTank = nullptr;
	m_pWorld = nullptr;
	m_nRespawnCnt = -1;
	m_nScore = 0;
	m_bMoveKeyDown = false;
	m_nMoveCutdown = 50;
	m_nFireCutdown = 500;
	m_dwLastMoveTick = 0;
	m_dwFireLastTick = 0;
}


GamePlayer::~GamePlayer(void)
{
}

void GamePlayer::RunLogic()
{
	DWORD dwCurrentTick = GetCurrentTime();

	// 移动控制
	if ( (int)( dwCurrentTick - m_dwLastMoveTick ) > m_nMoveCutdown )
	{
		m_dwLastMoveTick = dwCurrentTick;
		if ( m_bMoveKeyDown && m_pTank && m_pWorld )
		{
			m_pWorld->ContiuneMove( m_pTank );
		}
	}
}

void GamePlayer::OnEventKeyDown( int key )
{
	if ( !m_pTank )
	{
		return;
	}

	DWORD dwCurrentTick = GetCurrentTime();
	switch( key )
	{
	case 'A':
		{
			m_bMoveKeyDown = TRUE;
			if ( m_pTank->GetDir() != enDirLeft )
			{
				m_pTank->SetDir( enDirLeft );
			}
			CString strLog;
			strLog.Format( _T("Left key down %ld\n"), dwCurrentTick );
			TRACE( strLog );
			break;
		}

	case 'D':
		{
			m_bMoveKeyDown = TRUE;
			if ( m_pTank->GetDir() != enDirRight )
			{
				m_pTank->SetDir( enDirRight );
			}

// 			CString strLog;
// 			strLog.Format( _T("Right key down %ld\n"), dwCurrentTick );
// 			TRACE( strLog );
			break;
		}
	case 'W':
		{
			m_bMoveKeyDown = TRUE;
			if ( m_pTank->GetDir() != enDirUp )
			{
				m_pTank->SetDir( enDirUp );
			}
			break;
		}
	case 'S':
		{
			m_bMoveKeyDown = TRUE;
			if ( m_pTank->GetDir() != enDirDown )
			{
				m_pTank->SetDir( enDirDown );
			}
			break;
		}
	case 'J':
		{
			//暂时只能拥有一颗子弹， PlayGameSound在同一时刻只能播一个
			if ( (int)(dwCurrentTick - m_dwFireLastTick) > m_nFireCutdown &&
				m_pTank->GetOwnEntityCount() <= 0  )
			{
				if ( m_pTank->Fire() )
				{
					Tank2017::PlayGameSound( MAKEINTRESOURCE(TANK_FIRE) );
					//Tank2017::PlayMusic( _T("res/tank_fire.m4a"));
				}
				m_dwFireLastTick = dwCurrentTick;
			}
// 			CString strLog;
// 			strLog.Format( _T("Space key down %ld\n"), dwCurrentTick );
// 			TRACE( strLog );
			break;
		}
	}
}


void GamePlayer::OnEventKeyUp( int key )
{
	switch( key )
	{
// 	case VK_DOWN:
// 	case VK_UP:
// 	case VK_LEFT:
// 	case VK_RIGHT:
	case 'W':
	case 'A':
	case 'S':
	case 'D':
		{
			m_bMoveKeyDown = false;
			break;
		}
	}
}

void GamePlayer::Respawn()
{
	if ( !m_pWorld )
	{
		ASSERT( false );
		return;
	}

	POINT mPos = m_pWorld->GetValidPos( 
		Tank2017::gTankWidth / Tank2017::gGridUnitSize,
		Tank2017::gTankHeight / Tank2017::gGridUnitSize );
	m_pTank = dynamic_cast<PlayerTank*>(
		m_pWorld->CreateEntity( enPlayerTank, 
		mPos.x, mPos.y, 1, enDirUp ));
	if ( m_pTank )
	{
		m_pTank->RegisterEventObserver( this );
	}
}


void GamePlayer::OnEventBeenKilled()
{
	m_pTank = nullptr;
	if ( m_nRespawnCnt >0 )
	{
		m_nRespawnCnt--;
		if ( m_nRespawnCnt >= 0 )
		{
			Respawn();
		}
	}
	// 无限重生
	else if ( m_nRespawnCnt == -1 )
	{
		Respawn();
	}
}

void GamePlayer::OnEventKillTarget( Entity* pKillTarget )
{
	if ( !pKillTarget )
	{
		return;
	}

	//Tank2017::PlayGameSound( MAKEINTRESOURCE(TANK_BOMB) );

	if ( pKillTarget->GetType() == enOpposingTank )
	{
		++m_nScore;
		g_GameLogic.OnEventScore(this);
	}
}
