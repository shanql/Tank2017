// PausePanel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tank2017.h"
#include "PausePanel.h"
#include "afxdialogex.h"
#include "MsgDefine.h"


// PausePanel �Ի���

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


// PausePanel ��Ϣ�������


void PausePanel::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	AfxGetMainWnd()->SendMessage( WM_U_GAME_CONTINUE, 0, 0 );

	//CDialogEx::OnOK();
}


void PausePanel::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialogEx::OnCancel();
}


void PausePanel::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	AfxGetMainWnd()->PostMessage( WM_CLOSE );
	CDialogEx::OnClose();
}
