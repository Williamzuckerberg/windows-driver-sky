
// sysLoaderDlg.h : ͷ�ļ�
//

#pragma once

BOOL LoadNTDriver(LPCTSTR lpDriverName,LPCTSTR lpDriverPathName);
BOOL UnLoadSys( LPCTSTR szSvrName );

// CsysLoaderDlg �Ի���
class CsysLoaderDlg : public CDialogEx
{
// ����
public:
	CsysLoaderDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SYSLOADER_DIALOG };

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
	afx_msg void OnBnClickedButtonLoad();
	CString m_sysName;
	afx_msg void OnBnClickedButtonDelete();
};
