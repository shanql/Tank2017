#include "stdafx.h"
#include "GameLogic.h"
#include "GamePlayer.h"
#include "IGameEventSink.h"


//ȫ�ֱ���
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
	// �����¼��ص�
	ASSERT( pGameEventSink != nullptr );
	if ( !pGameEventSink )
	{
		return false;
	}
	m_pGameEventSink = pGameEventSink;

	// ��������
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

	// ��ȡ��ǰ��Ϸ�ȼ�����
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

	// �ж���Ϸ�Ƿ����
	if ( GetCurLv() < GetMaxLv() )
	{
		//������һ��
		m_nCurLevel++;
	}
	else
	{
		//��Ϸ����
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
				//������Ϸ
				if ( m_pGameEventSink )
				{
					m_pGameEventSink->OnEventGameContinue();
				}
			}
			else
			{
				//��Ϸ�¿�ʼ
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
				//��Ϸ��ͣ
				m_pGameEventSink->OnEventGamePaused();
			}
			break;
		}
	case GAME_OVER:
		{
			if ( m_pGameEventSink )
			{
				//��Ϸ����
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

	// ������Ϸ�ȼ�����
	for( int i = 0; i < 3; ++i )
	{
		LevelData mLevel;
		mLevel.m_nLevel = 1;
		mLevel.m_nPassScore = 5 + i * 3;
		m_LvDataArray.push_back(mLevel);
	}
}
