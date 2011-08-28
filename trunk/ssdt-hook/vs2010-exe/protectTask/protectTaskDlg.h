
// protectTaskDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CprotectTaskDlg 对话框
class CprotectTaskDlg : public CDialogEx
{
// 构造
public:
	CprotectTaskDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PROTECTTASK_DIALOG };

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
	afx_msg void OnBnClickedHookButton();
	afx_msg void OnBnClickedUnhookButton();
	CString m_protectPid;
public:
	HANDLE hDevice;
	CButton m_hookButton;
	CButton m_unhookButton;
	afx_msg void OnBnClickedSelectOk();
	CEdit m_pidControl;
	CButton m_selectPidButton;
};
