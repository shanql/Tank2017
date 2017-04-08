#include "stdafx.h"
#include "BulletAi.h"
#include "../Entity/Bullet.h"
#include "../BattleWorld.h"


BulletAi::BulletAi(Bullet* pEntity )
	:m_pBullet( pEntity )
{
}


BulletAi::~BulletAi(void)
{
}


void BulletAi::Run()
{
	if ( m_pBullet )
	{
		BattleWorld* pWorld = m_pBullet->GetWorld();
		if ( pWorld )
		{
			pWorld->ContiuneMove( m_pBullet );
		}
	}
}