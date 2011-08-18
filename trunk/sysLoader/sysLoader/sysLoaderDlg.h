
// sysLoaderDlg.h : 头文件
//

#pragma once

BOOL LoadNTDriver(LPCTSTR lpDriverName,LPCTSTR lpDriverPathName);
BOOL UnLoadSys( LPCTSTR szSvrName );

// CsysLoaderDlg 对话框
class CsysLoaderDlg : public CDialogEx
{
// 构造
public:
	CsysLoaderDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SYSLOADER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


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
	afx_msg void OnBnClickedButtonLoad();
	CString m_sysName;
	afx_msg void OnBnClickedButtonDelete();
};
