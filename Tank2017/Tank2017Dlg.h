
// Tank2017Dlg.h : ͷ�ļ�
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


// CTank2017Dlg �Ի���
class CTank2017Dlg : public CDialogEx, public IGameEventSink
{
// ����
public:
	CTank2017Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TANK2017_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	 * @brief ��ʼ��Ϸ
	*/
	afx_msg LRESULT OnGameStart(WPARAM wParam, LPARAM lParam);

	/**
	 * @brief ��Ϸ����
	*/
	afx_msg LRESULT OnGameEnd(WPARAM wParam, LPARAM lParam);

	/**
	 * @brief ��ͣ��Ϸ
	*/
	afx_msg LRESULT OnGamePause(WPARAM wParam, LPARAM lParam);

	/**
	 * @brief ������Ϸ
	*/
	afx_msg LRESULT OnGameContinue(WPARAM wParam, LPARAM lParam);

public:
	/**
	 * @brief ���������ʾ״̬
	 * @param bShow �Ƿ���ʾ
	*/
	void ShowPanel( CWnd& mPanel, bool bShow );

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);


	/**
	 * @brief ��Ϸ��ʼ�¼�
	*/
	virtual void OnEventGameStarted() override;

	/**
	 * @brief ��Ϸ��ͣ�¼�
	*/
	virtual void OnEventGamePaused() override;

	/**
	 * @brief ��Ϸ�����¼�
	*/
	virtual void OnEventGameEnded() override;


private:
	GameView m_GameView;			///< ��Ϸ��ͼ
	GameInfoView m_GameInfoView;	///< ��Ϸ��Ϣ��ͼ
	GamePlayer m_GamePlayer;		///< ���
	BattleWorld m_World;			///< ����
	GameLogic m_GameLogic;			///< ��Ϸ�߼�

	StartPanel m_StartPanel;		///< ��ʼ���
	PausePanel m_PausePanel;		///< ��ͣ���
	EndPanel m_EndPanel;			///< �������

	//CButton	m_btnStart;					///< ��ʼ��ť

};
