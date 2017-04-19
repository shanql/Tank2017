
// Tank2017.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Tank2017.h"
#include "GameFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTank2017App

BEGIN_MESSAGE_MAP(CTank2017App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTank2017App ����

CTank2017App::CTank2017App()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CTank2017App ����

CTank2017App theApp;


// CTank2017App ��ʼ��

BOOL CTank2017App::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	//CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	LoadIcon( IDR_MAINFRAME );

	//�����������
	srand( (unsigned)time(0) );

	GameFrame* pFrame = new GameFrame;
	if ( !pFrame )
	{
		return FALSE;
	}
	m_pMainWnd = pFrame;

	pFrame->Create( NULL, NULL,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX ,
		CRect(0, 0, 0, 0 ),
		CWnd::GetDesktopWindow(), NULL );

// 	pFrame->CreateEx( 0, NULL, NULL,
// 		WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX ,
// 		CRect(0, 0, 0, 0 ),
// 		CWnd::GetDesktopWindow(), NULL );

	//��ʾ������
	pFrame->ShowWindow( SW_SHOW );
	pFrame->UpdateWindow();
	pFrame->CenterWindow();

	// ��ʾ��ʼ��� 
	pFrame->ShowPanel( Panel_Start, true );
	pFrame->ShowPanel( Panel_Pause | Panel_End, false );

	return TRUE;


// 	CTank2017Dlg dlg;
// 	m_pMainWnd = &dlg;
// 	INT_PTR nResponse = dlg.DoModal();
// 	if (nResponse == IDOK)
// 	{
// 		// TODO: �ڴ˷��ô����ʱ��
// 		//  ��ȷ�������رնԻ���Ĵ���
// 	}
// 	else if (nResponse == IDCANCEL)
// 	{
// 		// TODO: �ڴ˷��ô����ʱ��
// 		//  ��ȡ�������رնԻ���Ĵ���
// 	}
// 	else if (nResponse == -1)
// 	{
// 		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
// 		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
// 	}
// 
// 	// ɾ�����洴���� shell ��������
// 	if (pShellManager != NULL)
// 	{
// 		delete pShellManager;
// 	}
// 
// 	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
// 	//  ����������Ӧ�ó������Ϣ�á�
// 	return FALSE;
}



BOOL CTank2017App::OnIdle(LONG lCount)
{
	// TODO: �ڴ����ר�ô����/����û���

	// �˺������ᱻ���ã���Ϊ���Ǹ�ģ̬�Ի������CWinThread::Run��δ������

	return CWinApp::OnIdle(lCount);
}
