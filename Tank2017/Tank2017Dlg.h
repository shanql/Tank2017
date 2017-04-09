
// Tank2017Dlg.h : 头文件
//

#pragma once

#include <vector>
#include "PlayerTank.h"
#include "MapGrid.h"
#include "BattleWorld.h"
#include "GamePlayer.h"
#include "GameInfoView.h"
#include "GameView.h"


// CTank2017Dlg 对话框
class CTank2017Dlg : public CDialogEx
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


public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);


private:
	GameView m_GameView;			///< 游戏视图
	GameInfoView m_GameInfoView;	///< 游戏信息视图
	GamePlayer m_GamePlayer;		///< 玩家
	BattleWorld m_World;			///< 世界

	//CButton	m_btnStart;					///< 开始按钮
	
};
