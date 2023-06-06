// Spooling Simulator GuiDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Spooling Simulator Gui.h"
#include "Spooling Simulator GuiDlg.h"

#include <iostream>

#include "CSpoolingOutput.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV 支持

	// 实现
protected:
DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSpoolingSimulatorGuiDlg 对话框


CSpoolingSimulatorGuiDlg::CSpoolingSimulatorGuiDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SPOOLING_SIMULATOR_GUI_DIALOG, pParent)
	  , CSpoolingOutput(), m_nTaskNum0(0)
	  , m_nTaskNum1(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSpoolingSimulatorGuiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PROCESS_0, m_nTaskNum0);
	//  DDX_Control(pDX, IDC_PROCESS_1, m_nTaskNum1);
	DDX_Text(pDX, IDC_PROCESS_1, m_nTaskNum1);
	// DDX_Control(pDX, IDC_PRCSR1_LIST, Process1ListBox);
}

BEGIN_MESSAGE_MAP(CSpoolingSimulatorGuiDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_PROCESS_1, &CSpoolingSimulatorGuiDlg::OnEnChangeProcess1)
	ON_BN_CLICKED(IDC_BUTTON1, &CSpoolingSimulatorGuiDlg::OnBnClickedButton1)
	ON_LBN_SELCHANGE(IDC_PRCS0_LIST, &CSpoolingSimulatorGuiDlg::OnLbnSelchangePrcs0List)
	ON_LBN_SELCHANGE(IDC_PRCS1_LIST, &CSpoolingSimulatorGuiDlg::OnLbnSelchangePrcs1List)
	ON_LBN_SELCHANGE(IDC_PRCS2_LIST, &CSpoolingSimulatorGuiDlg::OnLbnSelchangePrcs2List)
END_MESSAGE_MAP()


// CSpoolingSimulatorGuiDlg 消息处理程序

BOOL CSpoolingSimulatorGuiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE); // 设置大图标
	SetIcon(m_hIcon, FALSE); // 设置小图标

	SetWindowTextW(L"SPOOLING输入输出技术模拟");
	// TODO: 在此添加额外的初始化代码
	m_nTaskNum0 = 0;
	m_nTaskNum1 = 0;

	auto static_text = static_cast<CStatic*>(GetDlgItem(IDC_STATIC_SHOW)); //NOLINT
	static_text->SetWindowTextW(L"点击显示完整信息");
	return TRUE; // 除非将焦点设置到控件，否则返回 TRUE
}

void CSpoolingSimulatorGuiDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSpoolingSimulatorGuiDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSpoolingSimulatorGuiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//void CSpoolingSimulatorGuiDlg::OnLbnSelchangeList2()
//{
//	// TODO: 在此添加控件通知处理程序代码
//}


void CSpoolingSimulatorGuiDlg::OnEnChangeProcess1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CSpoolingSimulatorGuiDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	auto pProcess0ListBox = static_cast<CListBox*>(GetDlgItem(IDC_PRCS0_LIST)); // NOLINT
	auto pProcess1ListBox = static_cast<CListBox*>(GetDlgItem(IDC_PRCS1_LIST)); // NOLINT
	auto pProcess2ListBox = static_cast<CListBox*>(GetDlgItem(IDC_PRCS2_LIST)); // NOLINT
	UpdateData(TRUE);
	auto button = static_cast<CButton*>(GetDlgItem(IDC_BUTTON1)); //NOLINT

	button->SetWindowTextW(L"正在运行...");
	
	AfxBeginThread(&SpoolingSimulationThread, this); // 启动线
	
	pProcess0ListBox->ResetContent();
	pProcess1ListBox->ResetContent();
	pProcess2ListBox->ResetContent();

	pProcess0ListBox->RedrawWindow();
	pProcess1ListBox->RedrawWindow();
	pProcess2ListBox->RedrawWindow();

	int i = 1;
	int j = 1;
	int k = 1;
	while (true)
	{
		if (pcb[2].status == FINISH_STATUS && vTask0Logs.empty() && vTask1Logs.empty() && vTask2Logs.empty())
		{
			break;
		}
		if (!vTask0Logs.empty())
		{
			std::string logs = vTask0Logs.front();
			vTask0Logs.pop();
			CString cstr(logs.c_str());
			pProcess0ListBox->AddString(cstr);
			// UpdateData(FALSE);
			pProcess0ListBox->RedrawWindow();
			i++;
		}
		if (!vTask1Logs.empty())
		{
			std::string logs = vTask1Logs.front();
			vTask1Logs.pop();
			CString cstr(logs.c_str());
			pProcess1ListBox->AddString(cstr);
			// UpdateData(FALSE);
			pProcess1ListBox->RedrawWindow();
			j++;
		}
		if (!vTask2Logs.empty())
		{
			std::string logs = vTask2Logs.front();
			vTask2Logs.pop();
			CString cstr(logs.c_str());
			pProcess2ListBox->AddString(cstr);
			// UpdateData(FALSE);
			pProcess2ListBox->RedrawWindow();
			k++;
		}
	}
	button->SetWindowTextW(L"开始运行");
}

