#pragma once


// EndPanel �Ի���

class EndPanel : public CDialogEx
{
	DECLARE_DYNAMIC(EndPanel)

public:
	EndPanel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~EndPanel();

// �Ի�������
	enum { IDD = IDD_END_PANEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnClose();
};
