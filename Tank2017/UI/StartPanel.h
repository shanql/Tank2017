#pragma once



/*!
 * \class StartPanel
 *
 * \brief ��ʼ���
 *
 * \author shanql
 * \date 2017/04/12
 */
class StartPanel : public CDialogEx
{
	DECLARE_DYNAMIC(StartPanel)

public:
	StartPanel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~StartPanel();

// �Ի�������
	enum { IDD = IDD_START_PANEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnClose();
};
