// PausePanel.cpp : 实现文件
//

#include "stdafx.h"
#include "Tank2017.h"
#include "PausePanel.h"
#include "afxdialogex.h"
#include "MsgDefine.h"


// PausePanel 对话框

IMPLEMENT_DYNAMIC(PausePanel, CDialogEx)

PausePanel::PausePanel(CWnd* pParent /*=NULL*/)
	: CDialogEx(PausePanel::IDD, pParent)
{

}

PausePanel::~PausePanel()
{
}

void PausePanel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PausePanel, CDialogEx)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// PausePanel 消息处理程序


void PausePanel::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	AfxGetMainWnd()->SendMessage( WM_U_GAME_CONTINUE, 0, 0 );

	//CDialogEx::OnOK();
}


void PausePanel::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnCancel();
}


void PausePanel::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	AfxGetMainWnd()->PostMessage( WM_CLOSE );
	CDialogEx::OnClose();
}
