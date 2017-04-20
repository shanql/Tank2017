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
 * @brief ������Ͷ���
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
 * \brief ��Ϸ�����
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
	 * @brief ��ʼ��
	*/
	BOOL Init();

	/**
	 * @brief ���������ʾ״̬
	 * @param cbPanel �������, ֧����������Ӷ����ƶ�����
	 * @param bShow �Ƿ���ʾ
	*/
	void ShowPanel( PanelType cbPanel, bool bShow );


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
	virtual void OnEventGameContinue() override;

	/**
	 * @brief ��Ϸ�����¼�
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
	 * @brief ���������ʾ״̬
	 * @param bShow �Ƿ���ʾ
	*/
	void showPanel( CWnd& mPanel, bool bShow );

	
private:
	HICON m_hIcon;					///< ����ͼ��
	GameView m_GameView;			///< ��Ϸ��ͼ
	GameInfoView m_GameInfoView;	///< ��Ϸ��Ϣ��ͼ
	GamePlayer m_GamePlayer;		///< ���
	BattleWorld m_World;			///< ����

	StartPanel m_StartPanel;		///< ��ʼ���
	PausePanel m_PausePanel;		///< ��ͣ���
	EndPanel m_EndPanel;			///< �������
	
};


