#pragma once


// MapEditorWnd
/*!
 * \class MapEditorWnd
 *
 * \brief 主窗口类
 *
 * \author shanql
 * \date 2017/04/23
 */
class MapEditorWnd : public CWnd
{
	DECLARE_DYNAMIC(MapEditorWnd)

public:
	MapEditorWnd();
	virtual ~MapEditorWnd();

protected:
	DECLARE_MESSAGE_MAP()

	//重载函数
	virtual void PostNcDestroy();

	//消息函数
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnAppAbout();
	afx_msg void OnAppExit();

private:
	CMenu m_Menu;	
public:
	afx_msg void OnPaint();
};


