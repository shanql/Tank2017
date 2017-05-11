#pragma once


// MapEditorWnd
/*!
 * \class MapEditorWnd
 *
 * \brief ��������
 *
 * \author shanql
 * \date 2017/04/23
 */
class MapEditorWnd : public CFrameWnd
{
	DECLARE_DYNAMIC(MapEditorWnd)

public:
	MapEditorWnd();
	virtual ~MapEditorWnd();

protected:
	DECLARE_MESSAGE_MAP()

	//��Ϣ����
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnAppAbout();
	afx_msg void OnAppExit();
	afx_msg void OnPaint();
	afx_msg void OnIron1Wall();
	afx_msg void OnIron4Wall();
	afx_msg void OnNormalWall();
	afx_msg void OnUpdateIron1Wall(CCmdUI *pCmdUI);
	afx_msg void OnUpdateIron4Wall(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNormalWall(CCmdUI *pCmdUI);

private:
	CMenu m_Menu;	
	CToolBar m_ToolBar;
};


