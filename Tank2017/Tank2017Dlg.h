
// Tank2017Dlg.h : 头文件
//

#pragma once

#include <vector>
#include "PlayerTank.h"
#include "MapGrid.h"
#include "BattleWorld.h"
#include "GamePlayer.h"
#include "GameInfoView.h"


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
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	virtual void OnOK();
public:
	afx_msg void OnClose();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);


public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);


private:
	GameInfoView m_GameInfoView;
	GamePlayer m_GamePlayer;
	BattleWorld m_World;

	CDC m_MemoryDc;						///< 缓冲区dc
	CBitmap m_MemoryBmp;				///< 缓冲区位图
	int m_nGameWidth;					///< 游戏区宽
	int m_nGameHeight;					///< 游戏区高

	CButton	m_btnStart;					///< 开始按钮

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
