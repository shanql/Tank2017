
// tst_PlaySoundDlg.h : ͷ�ļ�
//

#pragma once


// Ctst_PlaySoundDlg �Ի���
class Ctst_PlaySoundDlg : public CDialogEx
{
// ����
public:
	Ctst_PlaySoundDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TST_PLAYSOUND_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnPlay1();
	afx_msg void OnBnClickedBtnStop1();
	afx_msg void OnBnClickedBtnPlay2();
	afx_msg void OnBnClickedBtnStop2();
};
