#pragma once

/*!
 * \class LevelData 
 *
 * \brief ��Ϸ�ȼ�����
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

	int m_nLevel;		///< �ȼ�
	int m_nPassScore;	///< ͨ�ط���
};
typedef std::vector<LevelData> LevelDataArray;


/**
 * @brief ��Ϸ״̬
*/
enum GameStatus
{
	GAME_NULL,			///< ��Ϸδ����
	GAME_RUNNING,		///< ��Ϸ������
	GAME_PAUSE,			///< ��Ϸ��ͣ
	GAME_OVER,			///< ��Ϸ����
};


// ǰ�򳡾�
class GamePlayer;

/*!
 * \class GameLogic
 *
 * \brief ��Ϸ�߼���
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
	 * @brief ��ʼ����
	*/
	bool Init();

	/**
	 * @brief ��ʼ��Ϸ
	*/
	void Start();

	/**
	 * @brief ��ͣ��Ϸ
	*/
	void Pause();

	/**
	 * @brief ������Ϸ
	*/
	void Contiune();


	/**
	 * @brief �Ƿ��ѿ�ʼ
	*/
	bool IsStarted() { return bool(m_Status != GAME_NULL); }

	/**
	 * @brief �Ƿ���ͣ
	*/
	bool IsPaused() const { return bool(m_Status == GAME_PAUSE); }

	/**
	 * @brief �÷��¼�
	*/
	void OnEventScore( GamePlayer* pPlayer );

	/**
	 * @brief ��ȡ��Ϸ���ȼ�
	*/
	int GetMaxLv() const;

	/**
	 * @brief ��ȡ��ǰ��Ϸ�ȼ�
	*/
	int GetCurLv() const;


private:
	/**
	 * @brief ��ȡ�ȼ�����
	*/
	const LevelData* getLevelData( int nLevel ) const;
	/**
	 * @brief ��Ϸ��ʼ�¼�
	*/
	//void onEventStart();

	/**
	 * @brief ��Ϸ��ͣ�¼�
	*/
	//void onEventPause();

	/**
	 * @brief ��Ϸ�����¼�
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
	GameStatus m_Status;		///< ��Ϸ״̬
	int m_nCurLevel;			///< ��ǰ��Ϸ�ȼ�
	LevelDataArray m_LvDataArray;	///< ��Ϸ�ȼ�����
};

