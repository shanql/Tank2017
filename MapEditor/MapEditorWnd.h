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
class MapEditorWnd : public CWnd
{
	DECLARE_DYNAMIC(MapEditorWnd)

public:
	MapEditorWnd();
	virtual ~MapEditorWnd();

protected:
	DECLARE_MESSAGE_MAP()

	//���غ���
	virtual void PostNcDestroy();

	//��Ϣ����
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnAppAbout();
	afx_msg void OnAppExit();

private:
	CMenu m_Menu;	
public:
	afx_msg void OnPaint();
};


