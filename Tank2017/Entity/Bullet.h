#pragma once

#include "entity.h"


class BulletAi;

//�ӵ�ʵ��
class Bullet :
	public Entity
{
public:
	Bullet(void);
	virtual ~Bullet(void);

	virtual void CreateAi() override;
};

