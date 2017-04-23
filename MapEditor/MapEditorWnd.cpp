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



// MapEditorWnd ��Ϣ�������




int MapEditorWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

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


	SetWindowPos( NULL, 0, 0, 1024, 768, SWP_NOMOVE );

	return 0;
}


void MapEditorWnd::PostNcDestroy()
{
	// TODO: �ڴ����ר�ô����/����û���
	delete this;

	//CWnd::PostNcDestroy();
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
	int nGrid = 32;	// �����С 
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
}
