#include "stdafx.h"
#include "Bullet.h"
#include "Ai/BulletAi.h"
#include "BattleWorld.h"


Bullet::Bullet(void)
{
	m_enType = enBullet;
}


Bullet::~Bullet(void)
{
}

void Bullet::CreateAi()
{
	m_pAi = new BulletAi( this );
}
