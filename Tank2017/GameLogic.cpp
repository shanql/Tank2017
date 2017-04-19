#include "stdafx.h"
#include "GameLogic.h"
#include "GamePlayer.h"
#include "IGameEventSink.h"


//全局变量
GameLogic	g_GameLogic;


GameLogic::GameLogic(void)
{
	m_Status = GAME_NULL;
	m_nCurLevel = 0;
}


GameLogic::~GameLogic(void)
{
}


bool GameLogic::Init( IGameEventSink* pGameEventSink )
{
	// 设置事件回调
	ASSERT( pGameEventSink != nullptr );
	if ( !pGameEventSink )
	{
		return false;
	}
	m_pGameEventSink = pGameEventSink;

	// 重置数据
	resetData();

	return true;
}


void GameLogic::Start()
{
	if ( m_Status != GAME_NULL )
	{
		TRACE( _T("game have stated already!"));
		return;
	}

	m_nCurLevel = 1;
	changeStatus( GAME_RUNNING );
// 	m_Status = GAME_RUNNING;
// 	if ( m_pGameEventSink )
// 	{
// 		m_pGameEventSink->OnEventGameStarted();
// 	}

}

void GameLogic::ReStart()
{
	resetData();
	Start();
}

void GameLogic::Pause()
{
	if ( IsStarted() )
	{
		changeStatus( GAME_PAUSE );
// 		m_Status = GAME_PAUSE;
// 		if ( m_pGameEventSink )
// 		{
// 			m_pGameEventSink->OnEventGamePaused();
// 		}
	}
}


void GameLogic::Contiune()
{
	if ( !IsPaused() )
	{
		TRACE(_T("status not paused!!!"));
		return;
	}

	//m_Status = GAME_RUNNING;
	changeStatus( GAME_RUNNING );
}


void GameLogic::OnEventScore( GamePlayer* pPlayer )
{
	if ( !pPlayer )
	{
		ASSERT( FALSE );
		return;
	}

	// 获取当前游戏等级数据
	const LevelData* pCurLvData = getLevelData( GetCurLv() ); 
	if ( !pCurLvData )
	{
		TRACE(_T("invalid pCurLvData"));
		return;
	}

	if ( pPlayer->GetScore() < pCurLvData->m_nPassScore )
	{
		return;
	}

	// 判断游戏是否结束
	if ( GetCurLv() < GetMaxLv() )
	{
		//继续下一关
		m_nCurLevel++;
	}
	else
	{
		//游戏结束
		changeStatus( GAME_OVER );
// 		m_Status = GAME_OVER;
// 		if ( m_pGameEventSink )
// 		{
// 			m_pGameEventSink->OnEventGameEnded();
// 		}
	}

}

int GameLogic::GetMaxLv() const
{
	return m_LvDataArray.size();
}

int GameLogic::GetCurLv() const
{
	return m_nCurLevel;
}

int GameLogic::GetCurPassScore() const
{
	const LevelData* pData = getLevelData( GetCurLv() );
	if ( !pData )
	{
		return 0;
	}

	return pData->m_nPassScore;
}

const LevelData* GameLogic::getLevelData( int nLevel ) const
{
	if ( nLevel < 1 || nLevel > (int)m_LvDataArray.size() )
	{
		return nullptr;
	}
	return &(m_LvDataArray.at(nLevel-1));
}

void GameLogic::changeStatus( GameStatus newStatus )
{
	if ( m_Status == newStatus )
	{
		return;
	}

	GameStatus oldStatus = m_Status;
	m_Status = newStatus;

	switch( newStatus )
	{
	case GAME_RUNNING:
		{
			if ( oldStatus == GAME_PAUSE )
			{
				//继续游戏
				if ( m_pGameEventSink )
				{
					m_pGameEventSink->OnEventGameContinue();
				}
			}
			else
			{
				//游戏新开始
				if ( m_pGameEventSink )
				{
					m_pGameEventSink->OnEventGameStarted();
				}
			}
			break;
		}
	case GAME_PAUSE:
		{
			if ( m_pGameEventSink )
			{
				//游戏暂停
				m_pGameEventSink->OnEventGamePaused();
			}
			break;
		}
	case GAME_OVER:
		{
			if ( m_pGameEventSink )
			{
				//游戏结束
				m_pGameEventSink->OnEventGameEnded();
			}
			break;
		}
	}

	
}

void GameLogic::resetData()
{
	m_Status = GAME_NULL;
	m_nCurLevel = 0;
	m_LvDataArray.clear();

	// 构造游戏等级数据
	for( int i = 0; i < 3; ++i )
	{
		LevelData mLevel;
		mLevel.m_nLevel = 1;
		mLevel.m_nPassScore = 5 + i * 3;
		m_LvDataArray.push_back(mLevel);
	}
}
