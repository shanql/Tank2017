#pragma once



/*!
 * \class PausePanel
 *
 * \brief 暂停面板
 *
 * \author shanql
 * \date 2017/04/12
 */
class PausePanel : public CDialogEx
{
	DECLARE_DYNAMIC(PausePanel)

public:
	PausePanel(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PausePanel();

// 对话框数据
	enum { IDD = IDD_PAUSE_PANEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnClose();
};
