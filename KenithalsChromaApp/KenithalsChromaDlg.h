
// KenithalsChromaDlg.h : header file
//
#include "ChromaSDKImpl.h"

#pragma once


// KenithalsChromaDlg dialog
class KenithalsChromaDlg : public CDialogEx
{
private:
	CChromaSDKImpl m_ChromaSDKImpl;

// Construction
public:
	KenithalsChromaDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KenithalsChromaApp_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual void OnDestroy();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
