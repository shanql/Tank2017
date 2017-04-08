
// Tank2017Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tank2017.h"
#include "Tank2017Dlg.h"
#include "afxdialogex.h"
#include "MapGrid.h"
#include "AiObject.h"
#include "OpposingTank.h"
#include "GlobalFunction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define IDI_TANK2017_UPDATE			1			//

//��ť
#define IDC_BTN_START				100			//��ʼ��ť


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


// CTank2017Dlg �Ի���



CTank2017Dlg::CTank2017Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTank2017Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//m_pPlayer1 = nullptr;
	m_nGameWidth = 1;
	m_nGameHeight = 1;
}

void CTank2017Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTank2017Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CTank2017Dlg ��Ϣ�������

BOOL CTank2017Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//���ô��ڹ̶���С 
	//ModifyStyle( WS_THICKFRAME, WS_CLIPCHILDREN );
	ModifyStyle( WS_THICKFRAME, 0 );


	// ���ϱ��������߿��С���������С�պ��ǿͻ�����С��������
	int nCyCaption = GetSystemMetrics( SM_CYCAPTION );
	int nCyBorder = GetSystemMetrics( SM_CYBORDER );
	int nCyFrame = GetSystemMetrics( SM_CYFRAME );
	int nCxFrame = GetSystemMetrics( SM_CXFRAME );
	int nCxBorder = GetSystemMetrics( SM_CXBORDER );

	int nWidth =  ( 2 * ::GetSystemMetrics(SM_CXSCREEN) ) / 3; 
	int nHeight = ( 3 * ::GetSystemMetrics(SM_CYSCREEN) ) / 4; 

	


	MoveWindow( 0, 0, nWidth, nHeight );
	CenterWindow();


	CRect clientRect;
	GetClientRect( &clientRect );

	// ��Ϣ����ʼ��
	int nInfoViewWidth = 200;
	int nInfoViewHeigth = clientRect.Height();
	CRect rcGameInfoView(
		clientRect.Width() - nInfoViewWidth,
		0, 
		clientRect.Width(),
		nInfoViewHeigth );
	m_GameInfoView.Create( NULL, NULL, WS_VISIBLE|WS_CHILD, 
		rcGameInfoView, this, 0 );
	m_GameInfoView.SetGamePlayer( &m_GamePlayer );


	//��Ϸ����С 
	m_nGameWidth = clientRect.Width() - nInfoViewWidth;
	m_nGameHeight = clientRect.Height();

	//��ť����
// 	m_btnStart.Create(_T("��ʼ"), WS_VISIBLE | BS_PUSHBUTTON,
// 		CRect( 100, 100, 150, 120 ), 
// 		this, IDC_BTN_START );

	// ��������DC
	CDC* pDC = this->GetDC();
	m_MemoryDc.CreateCompatibleDC( pDC );
	m_MemoryBmp.CreateCompatibleBitmap( pDC,
		m_nGameWidth, m_nGameHeight );
	m_MemoryDc.SelectObject( &m_MemoryBmp );
	this->ReleaseDC(pDC);
	pDC = nullptr;

	// �����ʼ��
	if ( !m_World.Initialize( m_nGameWidth / Tank2017::gGridUnitSize,
		m_nGameHeight / Tank2017::gGridUnitSize ) )
	{
		AfxMessageBox( _T("Initialize Map Grid failed!"));
		return FALSE;
	}

	// �������
	m_GamePlayer.SetWorld( &m_World );
	m_GamePlayer.Respawn();
	//m_pPlayer1 = (PlayerTank*)(m_World.CreateEntity( enPlayerTank, 0, 0, 1, enDirRight));


	SetTimer( IDI_TANK2017_UPDATE, 30, NULL );

	// ���ű�������
	int nIndex = 1;//rand() % 2;
	TCHAR szBgFile[128] = { 0 };
	_stprintf_s( szBgFile, _countof(szBgFile), _T("res/bg%d.mp3"), nIndex );
	Tank2017::PlayMusic( szBgFile, true );


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTank2017Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTank2017Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		//CDC* dc = this->GetDC();
		dc.BitBlt( 0, 0, m_nGameWidth, m_nGameHeight, &m_MemoryDc,
			0, 0, SRCCOPY );
		//this->ReleaseDC( dc );

// 		CRect clientRect;
// 		GetClientRect( clientRect );
// 		ValidateRect( clientRect );
		//buffDc.SelectObject( pOldBmp );
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTank2017Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTank2017Dlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialogEx::OnCancel();
}


void CTank2017Dlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialogEx::OnOK();
}


void CTank2017Dlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	EndDialog(IDCANCEL);

	//CDialogEx::OnClose();
}


void CTank2017Dlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CTank2017Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if ( pMsg->message == WM_KEYDOWN )
	{
		m_GamePlayer.OnEventKeyDown( pMsg->wParam );
	}
	else if ( pMsg->message == WM_KEYUP )
	{
		m_GamePlayer.OnEventKeyUp( pMsg->wParam );
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CTank2017Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if ( nIDEvent == IDI_TANK2017_UPDATE )
	{
		//���ƺ���
		CRect rect;
		GetClientRect(&rect);
		m_MemoryDc.FillSolidRect( 0, 0, m_nGameWidth, 
			m_nGameHeight, RGB( 0, 0, 0 ) );
		m_World.RunDraw( &m_MemoryDc );
		Invalidate( FALSE );
		//OnPaint();

		//���
		m_GamePlayer.RunLogic();

		//�߼�����
		m_World.RunLogic();

		

	}

	CDialogEx::OnTimer(nIDEvent);
}
