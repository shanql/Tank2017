#pragma once

/*!
 * \class LevelData 
 *
 * \brief 游戏等级数据
 *
 * \author shanql
 * \date 2017/04/10
 */
struct LevelData
{
public:
	LevelData()
	{
		m_nLevel = 0;
		m_nPassScore = 0;
	}

	int m_nLevel;		///< 等级
	int m_nPassScore;	///< 通关分数
};
typedef std::vector<LevelData> LevelDataArray;


/**
 * @brief 游戏状态
*/
enum GameStatus
{
	GAME_NULL,			///< 游戏未开启
	GAME_RUNNING,		///< 游戏运行中
	GAME_PAUSE,			///< 游戏暂停
	GAME_OVER,			///< 游戏结束
};


// 前向场景
class GamePlayer;

/*!
 * \class GameLogic
 *
 * \brief 游戏逻辑类
 *
 * \author shanql
 * \date 2017/04/10
 */
class GameLogic
{
public:
	GameLogic(void);
	virtual ~GameLogic(void);

	/**
	 * @brief 初始数据
	*/
	bool Init();

	/**
	 * @brief 开始游戏
	*/
	void Start();

	/**
	 * @brief 暂停游戏
	*/
	void Pause();

	/**
	 * @brief 继续游戏
	*/
	void Contiune();


	/**
	 * @brief 是否已开始
	*/
	bool IsStarted() { return bool(m_Status != GAME_NULL); }

	/**
	 * @brief 是否暂停
	*/
	bool IsPaused() const { return bool(m_Status == GAME_PAUSE); }

	/**
	 * @brief 得分事件
	*/
	void OnEventScore( GamePlayer* pPlayer );

	/**
	 * @brief 获取游戏最大等级
	*/
	int GetMaxLv() const;

	/**
	 * @brief 获取当前游戏等级
	*/
	int GetCurLv() const;


private:
	/**
	 * @brief 获取等级数据
	*/
	const LevelData* getLevelData( int nLevel ) const;
	/**
	 * @brief 游戏开始事件
	*/
	//void onEventStart();

	/**
	 * @brief 游戏暂停事件
	*/
	//void onEventPause();

	/**
	 * @brief 游戏结束事件
	*/
	//void onEventGameEnd();

	/**
	 * @brief 
	*/
	void onEventLevelStart();

	/**
	 * @brief 
	*/
	void onEventLevelEnd();

private:
	GameStatus m_Status;		///< 游戏状态
	int m_nCurLevel;			///< 当前游戏等级
	LevelDataArray m_LvDataArray;	///< 游戏等级数据
};