UINT CSpoolingSimulatorGuiDlg::SpoolingSimulationThread(LPVOID pParam)
{
	auto p = static_cast<CSpoolingSimulatorGuiDlg*>(pParam);
	// p->UpdateData(TRUE);
	p->InitAllTasks(p->m_nTaskNum0, p->m_nTaskNum1);
	p->Start();
	return 0;
}


void CSpoolingSimulatorGuiDlg::OnLbnSelchangePrcs0List()
{
	// TODO: 在此添加控件通知处理程序代码
	auto static_text = static_cast<CStatic*>(GetDlgItem(IDC_STATIC_SHOW)); //NOLINT
	auto pProcessListBox = static_cast<CListBox*>(GetDlgItem(IDC_PRCS0_LIST)); // NOLINT

	ClearOtherListBox(0);
	CString str;
	pProcessListBox->GetText(pProcessListBox->GetCurSel(), str);
	static_text->SetWindowTextW(str);
}


void CSpoolingSimulatorGuiDlg::OnLbnSelchangePrcs1List()
{
	// TODO: 在此添加控件通知处理程序代码
	auto static_text = static_cast<CStatic*>(GetDlgItem(IDC_STATIC_SHOW)); //NOLINT
	auto pProcessListBox = static_cast<CListBox*>(GetDlgItem(IDC_PRCS1_LIST)); // NOLINT

	ClearOtherListBox(1);
	CString str;
	pProcessListBox->GetText(pProcessListBox->GetCurSel(), str);
	static_text->SetWindowTextW(str);
}


void CSpoolingSimulatorGuiDlg::OnLbnSelchangePrcs2List()
{
	// TODO: 在此添加控件通知处理程序代码
	auto static_text = static_cast<CStatic*>(GetDlgItem(IDC_STATIC_SHOW)); //NOLINT
	auto pProcessListBox = static_cast<CListBox*>(GetDlgItem(IDC_PRCS2_LIST)); // NOLINT

	ClearOtherListBox(2);
	CString str;
	pProcessListBox->GetText(pProcessListBox->GetCurSel(), str);
	static_text->SetWindowTextW(str);
}

void CSpoolingSimulatorGuiDlg::ClearOtherListBox(const int boxId) const
{
	auto pProcess0ListBox = static_cast<CListBox*>(GetDlgItem(IDC_PRCS0_LIST)); // NOLINT
	auto pProcess1ListBox = static_cast<CListBox*>(GetDlgItem(IDC_PRCS1_LIST)); // NOLINT
	auto pProcess2ListBox = static_cast<CListBox*>(GetDlgItem(IDC_PRCS2_LIST)); // NOLINT
	switch (boxId)
	{
	case 0:
		pProcess1ListBox->SetCurSel(-1);
		pProcess2ListBox->SetCurSel(-1);
		break;
	case 1:
		pProcess0ListBox->SetCurSel(-1);
		pProcess2ListBox->SetCurSel(-1);
		break;
	case 2:
		pProcess0ListBox->SetCurSel(-1);
		pProcess1ListBox->SetCurSel(-1);
		break;
	default:
		break;
	}
}
