#pragma once

class BattleWorld;
class GamePlayer;

/*!
 * \class GameView
 *
 * \brief ��Ϸ��ͼ
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
	 * @brief ��������ָ��
	*/
	void SetWorld( BattleWorld* pWorld );


	/**
	 * @brief ������ҽ�ɫָ��
	*/
	void SetGamePlayer( GamePlayer* pPlayer);

	

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();

private:
	/**
	 * @brief ����
	*/
	void draw( CDC* pDC );
	

private:
	BattleWorld* m_pWorld;				///< ����ָ�����
	GamePlayer* m_pGamePlayer;			///< ��ҽ�ɫָ��

	CDC m_MemoryDc;						///< ������dc
	CBitmap m_MemoryBmp;				///< ������λͼ

};

