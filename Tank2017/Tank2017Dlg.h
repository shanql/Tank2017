
// Tank2017Dlg.h : ͷ�ļ�
//

#pragma once

#include <vector>
#include "PlayerTank.h"
#include "MapGrid.h"
#include "BattleWorld.h"
#include "GamePlayer.h"
#include "GameInfoView.h"
#include "GameView.h"


// CTank2017Dlg �Ի���
class CTank2017Dlg : public CDialogEx
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


public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);


private:
	GameView m_GameView;			///< ��Ϸ��ͼ
	GameInfoView m_GameInfoView;	///< ��Ϸ��Ϣ��ͼ
	GamePlayer m_GamePlayer;		///< ���
	BattleWorld m_World;			///< ����

	//CButton	m_btnStart;					///< ��ʼ��ť
	
};
