
// MapEditor.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "MapEditor.h"
#include "MapEditorWnd.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMapEditorApp

// CMapEditorApp ����

CMapEditorApp::CMapEditorApp()
{
}

// Ψһ��һ�� CMapEditorApp ����

CMapEditorApp theApp;


// CMapEditorApp ��ʼ��

BOOL CMapEditorApp::InitInstance()
{
	CWinApp::InitInstance();

	//ע�ᴰ����
	CString strClassName = AfxRegisterWndClass( 0, 
		LoadCursor( IDC_ARROW),
		(HBRUSH)::GetStockObject(WHITE_BRUSH),
		LoadIcon( IDR_MAINFRAME ) );

	//��������
	CWnd* pFrame = new MapEditorWnd();
	if ( !pFrame )
	{
		return FALSE;
	}
	pFrame->CreateEx( 0, strClassName, _T("Tank2017��ͼ�༭��"), 
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, CRect(),
		NULL, NULL );
	m_pMainWnd = pFrame;

	//��ʾ����
	pFrame->CenterWindow();
	pFrame->ShowWindow( SW_SHOW );

	return TRUE;
}

int CMapEditorApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	//AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}



