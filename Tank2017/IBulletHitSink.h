#pragma  once

class Bullet;
class Entity;
class IBulletHitSink
{
public:
	/**
	 * @brief �ӵ������¼�
	 * @param pBullet �ӵ�����
	 * @param pTargetEntity �ӵ���ײ����
	*/
	virtual void OnEventBulletHit( Bullet* pBullet, Entity* pTargetEntity ) = 0;
};
