// StartPanel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tank2017.h"
#include "StartPanel.h"
#include "afxdialogex.h"
#include "MsgDefine.h"


// StartPanel �Ի���

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


// StartPanel ��Ϣ�������


void StartPanel::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	AfxGetMainWnd()->SendMessage( WM_U_GAME_START, 0, 0 );

	//CDialogEx::OnOK();
}


void StartPanel::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	
	//CDialogEx::OnCancel();
}


void StartPanel::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	AfxGetMainWnd()->PostMessage( WM_CLOSE );
	CDialogEx::OnClose();
}
