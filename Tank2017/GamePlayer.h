#pragma once
#include "entity.h"
#include "BattleWorld.h"

class PlayerTank;

// ��Ϸ�����
class GamePlayer: public IEntityEvent
{
public:
	GamePlayer(void);
	virtual ~GamePlayer(void);

	/**
	 * @brief �����¼�
	*/
	void OnEventKeyDown( int key );

	/**
	 * @brief ���ͷ��¼�
	*/
	void OnEventKeyUp( int key );

	/**
	 * @brief �߼�����
	*/
	void RunLogic();

	/**
	 * @brief ��������ָ��
	*/
	void SetWorld( BattleWorld* pWorld ) { m_pWorld = pWorld; }

	/**
	 * @brief ����
	*/
	void Respawn( );

	virtual void OnEventBeenKilled() override;
	virtual void OnEventKillTarget( Entity* pKillTarget ) override;

	PlayerTank* GetPlayerTank() { return m_pTank; }

	/**
	 * @brief ��ȡ��ǰ�÷�
	*/
	int GetScore() const { return m_nScore; }

	/**
	 * @brief ���õ÷�
	*/
	void ResetScore() { m_nScore = 0; }

	/**
	 * @brief ��ȡ��������
	*/
	int GetRespawnCnt() const { return m_nRespawnCnt; }
private:
	PlayerTank* m_pTank;
	BattleWorld* m_pWorld;
	int m_nRespawnCnt;					///< ��������
	int m_nScore;						///< �÷�
	DWORD m_dwLastMoveTick;				///< �ϴ��ƶ���tick
	bool m_bMoveKeyDown;				///< �ƶ����Ƿ���
	int m_nMoveCutdown;					///< �ƶ�cdʱ��
	int m_nFireCutdown;					///< ����cdʱ��
	//DWORD m_dwLastTickMoveKeyDown;		///< �ϴ��ƶ�����tick
	DWORD m_dwFireLastTick;				///< �ϴο���tick
};

