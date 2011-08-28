
// protectTaskDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "protectTask.h"
#include "protectTaskDlg.h"
#include "afxdialogex.h"
#include "ctl_code.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CprotectTaskDlg 对话框




CprotectTaskDlg::CprotectTaskDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CprotectTaskDlg::IDD, pParent)
	, m_protectPid(_T(""))
{
	hDevice = NULL;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CprotectTaskDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_protectPid);
	DDX_Control(pDX, IDC_HOOK_BUTTON, m_hookButton);
	DDX_Control(pDX, IDC_UNHOOK_BUTTON, m_unhookButton);
	DDX_Control(pDX, IDC_EDIT1, m_pidControl);
	DDX_Control(pDX, IDC_SELECT_OK, m_selectPidButton);
}

BEGIN_MESSAGE_MAP(CprotectTaskDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_HOOK_BUTTON, &CprotectTaskDlg::OnBnClickedHookButton)
	ON_BN_CLICKED(IDC_UNHOOK_BUTTON, &CprotectTaskDlg::OnBnClickedUnhookButton)
	ON_BN_CLICKED(IDC_SELECT_OK, &CprotectTaskDlg::OnBnClickedSelectOk)
END_MESSAGE_MAP()


// CprotectTaskDlg 消息处理程序

BOOL CprotectTaskDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CprotectTaskDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CprotectTaskDlg::OnPaint()
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
HCURSOR CprotectTaskDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int Hook(HANDLE hDevice, ULONG pid) //pid 需要被保护进程ID
{

	int port[2];
	int bufret;
	ULONG dwWrite;
	port[0]=pid;


	DeviceIoControl(hDevice, hook_code , &port, 8, &bufret, 4, &dwWrite, NULL);
	return bufret;

}
int UnHook(HANDLE hDevice)
{

	int port[2];
	int bufret;
	ULONG dwWrite;	

	DeviceIoControl(hDevice, unhook_code , &port, 8, &bufret, 4, &dwWrite, NULL);
	return bufret;

}

BOOL hook = FALSE;
void CprotectTaskDlg::OnBnClickedHookButton()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!hook)
	{
		hook = TRUE;
		m_unhookButton.EnableWindow(TRUE);
		m_hookButton.EnableWindow(FALSE);

		//
		if (hDevice == 0)
		{
			hDevice = CreateFile(L"\\\\.\\SSDTHook0", // \\DosDevices\\SSDTHook0
				GENERIC_READ | GENERIC_WRITE,
				0,		// share mode none
				NULL,	// no security
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL );		// no template
			if (hDevice == INVALID_HANDLE_VALUE)
			{
				TRACE(L"获取驱动句柄失败: %s with Win32 error code: %d\n","MyDriver", GetLastError() );
			}
		}

		if (hDevice)
		{
			TRACE(L"start hook in application layer");
			Hook(hDevice, _tcstol(m_protectPid, NULL, 10));
		}
	}
}


void CprotectTaskDlg::OnBnClickedUnhookButton()
{
	// TODO: 在此添加控件通知处理程序代码
	if (hook)
	{
		hook = FALSE;
		m_hookButton.EnableWindow(TRUE);
		m_unhookButton.EnableWindow(FALSE);

		if (hDevice == 0)
		{
			hDevice = CreateFile(L"\\\\.\\DosDevices\\SSDTHook0", // \\DosDevices\\SSDTHook0
				GENERIC_READ | GENERIC_WRITE,
				0,		// share mode none
				NULL,	// no security
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL );		// no template
			if (hDevice == INVALID_HANDLE_VALUE)
			{
				TRACE(L"获取驱动句柄失败: %s with Win32 error code: %d\n","MyDriver", GetLastError() );
			}
		}

		if (hDevice)
		{
			TRACE(L"start unhook in application layer");
			UnHook(hDevice);
		}
	}
}


void CprotectTaskDlg::OnBnClickedSelectOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_protectPid == L"")
	{
		MessageBox(L"请输入要保护的进程ID");
	}
	else
	{
		m_selectPidButton.EnableWindow(FALSE);
		m_pidControl.EnableWindow(FALSE);
		m_hookButton.EnableWindow(TRUE);
	}
}
