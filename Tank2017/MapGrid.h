#pragma once

#include "Entity/Entity.h"
#include "IBulletHitSink.h"

// namespace tst_MapGrid {
// 	class TestMapGrid;
// }


// 网格单元
class GridUnit
{
public:
	/**
	 * @brief 加入实体，已在列表中的则不加入
	*/
	bool Add( Entity* pEntity )
	{
		for( auto it = m_EntityList.begin(); it != m_EntityList.end(); ++it )
		{
			if ( *it == pEntity )
			{
				return false;
			}
		}

		m_EntityList.push_back( pEntity );
		return true;
	}

	/**
	 * @brief 移除实体
	*/
	bool Remove( Entity* pEntity )
	{
		for( auto it = m_EntityList.begin(); it != m_EntityList.end(); ++it )
		{
			if ( *it == pEntity )
			{
				m_EntityList.erase( it );
				return true;
			}
		}
		return false;
	}

	/**
	 * @brief 获取数量
	*/
	int Count() const { return (int)(m_EntityList.size()); }

	/**
	 * @brief 遍历列表
	*/
	Entity* Enum( int nIndex )
	{
		if ( nIndex < 0 || nIndex >= (int)(m_EntityList.size()) )
		{
			return nullptr;
		}

		return m_EntityList.at( nIndex );
	}

private:
	std::vector<Entity*> m_EntityList;	///< 实体列表 
};

// 地图网格类
class MapGrid
{
	//friend class TestMapGrid;
public:
	//static const int s_nGridUnitSize = 12;	///< 网格单元大小(实体最小单元）

	MapGrid(void);
	virtual ~MapGrid(void);

	/**
	 * @brief 设置击中回调
	*/
	void SetBulletHitSink( IBulletHitSink* pSink ) { m_pBulletHitSink = pSink; }

	/**
	 * @brief 地图初始化
	 * @param nWidth 网格行单元个数
	 * @param nHeight 网格列单元个数
	*/
	bool Initialize( int nWidth, int nHeight );


	/**
	 * @brief 是否可以移动到某位置
	 * @param xPos 目标点x坐标
	 * @param yPos 目标点y坐标
	*/
	bool CanMove( Entity* pEntity, int xPos, int yPos );


	/**
	 * @brief 保持原方向移动
	 * @param nStep 移动的格子数
	*/
	//bool ContiuneMove( Entity* pEntity, int nStep );

	/**
	 * @brief 实体移动
	 * @param xPos 目标点x坐标
	 * @param yPos 目标点y坐标
	*/
	bool MoveEntity( Entity* pEntity, int xPos, int yPos );

	/**
	 * @brief 获取实体在某朝向上的相邻实体
	 * @return 无相邻实体返回nullptr,否则返回相应实体
	*/
	//Entity* GetAdjacentEntity( Entity* pEntity, PosDir enDir );

	/**
	 * @brief 检测子弹是否击中
	*/
	void CheckBullteHit( Bullet* pBullet );

	/**
	 * @brief 实体碰撞检测
	*/
	//void CheckCollision( Entity* pEntity );

	/**
	 * @brief 移除实体
	*/
	void RemoveEntity( Entity* pEntity );

	/**
	 * @brief 获取实体
	 * @param xPos 坐标x
	 * @param yPos 坐标y
	 * @return 无实体返回nullptr, 有则返回相应实体
	*/
	//Entity* GetEntity( int xPos, int yPos );

	/**
	 * @brief 判断坐标点是否有效
	*/
// 	bool IsVaildPos( int xPos, int yPos, int nEntityWidth = 0,
// 		int nEntityHeight = 0 );
	bool IsVaildPos( int xPos, int yPos );

	/**
	 * @brief 判断坐标点是否可重生实体
	*/
	bool CanRespawn( int xPos, int yPos, 
		int nEntityWidth, int nEntityHeight );

	/**
	 * @brief 地图宽
	*/
	int GetWidth() const { return m_nWidth;}

	/**
	 * @brief 地图高
	*/
	int GetHeight() const { return m_nHeight; }

	/**
	 * @brief 是否可穿透
	*/
	//bool CanCross()

private:
	/**
	 * @brief 设置实体
	 * @param xPos 坐标x
	 * @param yPos 坐标y
	*/
	void addEntity( Entity* pEntity, int xPos, int yPos );

	/**
	 * @brief 获取地图实体列表索引
	*/
	int getMapIndex( int xPos, int yPos );

	/**
	 * @brief 子弹是否击中
	*/
	//bool isBulletHit( Bullet* pBullet, Entity* pEntity );

	/**
	 * @brief 在指定位置，指定方向上进行子弹命中检测
	 * @param pSrcEntity 发起检测的实体
	 * @param mCheckPos 检测的位置点
	 * @param enCheckDir 检测的方向 
	*/
	//void checkBulletHitByPos( Entity* pSrcEntity, POINT mCheckPos, PosDir enCheckDir );


private:
	int m_nWidth;		///< 地图宽
	int m_nHeight;		///< 地图高
	//Entity** m_pMap;		///< 地图（二维地图）
	GridUnit* m_pMap;	///< 地图（二维地图）
	IBulletHitSink* m_pBulletHitSink;	///< 子弹击中回调
};

