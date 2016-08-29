
// KenithalsChromaDlg.h : header file
//
#include "ChromaSDKImpl.h"

#pragma once


// KenithalsChromaDlg dialog
class KenithalsChromaDlg : public CDialogEx
{
private:
// Construction
public:
	CChromaSDKImpl m_ChromaSDKImpl;
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
public:
	CComboBox m_WOWDISPLAY, m_WOWSTATIC, m_BGDISPLAY;
	CButton m_WOWWASD, m_WOWNUMS;
	CSliderCtrl m_WOWBRIGHTNESS, m_BGBRIGHTNESS;
	CEdit m_WOWPATH;

	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	afx_msg void OnCbnSelchangeWowdisplay();
	afx_msg void OnBnClickedWowwasd();
	afx_msg void OnBnClickedWownums();
	afx_msg void OnCbnSelchangeWowstatic();
	afx_msg void OnCbnSelchangeBgdisplay();
	afx_msg void OnEnChangeWowpath();
};
