#pragma once



/*!
 * \class PausePanel
 *
 * \brief ��ͣ���
 *
 * \author shanql
 * \date 2017/04/12
 */
class PausePanel : public CDialogEx
{
	DECLARE_DYNAMIC(PausePanel)

public:
	PausePanel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PausePanel();

// �Ի�������
	enum { IDD = IDD_PAUSE_PANEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnClose();
};
