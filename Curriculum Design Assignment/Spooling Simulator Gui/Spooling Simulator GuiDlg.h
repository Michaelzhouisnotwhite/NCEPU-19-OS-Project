// Spooling Simulator GuiDlg.h: 头文件
//

#pragma once
#include "CSpoolingOutput.h"

// CSpoolingSimulatorGuiDlg 对话框
class CSpoolingSimulatorGuiDlg : public CDialogEx, public CSpoolingOutput
{
	// 构造
public:
	CSpoolingSimulatorGuiDlg(CWnd* pParent = nullptr); // 标准构造函数

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SPOOLING_SIMULATOR_GUI_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV 支持


	// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
DECLARE_MESSAGE_MAP()
public:
	//	afx_msg void OnLbnSelchangeList2();
	int m_nTaskNum0;
	//	CEdit m_nTaskNum1;
	afx_msg void OnEnChangeProcess1();
	int m_nTaskNum1;
	afx_msg void OnBnClickedButton1();
	static UINT __cdecl SpoolingSimulationThread(LPVOID pParam);
	//	void Thread0() override;
	//	void Thread1() override;
	//	void Request(int pid) override;
	//	void Spooling() override;
	//	void Start() override;
	// CListBox Process1ListBox;
	afx_msg void OnLbnSelchangePrcs0List();
	afx_msg void OnLbnSelchangePrcs1List();
	afx_msg void OnLbnSelchangePrcs2List();

	void ClearOtherListBox(int boxId) const;
};
