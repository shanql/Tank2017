#pragma once

#include <vector>
#include "Entity/Entity.h"
#include "Entity/Bullet.h"
#include "IBulletHitSink.h"
#include "MapGrid.h"


/*!
 * \class BattleWorld
 *
 * \brief 世界类
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
	 * @brief 初始化世界
	*/
	bool Initialize( int nWidth, int nHeight);


	/**
	 * @brief 绘制
	*/
	void RunDraw( CDC* pDc );


	/**
	 * @brief 逻辑
	*/
	void RunLogic();

	
	/**
	 * @brief 创建实体
	 * @param enEntityType 实体类型
	 * @param xPos 出生点x坐标
	 * @param yPos 出生点y坐标
	 * @param nSpeed 实体运动速度
	 * @param enDir 实体方向
	 * @return 创建成功，返回实体指针, 否则返回nullptr
	*/
	Entity* CreateEntity( EntityType enEntityType, int xPos, int yPos, 
		int nSpeed = 0, PosDir enDir = enDirLeft );

	/**
	 * @brief 销毁实体
	*/
	//void DestroyEntity( Entity* pEntity );

	/**
	 * @brief 移动
	*/
	bool Move( Entity* pEntity, int xPos, int yPos );

	/**
	* @brief 保持原方向移动
	*/
	bool ContiuneMove( Entity* pEntity );

	/**
	 * @brief 子弹命中事件
	*/
	virtual void OnEventBulletHit( Bullet* pBullet, Entity* pTargetEntity ) override;

	/**
	 * @brief 获取实体表
	*/
	//EntityArray& GetEntityArray() { return m_EntityArray; } 

	/**
	 * @brief 获取世界宽
	*/
	int GetWidth() const { return m_MapGrid.GetWidth(); }

	/**
	 * @brief 获取世界高
	*/
	int GetHeight() const { return m_MapGrid.GetHeight(); }

	/**
	 * @brief 获取有效点
	 * @param nEntityWidth 实体宽
	 * @param nEntityHeight 实体高
	*/
	POINT GetValidPos( int nEntityWidth, int nEntityHeight );


private:
	/**
	 * @brief 一个实体进入世界
	*/
	void enterWorld( Entity* pEntity );

	/**
	 * @brief 一个实体离开世界
	*/
	void leaveWorld( Entity* pEntity );

	/**
	 * @brief 生成敌方坦克
	*/
	void autoGenerateOpposingTank();

	/**
	 * @brief 执行AI逻辑
	*/
	void runAiLogic();


	/**
	 * @brief 碰撞检测
	*/
	void checkCollision();

	/**
	 * @brief 清理
	*/
	void clearWorld();

private:
	EntityArray m_EntityArray;
	MapGrid m_MapGrid;
};

