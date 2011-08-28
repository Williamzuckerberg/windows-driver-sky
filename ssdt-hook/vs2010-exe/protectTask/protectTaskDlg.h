
// protectTaskDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CprotectTaskDlg �Ի���
class CprotectTaskDlg : public CDialogEx
{
// ����
public:
	CprotectTaskDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PROTECTTASK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
