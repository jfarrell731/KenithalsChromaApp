
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
	CEdit m_WOWPATH;
	CButton m_Keyboard_Buttons[ChromaSDK::Keyboard::MAX_ROW][ChromaSDK::Keyboard::MAX_COLUMN];
	CButton m_Mouse_Buttons[ChromaSDK::Mouse::MAX_ROW][ChromaSDK::Mouse::MAX_COLUMN];
	CButton m_Select, m_Deselect, m_Apply, m_Save, m_Load;
	CComboBox m_DisplayType, m_Profile;
	CMFCColorButton m_ColorPicker;
	CSliderCtrl m_Brightness;

	afx_msg void OnEnChangeWowpath();
	afx_msg void OnBnClickedSelect();
	afx_msg void OnBnClickedDeselect();
	afx_msg void OnBnClickedApply();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();
};
