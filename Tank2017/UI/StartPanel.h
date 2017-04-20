#pragma once



/*!
 * \class StartPanel
 *
 * \brief 开始面板
 *
 * \author shanql
 * \date 2017/04/12
 */
class StartPanel : public CDialogEx
{
	DECLARE_DYNAMIC(StartPanel)

public:
	StartPanel(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~StartPanel();

// 对话框数据
	enum { IDD = IDD_START_PANEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnClose();
};
