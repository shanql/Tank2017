
// Tank2017Dlg.h : ͷ�ļ�
//

#pragma once

#include <vector>
#include "PlayerTank.h"
#include "MapGrid.h"
#include "BattleWorld.h"
#include "GamePlayer.h"
#include "GameInfoView.h"


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

	CDC m_MemoryDc;						///< ������dc
	CBitmap m_MemoryBmp;				///< ������λͼ
	int m_nGameWidth;					///< ��Ϸ����
	int m_nGameHeight;					///< ��Ϸ����

	CButton	m_btnStart;					///< ��ʼ��ť

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
