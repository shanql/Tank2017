#pragma once

#include <vector>
#include "Entity/Entity.h"
#include "Entity/Bullet.h"
#include "IBulletHitSink.h"
#include "MapGrid.h"


/*!
 * \class BattleWorld
 *
 * \brief ������
 *
 * \author shanql
 * \date 2017/03/22
 */
class BattleWorld: public IBulletHitSink
{
public:
	typedef std::vector<Entity*> EntityArray;
	//typedef std::vector<EntityPtr> EntityArray;

	BattleWorld(void);
	virtual ~BattleWorld(void);

	/**
	 * @brief ��ʼ������
	*/
	bool Initialize( int nWidth, int nHeight);


	/**
	 * @brief ����
	*/
	void RunDraw( CDC* pDc );


	/**
	 * @brief �߼�
	*/
	void RunLogic();

	
	/**
	 * @brief ����ʵ��
	 * @param enEntityType ʵ������
	 * @param xPos ������x����
	 * @param yPos ������y����
	 * @param nSpeed ʵ���˶��ٶ�
	 * @param enDir ʵ�巽��
	 * @return �����ɹ�������ʵ��ָ��, ���򷵻�nullptr
	*/
	Entity* CreateEntity( EntityType enEntityType, int xPos, int yPos, 
		int nSpeed = 0, PosDir enDir = enDirLeft );

	/**
	 * @brief ����ʵ��
	*/
	//void DestroyEntity( Entity* pEntity );

	/**
	 * @brief �ƶ�
	*/
	bool Move( Entity* pEntity, int xPos, int yPos );

	/**
	* @brief ����ԭ�����ƶ�
	*/
	bool ContiuneMove( Entity* pEntity );

	/**
	 * @brief �ӵ������¼�
	*/
	virtual void OnEventBulletHit( Bullet* pBullet, Entity* pTargetEntity ) override;

	/**
	 * @brief ��ȡʵ���
	*/
	//EntityArray& GetEntityArray() { return m_EntityArray; } 

	/**
	 * @brief ��ȡ�����
	*/
	int GetWidth() const { return m_MapGrid.GetWidth(); }

	/**
	 * @brief ��ȡ�����
	*/
	int GetHeight() const { return m_MapGrid.GetHeight(); }

	/**
	 * @brief ��ȡ��Ч��
	 * @param nEntityWidth ʵ���
	 * @param nEntityHeight ʵ���
	*/
	POINT GetValidPos( int nEntityWidth, int nEntityHeight );


private:
	/**
	 * @brief һ��ʵ���������
	*/
	void enterWorld( Entity* pEntity );

	/**
	 * @brief һ��ʵ���뿪����
	*/
	void leaveWorld( Entity* pEntity );

	/**
	 * @brief ���ɵз�̹��
	*/
	void autoGenerateOpposingTank();

	/**
	 * @brief ִ��AI�߼�
	*/
	void runAiLogic();


	/**
	 * @brief ��ײ���
	*/
	void checkCollision();

	/**
	 * @brief ����
	*/
	void clearWorld();

private:
	EntityArray m_EntityArray;
	MapGrid m_MapGrid;
};

