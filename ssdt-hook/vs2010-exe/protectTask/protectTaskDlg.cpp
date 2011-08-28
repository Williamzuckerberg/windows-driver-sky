
// protectTaskDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "protectTask.h"
#include "protectTaskDlg.h"
#include "afxdialogex.h"
#include "ctl_code.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CprotectTaskDlg �Ի���




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


// CprotectTaskDlg ��Ϣ�������

BOOL CprotectTaskDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CprotectTaskDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CprotectTaskDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int Hook(HANDLE hDevice, ULONG pid) //pid ��Ҫ����������ID
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
				TRACE(L"��ȡ�������ʧ��: %s with Win32 error code: %d\n","MyDriver", GetLastError() );
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
				TRACE(L"��ȡ�������ʧ��: %s with Win32 error code: %d\n","MyDriver", GetLastError() );
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_protectPid == L"")
	{
		MessageBox(L"������Ҫ�����Ľ���ID");
	}
	else
	{
		m_selectPidButton.EnableWindow(FALSE);
		m_pidControl.EnableWindow(FALSE);
		m_hookButton.EnableWindow(TRUE);
	}
}
