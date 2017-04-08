
// tst_PlaySoundDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "tst_PlaySound.h"
#include "tst_PlaySoundDlg.h"
#include "afxdialogex.h"
#include "../../Tank2017/MCIPlaySndManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// Ctst_PlaySoundDlg �Ի���



Ctst_PlaySoundDlg::Ctst_PlaySoundDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Ctst_PlaySoundDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ctst_PlaySoundDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Ctst_PlaySoundDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_PLAY1, &Ctst_PlaySoundDlg::OnBnClickedBtnPlay1)
	ON_BN_CLICKED(IDC_BTN_STOP1, &Ctst_PlaySoundDlg::OnBnClickedBtnStop1)
	ON_BN_CLICKED(IDC_BTN_PLAY2, &Ctst_PlaySoundDlg::OnBnClickedBtnPlay2)
	ON_BN_CLICKED(IDC_BTN_STOP2, &Ctst_PlaySoundDlg::OnBnClickedBtnStop2)
END_MESSAGE_MAP()


// Ctst_PlaySoundDlg ��Ϣ�������

BOOL Ctst_PlaySoundDlg::OnInitDialog()
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Ctst_PlaySoundDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Ctst_PlaySoundDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Ctst_PlaySoundDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Ctst_PlaySoundDlg::OnBnClickedBtnPlay1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MCIPlaySndManager::GetInstance().PlayGameSound( _T("res/bg0.mp3"));
}


void Ctst_PlaySoundDlg::OnBnClickedBtnStop1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MCIPlaySndManager::GetInstance().StopGameSound( _T("res/bg0.mp3"));
}


void Ctst_PlaySoundDlg::OnBnClickedBtnPlay2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MCIPlaySndManager::GetInstance().PlayGameSound( _T("res/bg1.wav"), true );
}


void Ctst_PlaySoundDlg::OnBnClickedBtnStop2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MCIPlaySndManager::GetInstance().StopGameSound( _T("res/bg1.wav"));
}
