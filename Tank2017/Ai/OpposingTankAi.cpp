#include "stdafx.h"
#include "OpposingTankAi.h"
#include "../BattleWorld.h"
#include "Entity/OpposingTank.h"
#include "GlobalFunction.h"
#include "Resource.h"


OpposingTankAi::OpposingTankAi(OpposingTank* pOpposingTank )
	:m_pOpposingTank( pOpposingTank )
{
	m_dwLastTick = 0;
	m_dwFireLastTick = 0;
	m_nSpeed = 80;
	m_nFireSpeed = 1000;
}


OpposingTankAi::~OpposingTankAi(void)
{
}

void OpposingTankAi::Run()
{
	DWORD dwCurTick = GetCurrentTime();
	if ( (int)(dwCurTick - m_dwLastTick) < m_nSpeed )
	{
		return;
	}
	m_dwLastTick = dwCurTick;
	if ( m_pOpposingTank )
	{
		BattleWorld* pWorld = m_pOpposingTank->GetWorld();
		if ( pWorld )
		{
			if ( !( pWorld->ContiuneMove( m_pOpposingTank ) ) )
			{
				PosDir enOldDir = m_pOpposingTank->GetDir();
				PosDir enNewDir = PosDir(rand() % 4 + 1);
				m_pOpposingTank->SetDir( enNewDir );
			}

			// 20%µÄ¿ª»ð¸ÅÂÊ
			if ( int( dwCurTick - m_dwFireLastTick ) > m_nFireSpeed )
			{
				m_dwFireLastTick = dwCurTick;
				int randNum = rand() % 100;
				if ( randNum >= 80 )
				{
					 m_pOpposingTank->Fire();
				}
			}
			
		}
		
	}
}
