#pragma once

#include <vector>
#include "IGameEventSink.h"
#include "PlayerTank.h"
#include "MapGrid.h"
#include "BattleWorld.h"
#include "GamePlayer.h"
#include "GameInfoView.h"
#include "GameView.h"
#include "GameLogic.h"
#include "UI\StartPanel.h"
#include "UI\PausePanel.h"
#include "UI\EndPanel.h"

/**
 * @brief 面板类型定义
*/
#define		Panel_Start		(0x1)
#define		Panel_Pause		(0x2)
#define		Panel_End		(0x4)
#define		Panel_All		(	Panel_Start|\
								Panel_Pause|\
								Panel_End )
typedef unsigned char PanelType;



/*!
 * \class GameFrame
 *
 * \brief 游戏框架类
 *
 * \author shanql
 * \date 2017/04/19
 */
class GameFrame : public CFrameWnd, public IGameEventSink
{
	DECLARE_DYNAMIC(GameFrame)

public:
	GameFrame();
	virtual ~GameFrame();

	/**
	 * @brief 初始化
	*/
	BOOL Init();

	/**
	 * @brief 设置面板显示状态
	 * @param cbPanel 面板类型, 支持与操作，从而控制多个面板
	 * @param bShow 是否显示
	*/
	void ShowPanel( PanelType cbPanel, bool bShow );


	/**
	 * @brief 游戏开始事件
	*/
	virtual void OnEventGameStarted() override;

	/**
	 * @brief 游戏暂停事件
	*/
	virtual void OnEventGamePaused() override;

	/**
	 * @brief 游戏继续事件
	*/
	virtual void OnEventGameContinue() override;

	/**
	 * @brief 游戏结束事件
	*/
	virtual void OnEventGameEnded() override;


protected:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);

private:
	/**
	 * @brief 设置面板显示状态
	 * @param bShow 是否显示
	*/
	void showPanel( CWnd& mPanel, bool bShow );

	
private:
	HICON m_hIcon;					///< 程序图标
	GameView m_GameView;			///< 游戏视图
	GameInfoView m_GameInfoView;	///< 游戏信息视图
	GamePlayer m_GamePlayer;		///< 玩家
	BattleWorld m_World;			///< 世界

	StartPanel m_StartPanel;		///< 开始面板
	PausePanel m_PausePanel;		///< 暂停面板
	EndPanel m_EndPanel;			///< 结束面板
	
};


