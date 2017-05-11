// MapEditorWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MapEditor.h"
#include "MapEditorWnd.h"


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
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



// MapEditorWnd ��Ϣ�������




int MapEditorWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetWindowPos( NULL, 0, 0, 940, 680, SWP_NOMOVE );

	//��Ӳ˵�
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



	//����������
	m_ToolBar.CreateEx( this );

	//����ͼƬ
	CImageList imgList;
	imgList.Create( 16, 16, ILC_COLOR32, 3, 3 );
	imgList.SetBkColor( RGB(0, 0, 0 ) );
	imgList.Add( AfxGetApp()->LoadIcon( IDI_ICON_IRON_1_WALL ) );
	imgList.Add( AfxGetApp()->LoadIcon( IDI_ICON_IRON_4_WALL ) );
	imgList.Add( AfxGetApp()->LoadIcon( IDI_ICON_WALL ) );
	m_ToolBar.GetToolBarCtrl().SetImageList( &imgList );
	imgList.Detach();//��Ҫ

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
	m_ToolBar.SetButtonText( 0, _T("������ǽ"));
	m_ToolBar.SetButtonText( 1, _T("�ĸ���ǽ"));
	m_ToolBar.SetButtonText( 2, _T("��ͨǽ"));
	CRect rectToolBar;
	//�õ���ť�Ĵ�С
	m_ToolBar.GetItemRect(0, &rectToolBar);
	//���ð�ť�Ĵ�С
	m_ToolBar.SetSizes(CSize( 60, 32), CSize(16,16));

	return 0;
}


void MapEditorWnd::OnAppAbout()
{
	// TODO: �ڴ���������������
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


void MapEditorWnd::OnAppExit()
{
	// TODO: �ڴ���������������
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

	//����������
	int nGrid = 8;	// �����С 
	for( int i = 0; i < clientRect.Height(); i += nGrid )
	{
		dc.MoveTo( 0, i );
		dc.LineTo( clientRect.Width(), i );
	}

	//����������
	for( int i = 0; i < clientRect.Width(); i += nGrid )
	{
		dc.MoveTo( i, 0 );
		dc.LineTo( i, clientRect.Height() );
	}

	dc.SelectObject( pOldPen );

	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CWnd::OnPaint()
	TRACE( _T("onpaint\n"));
}


void MapEditorWnd::OnIron1Wall()
{
	// TODO: �ڴ���������������
	AfxMessageBox( _T("OnIron1Wall"));
}


void MapEditorWnd::OnIron4Wall()
{
	// TODO: �ڴ���������������
	AfxMessageBox( _T("OnIron4Wall"));
}


void MapEditorWnd::OnNormalWall()
{
	// TODO: �ڴ���������������
	AfxMessageBox( _T("OnNormalWall"));
}


void MapEditorWnd::OnUpdateIron1Wall(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	//pCmdUI->SetCheck();
}


void MapEditorWnd::OnUpdateIron4Wall(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	//pCmdUI->SetCheck();
}


void MapEditorWnd::OnUpdateNormalWall(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
}
