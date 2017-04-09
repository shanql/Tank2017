#pragma once

class BattleWorld;
class GamePlayer;

/*!
 * \class GameView
 *
 * \brief 游戏视图
 *
 * \author shanql
 * \date 2017/04/09
 */
class GameView: 
	public CWnd
{
public:
	GameView(void);
	virtual ~GameView(void);

	/**
	 * @brief 设置世界指针
	*/
	void SetWorld( BattleWorld* pWorld );


	/**
	 * @brief 设置玩家角色指针
	*/
	void SetGamePlayer( GamePlayer* pPlayer);

	

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();

private:
	/**
	 * @brief 绘制
	*/
	void draw( CDC* pDC );
	

private:
	BattleWorld* m_pWorld;				///< 世界指针对象
	GamePlayer* m_pGamePlayer;			///< 玩家角色指针

	CDC m_MemoryDc;						///< 缓冲区dc
	CBitmap m_MemoryBmp;				///< 缓冲区位图

};

