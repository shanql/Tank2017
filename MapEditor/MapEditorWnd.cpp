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

IMPLEMENT_DYNAMIC(MapEditorWnd, CFrameWnd)

MapEditorWnd::MapEditorWnd()
{

}

MapEditorWnd::~MapEditorWnd()
{
}


BEGIN_MESSAGE_MAP(MapEditorWnd, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_APP_ABOUT, &MapEditorWnd::OnAppAbout)
	ON_COMMAND(ID_APP_EXIT, &MapEditorWnd::OnAppExit)
	ON_WM_PAINT()
	ON_COMMAND(ID_IRON_1_WALL, &MapEditorWnd::OnIron1Wall)
	ON_COMMAND(ID_IRON_4_WALL, &MapEditorWnd::OnIron4Wall)
	ON_COMMAND(ID_NORMAL_WALL, &MapEditorWnd::OnNormalWall)
	ON_UPDATE_COMMAND_UI(ID_IRON_1_WALL, &MapEditorWnd::OnUpdateIron1Wall)
	ON_UPDATE_COMMAND_UI(ID_IRON_4_WALL, &MapEditorWnd::OnUpdateIron4Wall)
	ON_UPDATE_COMMAND_UI(ID_NORMAL_WALL, &MapEditorWnd::OnUpdateNormalWall)
END_MESSAGE_MAP()



// MapEditorWnd 消息处理程序




int MapEditorWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetWindowPos( NULL, 0, 0, 940, 680, SWP_NOMOVE );

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



	//创建工具栏
	m_ToolBar.CreateEx( this );

	//设置图片
	CImageList imgList;
	imgList.Create( 16, 16, ILC_COLOR32, 3, 3 );
	imgList.SetBkColor( RGB(0, 0, 0 ) );
	imgList.Add( AfxGetApp()->LoadIcon( IDI_ICON_IRON_1_WALL ) );
	imgList.Add( AfxGetApp()->LoadIcon( IDI_ICON_IRON_4_WALL ) );
	imgList.Add( AfxGetApp()->LoadIcon( IDI_ICON_WALL ) );
	m_ToolBar.GetToolBarCtrl().SetImageList( &imgList );
	imgList.Detach();//重要

	imgList.Create( 32, 32, ILC_COLOR4, 3, 3 );
	imgList.Add( AfxGetApp()->LoadIcon( IDI_ICON_IRON_1_WALL ) );
	imgList.Add( AfxGetApp()->LoadIcon( IDI_ICON_IRON_4_WALL ) );
	imgList.Add( AfxGetApp()->LoadIcon( IDI_ICON_WALL ) );
	imgList.Detach();
	
	UINT idArray[] = 
	{
		ID_IRON_1_WALL,
		ID_IRON_4_WALL,
		ID_NORMAL_WALL
	};
 	m_ToolBar.SetButtons( idArray, 3 ); 
	m_ToolBar.SetButtonText( 0, _T("单格铁墙"));
	m_ToolBar.SetButtonText( 1, _T("四格铁墙"));
	m_ToolBar.SetButtonText( 2, _T("普通墙"));
	CRect rectToolBar;
	//得到按钮的大小
	m_ToolBar.GetItemRect(0, &rectToolBar);
	//设置按钮的大小
	m_ToolBar.SetSizes(CSize( 60, 32), CSize(16,16));

	return 0;
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
	int nGrid = 8;	// 网格大小 
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
	TRACE( _T("onpaint\n"));
}


void MapEditorWnd::OnIron1Wall()
{
	// TODO: 在此添加命令处理程序代码
	AfxMessageBox( _T("OnIron1Wall"));
}


void MapEditorWnd::OnIron4Wall()
{
	// TODO: 在此添加命令处理程序代码
	AfxMessageBox( _T("OnIron4Wall"));
}


void MapEditorWnd::OnNormalWall()
{
	// TODO: 在此添加命令处理程序代码
	AfxMessageBox( _T("OnNormalWall"));
}


void MapEditorWnd::OnUpdateIron1Wall(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	//pCmdUI->SetCheck();
}


void MapEditorWnd::OnUpdateIron4Wall(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	//pCmdUI->SetCheck();
}


void MapEditorWnd::OnUpdateNormalWall(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}
