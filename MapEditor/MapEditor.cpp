
// MapEditor.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "MapEditor.h"
#include "MapEditorWnd.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMapEditorApp

// CMapEditorApp 构造

CMapEditorApp::CMapEditorApp()
{
}

// 唯一的一个 CMapEditorApp 对象

CMapEditorApp theApp;


// CMapEditorApp 初始化

BOOL CMapEditorApp::InitInstance()
{
	CWinApp::InitInstance();

	//注册窗口类
	CString strClassName = AfxRegisterWndClass( 0, 
		LoadCursor( IDC_ARROW),
		(HBRUSH)::GetStockObject(WHITE_BRUSH),
		LoadIcon( IDR_MAINFRAME ) );

	//创建窗口
	CWnd* pFrame = new MapEditorWnd();
	if ( !pFrame )
	{
		return FALSE;
	}
	pFrame->CreateEx( 0, strClassName, _T("Tank2017地图编辑器"), 
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, CRect(),
		NULL, NULL );
	m_pMainWnd = pFrame;

	//显示窗口
	pFrame->CenterWindow();
	pFrame->ShowWindow( SW_SHOW );

	return TRUE;
}

int CMapEditorApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	//AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}



