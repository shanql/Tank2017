#pragma once

#include "entity.h"


class BulletAi;

//×Óµ¯ÊµÌå
class Bullet :
	public Entity
{
public:
	Bullet(void);
	virtual ~Bullet(void);

	virtual void CreateAi() override;
};

