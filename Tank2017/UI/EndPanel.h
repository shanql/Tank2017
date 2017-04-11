#pragma once


// EndPanel 对话框

class EndPanel : public CDialogEx
{
	DECLARE_DYNAMIC(EndPanel)

public:
	EndPanel(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~EndPanel();

// 对话框数据
	enum { IDD = IDD_END_PANEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnClose();
};
