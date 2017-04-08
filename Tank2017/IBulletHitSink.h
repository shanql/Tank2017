#pragma  once

class Bullet;
class Entity;
class IBulletHitSink
{
public:
	/**
	 * @brief 子弹命中事件
	 * @param pBullet 子弹对象
	 * @param pTargetEntity 子弹碰撞对象
	*/
	virtual void OnEventBulletHit( Bullet* pBullet, Entity* pTargetEntity ) = 0;
};
