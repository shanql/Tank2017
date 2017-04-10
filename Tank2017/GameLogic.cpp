#include "stdafx.h"
#include "GameLogic.h"
#include "GamePlayer.h"


GameLogic::GameLogic(void)
{
	m_Status = GAME_NULL;
	m_nCurLevel = 0;
}


GameLogic::~GameLogic(void)
{
}

bool GameLogic::Init()
{
	m_Status = GAME_NULL;
	m_nCurLevel = 0;
	m_LvDataArray.clear();

	// 构造游戏等级数据
	for( int i = 0; i < 5; ++i )
	{
		LevelData mLevel;
		mLevel.m_nLevel = 1;
		mLevel.m_nPassScore = 10 + i * 5;
		m_LvDataArray.push_back(mLevel);
	}

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
	m_Status = GAME_RUNNING;

}

void GameLogic::Pause()
{
	if ( IsStarted() )
	{
		m_Status = GAME_PAUSE;
	}
}


void GameLogic::Contiune()
{
	if ( !IsPaused() )
	{
		TRACE(_T("status not paused!!!"));
		return;
	}

	m_Status = GAME_RUNNING;
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
	if ( GetCurLv() <GetMaxLv() )
	{
		//继续下一关
		m_nCurLevel++;
	}
	else
	{
		//游戏结束

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

const LevelData* GameLogic::getLevelData( int nLevel ) const
{
	if ( nLevel < 1 || nLevel > (int)m_LvDataArray.size() )
	{
		return nullptr;
	}
	return &(m_LvDataArray.at(nLevel-1));
}