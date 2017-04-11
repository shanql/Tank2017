
// Tank2017Dlg.h : 头文件
//

#pragma once
#include "IGameEventSink.h"

#include <vector>
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


// CTank2017Dlg 对话框
class CTank2017Dlg : public CDialogEx, public IGameEventSink
{
// 构造
public:
	CTank2017Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TANK2017_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();


	DECLARE_MESSAGE_MAP()
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	/**
	 * @brief 开始游戏
	*/
	afx_msg LRESULT OnGameStart(WPARAM wParam, LPARAM lParam);

	/**
	 * @brief 游戏结束
	*/
	afx_msg LRESULT OnGameEnd(WPARAM wParam, LPARAM lParam);

	/**
	 * @brief 暂停游戏
	*/
	afx_msg LRESULT OnGamePause(WPARAM wParam, LPARAM lParam);

	/**
	 * @brief 继续游戏
	*/
	afx_msg LRESULT OnGameContinue(WPARAM wParam, LPARAM lParam);

public:
	/**
	 * @brief 设置面板显示状态
	 * @param bShow 是否显示
	*/
	void ShowPanel( CWnd& mPanel, bool bShow );

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);


	/**
	 * @brief 游戏开始事件
	*/
	virtual void OnEventGameStarted() override;

	/**
	 * @brief 游戏暂停事件
	*/
	virtual void OnEventGamePaused() override;

	/**
	 * @brief 游戏结束事件
	*/
	virtual void OnEventGameEnded() override;


private:
	GameView m_GameView;			///< 游戏视图
	GameInfoView m_GameInfoView;	///< 游戏信息视图
	GamePlayer m_GamePlayer;		///< 玩家
	BattleWorld m_World;			///< 世界
	GameLogic m_GameLogic;			///< 游戏逻辑

	StartPanel m_StartPanel;		///< 开始面板
	PausePanel m_PausePanel;		///< 暂停面板
	EndPanel m_EndPanel;			///< 结束面板

	//CButton	m_btnStart;					///< 开始按钮

};
