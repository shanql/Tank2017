#pragma once
#include "entity.h"
#include "BattleWorld.h"

class PlayerTank;

// 游戏玩家类
class GamePlayer: public IEntityEvent
{
public:
	GamePlayer(void);
	virtual ~GamePlayer(void);

	/**
	 * @brief 按键事件
	*/
	void OnEventKeyDown( int key );

	/**
	 * @brief 键释放事件
	*/
	void OnEventKeyUp( int key );

	/**
	 * @brief 逻辑运行
	*/
	void RunLogic();

	/**
	 * @brief 设置世界指针
	*/
	void SetWorld( BattleWorld* pWorld ) { m_pWorld = pWorld; }

	/**
	 * @brief 出生
	*/
	void Respawn( );

	virtual void OnEventBeenKilled() override;
	virtual void OnEventKillTarget( Entity* pKillTarget ) override;

	PlayerTank* GetPlayerTank() { return m_pTank; }

	/**
	 * @brief 获取当前得分
	*/
	int GetScore() const { return m_nScore; }

	/**
	 * @brief 重置得分
	*/
	void ResetScore() { m_nScore = 0; }

	/**
	 * @brief 获取重生次数
	*/
	int GetRespawnCnt() const { return m_nRespawnCnt; }
private:
	PlayerTank* m_pTank;
	BattleWorld* m_pWorld;
	int m_nRespawnCnt;					///< 重生次数
	int m_nScore;						///< 得分
	DWORD m_dwLastMoveTick;				///< 上次移动的tick
	bool m_bMoveKeyDown;				///< 移动键是否按下
	int m_nMoveCutdown;					///< 移动cd时间
	int m_nFireCutdown;					///< 开火cd时间
	//DWORD m_dwLastTickMoveKeyDown;		///< 上次移动按键tick
	DWORD m_dwFireLastTick;				///< 上次开火tick
};

