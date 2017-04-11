// StartPanel.cpp : 实现文件
//

#include "stdafx.h"
#include "Tank2017.h"
#include "StartPanel.h"
#include "afxdialogex.h"
#include "MsgDefine.h"


// StartPanel 对话框

IMPLEMENT_DYNAMIC(StartPanel, CDialogEx)

StartPanel::StartPanel(CWnd* pParent /*=NULL*/)
	: CDialogEx(StartPanel::IDD, pParent)
{

}

StartPanel::~StartPanel()
{
}

void StartPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(StartPanel, CDialogEx)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// StartPanel 消息处理程序


void StartPanel::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	AfxGetMainWnd()->SendMessage( WM_U_GAME_START, 0, 0 );

	//CDialogEx::OnOK();
}


void StartPanel::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	
	//CDialogEx::OnCancel();
}


void StartPanel::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	AfxGetMainWnd()->PostMessage( WM_CLOSE );
	CDialogEx::OnClose();
}
