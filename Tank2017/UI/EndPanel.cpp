// EndPanel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tank2017.h"
#include "EndPanel.h"
#include "afxdialogex.h"
#include "MsgDefine.h"


// EndPanel �Ի���

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


// EndPanel ��Ϣ�������


void EndPanel::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	//AfxGetMainWnd()->SendMessage( WM_U_GAME_START, 0, 0 );
	g_GameLogic.ReStart();

	//CDialogEx::OnOK();
}


void EndPanel::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	//CDialogEx::OnCancel();
}


void EndPanel::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	AfxGetMainWnd()->PostMessage( WM_CLOSE );
	CDialogEx::OnClose();
}
