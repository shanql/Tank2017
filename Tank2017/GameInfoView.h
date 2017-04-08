#pragma once


class GamePlayer;

// GameInfoView
class GameInfoView : public CWnd
{
	DECLARE_DYNAMIC(GameInfoView)

public:
	GameInfoView();
	virtual ~GameInfoView();

	/**
	 * @brief �������ָ��
	*/
	void SetGamePlayer( GamePlayer* pGamePlayer );

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();

private:
	GamePlayer* m_pGamePlayer;
};


