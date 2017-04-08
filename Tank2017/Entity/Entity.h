#pragma once

#include <vector>
#include "GlobalDefine.h"

class Entity;
class BattleWorld;
class AiObject;

// 位置朝向
enum PosDir
{
	enDirNull,
	enDirLeft,		
	enDirRight,
	enDirUp,
	enDirDown,
};


enum EntityType
{
	enEntityNull,	///< 无效实体
	enPlayerTank,	///< 坦克玩家
	enBullet,		///< 子弹
	enOpposingTank,	///< 敌方坦克
	enEntityBorder,	///< 边界
};

enum EntityEvent
{
	enEventHitTarget,	///< 击中目标
	enEventHitted,		///< 被击中
};

// 实体事件
class IEntityEvent
{
public:
	virtual void OnEventBeenKilled() = 0;
	virtual void OnEventKillTarget( Entity* pKillTarget ) = 0;
};



// 实体基类
class Entity
{
public:
	typedef std::vector<Entity*> EntityArray;

	Entity(void);
	virtual ~Entity(void);

	/**
	 * @brief 实例初始化
	*/
	//bool Initialize( LPCTSTR lpszImageFile );
	bool Initialize( int nWidth, int nHeight );


	/**
	 * @brief 注册观察者
	*/
	void RegisterEventObserver( IEntityEvent* pEventObserver );

	/**
	 * @brief 位置设置
	*/
	void SetPos( const POINT& pos ){ m_Pos = pos; }

	/**
	 * @brief 获取位置
	*/
	POINT GetPos() const { return m_Pos; }

	/**
	 * @brief 设置朝向
	*/
	void SetDir( PosDir mDir ) { m_Dir = mDir; }

	/**
	 * @brief 获取朝向
	*/
	PosDir GetDir( ) const { return m_Dir;}

	/**
	 * @brief 设置类型
	*/
	//void SetType( EntityType enType ) { m_enType = enType;}

	/**
	 * @brief 获取类型
	*/
	EntityType GetType() const { return m_enType; }

	/**
	 * @brief 设置世界
	*/
	void SetWorld( BattleWorld* pWorld ) { m_pWorld = pWorld; }

	/**
	 * @brief 获得世界
	*/
	BattleWorld* GetWorld() { return m_pWorld; }

	/**
	 * @brief 获取宽度
	*/
	int GetWidth() const { return m_nWidth;}

	/**
	 * @brief 获取高度
	*/
	int GetHeight() const { return m_nHeight; }

	/**
	 * @brief 设置速度 
	*/
	void SetSpeed( int nSpeed ) { m_nSpeed = nSpeed; }

	/**
	 * @brief 获取速度
	*/
	int GetSpeed() const { return m_nSpeed; }

	/**
	 * @brief 获取ai
	 * @return 无ai的返回nullptr
	*/
	AiObject* GetAi() { return m_pAi; }

	/**
	 * @brief 设置进入世界
	*/
	void SetInWorld( bool bInWorld ) { m_bInWorld = bInWorld; }

	/**
	 * @brief 是否在世界中
	*/
	bool IsInWorld() { return m_bInWorld; }

	/**
	 * @brief 绘制
	*/
	virtual void Draw( CDC* pDC );

	/**
	 * @brief 创建ai
	*/
	virtual void CreateAi() {}

	/**
	 * @brief 被杀响应
	 * @param pEntity 当为nullptr,则表示自杀（如子弹碰到边界），
	 *				  否则指向最后致命一击的实体
	*/
	void OnBeenKilled( Entity* pEntity );

	/**
	 * @brief 杀死目标响应
	 * @param pTarget 其它实体对象
	*/
	void OnKillTarget( Entity* pTarget );


	/**
	 * @brief 移除拥有的实体(切断关系)
	 * @param pEntity 当pEntity==nullptr时，表示移除所有
	 * @note 移除拥有的实体的同时，也会设置拥有的实体的Owner为nullptr
	*/
	void RmvFromOwnEntityList( Entity* pEntity );


	/**
	 * @brief 增加拥有某实体
	 * @note 增加拥有实体的同时，也会设置拥有的实体的Owner为this
	*/
	void AddToOwnEntityList( Entity* pEntity );

	/**
	 * @brief 获取归属者
	*/
	Entity* GetOwner() { return m_pOwner; }

	/**
	 * @brief 设置生命值 
	*/
	void SetHP( int nHP ) { m_nHP = nHP; }

	/**
	 * @brief 获取生命值 
	*/
	int GetHP() const { return m_nHP; }


	/**
	 * @brief 获取拥有的实体个数
	*/
	int GetOwnEntityCount() const { return m_OwnEntityList.size(); }


	/**
	 * @brief 设置归属者
	*/
	void SetOwner( Entity* pOwner ) { m_pOwner = pOwner; }


protected:
	

	POINT m_Pos;				///< 位置
	PosDir m_Dir;				///< 朝向
	EntityType m_enType;		///< 实体类型
	int m_nWidth;				///< 实体宽
	int m_nHeight;				///< 实体高
	int m_nSpeed;				///< 实体运动速度
	int m_nHP;					///< 实体生命值
	bool m_bInWorld;			///< have enter world?
	BattleWorld* m_pWorld;		///< 所在世界
	AiObject* m_pAi;			///< ai
	

	EntityArray m_OwnEntityList; ///< 拥有实体列表
	Entity* m_pOwner;
	std::vector<IEntityEvent*> m_EventObservers;	///< 观察者
};
