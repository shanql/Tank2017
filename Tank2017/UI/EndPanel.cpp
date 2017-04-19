// EndPanel.cpp : 实现文件
//

#include "stdafx.h"
#include "Tank2017.h"
#include "EndPanel.h"
#include "afxdialogex.h"
#include "MsgDefine.h"


// EndPanel 对话框

IMPLEMENT_DYNAMIC(EndPanel, CDialogEx)

EndPanel::EndPanel(CWnd* pParent /*=NULL*/)
	: CDialogEx(EndPanel::IDD, pParent)
{

}

EndPanel::~EndPanel()
{
}

void EndPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(EndPanel, CDialogEx)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// EndPanel 消息处理程序


void EndPanel::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	//AfxGetMainWnd()->SendMessage( WM_U_GAME_START, 0, 0 );
	g_GameLogic.ReStart();

	//CDialogEx::OnOK();
}


void EndPanel::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	//CDialogEx::OnCancel();
}


void EndPanel::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	AfxGetMainWnd()->PostMessage( WM_CLOSE );
	CDialogEx::OnClose();
}
