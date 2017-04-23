
// Tank2017.cpp : 定义应用程序的类行为。
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


// CTank2017App 构造

CTank2017App::CTank2017App()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CTank2017App 对象

CTank2017App theApp;


// CTank2017App 初始化

BOOL CTank2017App::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	//CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	//LoadIcon( IDR_MAINFRAME );

	//设置随机种子
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

	//显示主窗口
	pFrame->ShowWindow( SW_SHOW );
	pFrame->UpdateWindow();
	pFrame->CenterWindow();

	// 显示开始面板 
	pFrame->ShowPanel( Panel_Start, true );
	pFrame->ShowPanel( Panel_Pause | Panel_End, false );

	return TRUE;
}



BOOL CTank2017App::OnIdle(LONG lCount)
{
	// TODO: 在此添加专用代码和/或调用基类

	// 此函数不会被调用，因为这是个模态对话框程序，CWinThread::Run并未被运行

	return CWinApp::OnIdle(lCount);
}
