#pragma once

#include "aiobject.h"

class Bullet;


//�ӵ�ai
class BulletAi :
	public AiObject
{
public:
	BulletAi(Bullet* pEntity );
	virtual ~BulletAi(void);

	virtual void Run() override;

private:
	Bullet* m_pBullet;
};

