// MapEditorWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "MapEditor.h"
#include "MapEditorWnd.h"


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()



// MapEditorWnd

IMPLEMENT_DYNAMIC(MapEditorWnd, CWnd)

MapEditorWnd::MapEditorWnd()
{

}

MapEditorWnd::~MapEditorWnd()
{
}


BEGIN_MESSAGE_MAP(MapEditorWnd, CWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_APP_ABOUT, &MapEditorWnd::OnAppAbout)
	ON_COMMAND(ID_APP_EXIT, &MapEditorWnd::OnAppExit)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// MapEditorWnd 消息处理程序




int MapEditorWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//添加菜单
	m_Menu.LoadMenu( MAKEINTRESOURCE(IDR_MAINFRAME ) );
	CMenu* pOldMenu = GetMenu();
	if ( pOldMenu )
	{
		//SetMenu will not destroy a previous menu. 
		//An application should call the CMenu::DestroyMenu
		//member function to accomplish this task.
		pOldMenu->DestroyMenu();
	}
	SetMenu( NULL );
	SetMenu( &m_Menu );


	SetWindowPos( NULL, 0, 0, 1024, 768, SWP_NOMOVE );

	return 0;
}


void MapEditorWnd::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类
	delete this;

	//CWnd::PostNcDestroy();
}


void MapEditorWnd::OnAppAbout()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


void MapEditorWnd::OnAppExit()
{
	// TODO: 在此添加命令处理程序代码
	PostMessage( WM_CLOSE );
}


void MapEditorWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	
	CRect clientRect;
	GetClientRect( clientRect );
	dc.FillSolidRect( clientRect, RGB(0, 0, 0 ) );

	CPen gridPen;
	gridPen.CreatePen( PS_SOLID, 1, RGB(255, 255, 0 ) );
	CPen* pOldPen = dc.SelectObject( &gridPen );

	//横向网格线
	int nGrid = 32;	// 网格大小 
	for( int i = 0; i < clientRect.Height(); i += nGrid )
	{
		dc.MoveTo( 0, i );
		dc.LineTo( clientRect.Width(), i );
	}

	//竖向网格线
	for( int i = 0; i < clientRect.Width(); i += nGrid )
	{
		dc.MoveTo( i, 0 );
		dc.LineTo( i, clientRect.Height() );
	}

	dc.SelectObject( pOldPen );

	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()
}
