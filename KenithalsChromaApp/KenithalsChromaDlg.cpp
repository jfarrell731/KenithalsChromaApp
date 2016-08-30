
// KenithalsChromaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KenithalsChromaApp.h"
#include "KenithalsChromaDlg.h"
#include "afxdialogex.h"
#include <string>
#include <iostream>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// KenithalsChromaDlg dialog



KenithalsChromaDlg::KenithalsChromaDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_KenithalsChromaApp_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void KenithalsChromaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WOWDISPLAY, m_WOWDISPLAY);
	DDX_Control(pDX, IDC_WOWSTATIC, m_WOWSTATIC);
	DDX_Control(pDX, IDC_WOWWASD, m_WOWWASD);
	DDX_Control(pDX, IDC_WOWNUMS, m_WOWNUMS);
	DDX_Control(pDX, IDC_WOWBRIGHTNESS, m_WOWBRIGHTNESS);
	DDX_Control(pDX, IDC_BGDISPLAY, m_BGDISPLAY);
	DDX_Control(pDX, IDC_BGBRIGHTNESS, m_BGBRIGHTNESS);
	DDX_Control(pDX, IDC_WOWPATH, m_WOWPATH);
}

BEGIN_MESSAGE_MAP(KenithalsChromaDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_WOWDISPLAY, &KenithalsChromaDlg::OnCbnSelchangeWowdisplay)
	ON_BN_CLICKED(IDC_WOWWASD, &KenithalsChromaDlg::OnBnClickedWowwasd)
	ON_BN_CLICKED(IDC_WOWNUMS, &KenithalsChromaDlg::OnBnClickedWownums)
	ON_CBN_SELCHANGE(IDC_WOWSTATIC, &KenithalsChromaDlg::OnCbnSelchangeWowstatic)
	ON_CBN_SELCHANGE(IDC_BGDISPLAY, &KenithalsChromaDlg::OnCbnSelchangeBgdisplay)
	ON_EN_CHANGE(IDC_WOWPATH, &KenithalsChromaDlg::OnEnChangeWowpath)
END_MESSAGE_MAP()


// KenithalsChromaDlg message handlers

BOOL KenithalsChromaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	m_ChromaSDKImpl.Initialize();
	m_ChromaSDKImpl.ResetEffects(0);

	m_WOWDISPLAY.SetCurSel(0);
	m_WOWSTATIC.SetCurSel(0);
	m_WOWWASD.SetCheck(1);
	m_WOWNUMS.SetCheck(1);
	m_WOWBRIGHTNESS.SetRange(20, 100);
	m_WOWBRIGHTNESS.SetPos(100);

	CString wowPath("C:\\Program Files\\World of Warcraft\\WTF\\Account\\!ACOUNTNAME!\\SavedVariables\\KenithalsChromaApp_WoWAddon.lua");

	m_WOWPATH.SetWindowText(wowPath);

	m_ChromaSDKImpl.SetKBEffect(CChromaSDKImpl::Off);
	m_ChromaSDKImpl.setStaticCharacter(DEFAULT);
	m_ChromaSDKImpl.SetPath("C:\\Program Files\\World of Warcraft\\WTF\\Account\\!ACOUNTNAME!\\SavedVariables\\KenithalsChromaApp_WoWAddon.lua");
	m_ChromaSDKImpl.SetWoWWASD(m_WOWWASD.GetCheck() == 1);
	m_ChromaSDKImpl.SetWoWNUMS(m_WOWNUMS.GetCheck() == 1);
	m_ChromaSDKImpl.UpdateCharacterBrightness(m_WOWBRIGHTNESS.GetPos());

	m_BGDISPLAY.SetCurSel(1);
	m_BGBRIGHTNESS.SetRange(20, 100);
	m_BGBRIGHTNESS.SetPos(50);

	m_ChromaSDKImpl.SetBGEffect(CChromaSDKImpl::Spectrum);
	m_ChromaSDKImpl.UpdateBGBrightness(m_BGBRIGHTNESS.GetPos());

	m_ChromaSDKImpl.StartAnim();
	m_ChromaSDKImpl.MainAnimation();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void KenithalsChromaDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void KenithalsChromaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR KenithalsChromaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void KenithalsChromaDlg::OnDestroy()
{
	m_ChromaSDKImpl.UnInitialize();
}

void KenithalsChromaDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	m_ChromaSDKImpl.UpdateCharacterBrightness(m_WOWBRIGHTNESS.GetPos());
	m_ChromaSDKImpl.UpdateBGBrightness(m_BGBRIGHTNESS.GetPos());
}

void KenithalsChromaDlg::OnCbnSelchangeWowdisplay()
{
	switch (m_WOWDISPLAY.GetCurSel())
	{
	case 1: m_ChromaSDKImpl.SetKBEffect(CChromaSDKImpl::Spectrum);
		break;
	case 2: m_ChromaSDKImpl.SetKBEffect(CChromaSDKImpl::Static);
		break;
	case 3: m_ChromaSDKImpl.SetKBEffect(CChromaSDKImpl::Character);
		break;
	default: m_ChromaSDKImpl.SetKBEffect(CChromaSDKImpl::Off);
	}
}

void KenithalsChromaDlg::OnCbnSelchangeWowstatic()
{
	switch (m_WOWSTATIC.GetCurSel())
	{
	case 1: m_ChromaSDKImpl.setStaticCharacter(DEATHKNIGHT);
		break;
	case 2: m_ChromaSDKImpl.setStaticCharacter(DEMONHUNTER);
		break;
	case 3: m_ChromaSDKImpl.setStaticCharacter(DRUID);
		break;
	case 4: m_ChromaSDKImpl.setStaticCharacter(HUNTER);
		break;
	case 5: m_ChromaSDKImpl.setStaticCharacter(MAGE);
		break;
	case 6: m_ChromaSDKImpl.setStaticCharacter(MONK);
		break;
	case 7: m_ChromaSDKImpl.setStaticCharacter(PALADIN);
		break;
	case 8: m_ChromaSDKImpl.setStaticCharacter(PRIEST);
		break;
	case 9: m_ChromaSDKImpl.setStaticCharacter(ROGUE);
		break;
	case 10: m_ChromaSDKImpl.setStaticCharacter(SHAMAN);
		break;
	case 11: m_ChromaSDKImpl.setStaticCharacter(WARLOCK);
		break;
	case 12: m_ChromaSDKImpl.setStaticCharacter(WARRIOR);
		break;
	default: m_ChromaSDKImpl.setStaticCharacter(DEFAULT);
	}
}

void KenithalsChromaDlg::OnBnClickedWowwasd()
{
	m_ChromaSDKImpl.SetWoWWASD(m_WOWWASD.GetCheck() == 1);
}

void KenithalsChromaDlg::OnBnClickedWownums()
{
	m_ChromaSDKImpl.SetWoWNUMS(m_WOWNUMS.GetCheck() == 1);
}

void KenithalsChromaDlg::OnCbnSelchangeBgdisplay()
{
	switch (m_BGDISPLAY.GetCurSel())
	{
	case 1: m_ChromaSDKImpl.SetBGEffect(CChromaSDKImpl::Spectrum);
		break;
	case 2: m_ChromaSDKImpl.SetBGEffect(CChromaSDKImpl::Static);
		break;
	case 3: m_ChromaSDKImpl.SetBGEffect(CChromaSDKImpl::Character);
		break;
	default: m_ChromaSDKImpl.SetBGEffect(CChromaSDKImpl::Off);
	}
}


void KenithalsChromaDlg::OnEnChangeWowpath()
{
	std::ifstream ifs;
	CString text;
	m_WOWPATH.GetWindowText(text);

	CT2CA convertString(text);
	std::string textConvert(convertString);

	ifs.open(textConvert);

	if (ifs)
	{
		m_ChromaSDKImpl.SetPath(textConvert);
	}
}
