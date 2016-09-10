
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
	DDX_Control(pDX, IDC_WOWPATH, m_WOWPATH);
	DDX_Control(pDX, IDC_KEY_ESC, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_ESC)][LOBYTE(ChromaSDK::Keyboard::RZKEY_ESC)]);
	DDX_Control(pDX, IDC_KEY_F1, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_F1)][LOBYTE(ChromaSDK::Keyboard::RZKEY_F1)]);
	DDX_Control(pDX, IDC_KEY_F2, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_F2)][LOBYTE(ChromaSDK::Keyboard::RZKEY_F2)]);
	DDX_Control(pDX, IDC_KEY_F3, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_F3)][LOBYTE(ChromaSDK::Keyboard::RZKEY_F3)]);
	DDX_Control(pDX, IDC_KEY_F4, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_F4)][LOBYTE(ChromaSDK::Keyboard::RZKEY_F4)]);
	DDX_Control(pDX, IDC_KEY_F5, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_F5)][LOBYTE(ChromaSDK::Keyboard::RZKEY_F5)]);
	DDX_Control(pDX, IDC_KEY_F6, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_F6)][LOBYTE(ChromaSDK::Keyboard::RZKEY_F6)]);
	DDX_Control(pDX, IDC_KEY_F7, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_F7)][LOBYTE(ChromaSDK::Keyboard::RZKEY_F7)]);
	DDX_Control(pDX, IDC_KEY_F8, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_F8)][LOBYTE(ChromaSDK::Keyboard::RZKEY_F8)]);
	DDX_Control(pDX, IDC_KEY_F9, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_F9)][LOBYTE(ChromaSDK::Keyboard::RZKEY_F9)]);
	DDX_Control(pDX, IDC_KEY_F10, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_F10)][LOBYTE(ChromaSDK::Keyboard::RZKEY_F10)]);
	DDX_Control(pDX, IDC_KEY_F11, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_F11)][LOBYTE(ChromaSDK::Keyboard::RZKEY_F11)]);
	DDX_Control(pDX, IDC_KEY_F12, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_F12)][LOBYTE(ChromaSDK::Keyboard::RZKEY_F12)]);
	DDX_Control(pDX, IDC_KEY_PRNT, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_PRINTSCREEN)][LOBYTE(ChromaSDK::Keyboard::RZKEY_PRINTSCREEN)]);
	DDX_Control(pDX, IDC_KEY_SCRLL, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_SCROLL)][LOBYTE(ChromaSDK::Keyboard::RZKEY_SCROLL)]);
	DDX_Control(pDX, IDC_KEY_PAUSE, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_PAUSE)][LOBYTE(ChromaSDK::Keyboard::RZKEY_PAUSE)]);

	DDX_Control(pDX, IDC_KEY_M1, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_MACRO1)][LOBYTE(ChromaSDK::Keyboard::RZKEY_MACRO1)]);
	DDX_Control(pDX, IDC_KEY_TILDA, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_OEM_1)][LOBYTE(ChromaSDK::Keyboard::RZKEY_OEM_1)]);
	DDX_Control(pDX, IDC_KEY_1, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_1)][LOBYTE(ChromaSDK::Keyboard::RZKEY_1)]);
	DDX_Control(pDX, IDC_KEY_2, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_2)][LOBYTE(ChromaSDK::Keyboard::RZKEY_2)]);
	DDX_Control(pDX, IDC_KEY_3, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_3)][LOBYTE(ChromaSDK::Keyboard::RZKEY_3)]);
	DDX_Control(pDX, IDC_KEY_4, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_4)][LOBYTE(ChromaSDK::Keyboard::RZKEY_4)]);
	DDX_Control(pDX, IDC_KEY_5, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_5)][LOBYTE(ChromaSDK::Keyboard::RZKEY_5)]);
	DDX_Control(pDX, IDC_KEY_6, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_6)][LOBYTE(ChromaSDK::Keyboard::RZKEY_6)]);
	DDX_Control(pDX, IDC_KEY_7, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_7)][LOBYTE(ChromaSDK::Keyboard::RZKEY_7)]);
	DDX_Control(pDX, IDC_KEY_8, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_8)][LOBYTE(ChromaSDK::Keyboard::RZKEY_8)]);
	DDX_Control(pDX, IDC_KEY_9, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_9)][LOBYTE(ChromaSDK::Keyboard::RZKEY_9)]);
	DDX_Control(pDX, IDC_KEY_0, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_0)][LOBYTE(ChromaSDK::Keyboard::RZKEY_0)]);
	DDX_Control(pDX, IDC_KEY_MINUS, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_OEM_2)][LOBYTE(ChromaSDK::Keyboard::RZKEY_OEM_2)]);
	DDX_Control(pDX, IDC_KEY_EQUAL, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_OEM_3)][LOBYTE(ChromaSDK::Keyboard::RZKEY_OEM_3)]);
	DDX_Control(pDX, IDC_KEY_BKSPCE, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_BACKSPACE)][LOBYTE(ChromaSDK::Keyboard::RZKEY_BACKSPACE)]);
	DDX_Control(pDX, IDC_KEY_INS, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_INSERT)][LOBYTE(ChromaSDK::Keyboard::RZKEY_INSERT)]);
	DDX_Control(pDX, IDC_KEY_HOME, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_HOME)][LOBYTE(ChromaSDK::Keyboard::RZKEY_HOME)]);
	DDX_Control(pDX, IDC_KEY_PGUP, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_PAGEUP)][LOBYTE(ChromaSDK::Keyboard::RZKEY_PAGEUP)]);
	DDX_Control(pDX, IDC_KEY_NUM_LK, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_NUMLOCK)][LOBYTE(ChromaSDK::Keyboard::RZKEY_NUMLOCK)]);
	DDX_Control(pDX, IDC_KEY_NUM_SLASH, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_NUMPAD_DIVIDE)][LOBYTE(ChromaSDK::Keyboard::RZKEY_NUMPAD_DIVIDE)]);
	DDX_Control(pDX, IDC_KEY_NUM_STAR, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_NUMPAD_MULTIPLY)][LOBYTE(ChromaSDK::Keyboard::RZKEY_NUMPAD_MULTIPLY)]);
	DDX_Control(pDX, IDC_KEY_NUM_MINUS, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_NUMPAD_SUBTRACT)][LOBYTE(ChromaSDK::Keyboard::RZKEY_NUMPAD_SUBTRACT)]);

	DDX_Control(pDX, IDC_KEY_M2, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_MACRO2)][LOBYTE(ChromaSDK::Keyboard::RZKEY_MACRO2)]);
	DDX_Control(pDX, IDC_KEY_TAB, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_TAB)][LOBYTE(ChromaSDK::Keyboard::RZKEY_TAB)]);
	DDX_Control(pDX, IDC_KEY_Q, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_Q)][LOBYTE(ChromaSDK::Keyboard::RZKEY_Q)]);
	DDX_Control(pDX, IDC_KEY_W, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_W)][LOBYTE(ChromaSDK::Keyboard::RZKEY_W)]);
	DDX_Control(pDX, IDC_KEY_E, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_E)][LOBYTE(ChromaSDK::Keyboard::RZKEY_E)]);
	DDX_Control(pDX, IDC_KEY_R, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_R)][LOBYTE(ChromaSDK::Keyboard::RZKEY_R)]);
	DDX_Control(pDX, IDC_KEY_T, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_T)][LOBYTE(ChromaSDK::Keyboard::RZKEY_T)]);
	DDX_Control(pDX, IDC_KEY_Y, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_Y)][LOBYTE(ChromaSDK::Keyboard::RZKEY_Y)]);
	DDX_Control(pDX, IDC_KEY_U, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_U)][LOBYTE(ChromaSDK::Keyboard::RZKEY_U)]);
	DDX_Control(pDX, IDC_KEY_I, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_I)][LOBYTE(ChromaSDK::Keyboard::RZKEY_I)]);
	DDX_Control(pDX, IDC_KEY_O, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_O)][LOBYTE(ChromaSDK::Keyboard::RZKEY_O)]);
	DDX_Control(pDX, IDC_KEY_P, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_P)][LOBYTE(ChromaSDK::Keyboard::RZKEY_P)]);
	DDX_Control(pDX, IDC_KEY_LBKT, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_OEM_4)][LOBYTE(ChromaSDK::Keyboard::RZKEY_OEM_4)]);
	DDX_Control(pDX, IDC_KEY_RBKT, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_OEM_5)][LOBYTE(ChromaSDK::Keyboard::RZKEY_OEM_5)]);
	DDX_Control(pDX, IDC_KEY_BSLASH, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_OEM_6)][LOBYTE(ChromaSDK::Keyboard::RZKEY_OEM_6)]);
	DDX_Control(pDX, IDC_KEY_DEL, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_DELETE)][LOBYTE(ChromaSDK::Keyboard::RZKEY_DELETE)]);
	DDX_Control(pDX, IDC_KEY_END, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_END)][LOBYTE(ChromaSDK::Keyboard::RZKEY_END)]);
	DDX_Control(pDX, IDC_KEY_PGDWN, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_PAGEDOWN)][LOBYTE(ChromaSDK::Keyboard::RZKEY_PAGEDOWN)]);
	DDX_Control(pDX, IDC_KEY_NUM_7, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_NUMPAD7)][LOBYTE(ChromaSDK::Keyboard::RZKEY_NUMPAD7)]);
	DDX_Control(pDX, IDC_KEY_NUM_8, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_NUMPAD8)][LOBYTE(ChromaSDK::Keyboard::RZKEY_NUMPAD8)]);
	DDX_Control(pDX, IDC_KEY_NUM_9, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_NUMPAD9)][LOBYTE(ChromaSDK::Keyboard::RZKEY_NUMPAD9)]);
	DDX_Control(pDX, IDC_KEY_NUM_PLUS, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_NUMPAD_ADD)][LOBYTE(ChromaSDK::Keyboard::RZKEY_NUMPAD_ADD)]);

	DDX_Control(pDX, IDC_KEY_M3, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_MACRO3)][LOBYTE(ChromaSDK::Keyboard::RZKEY_MACRO3)]);
	DDX_Control(pDX, IDC_KEY_CAPS, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_CAPSLOCK)][LOBYTE(ChromaSDK::Keyboard::RZKEY_CAPSLOCK)]);
	DDX_Control(pDX, IDC_KEY_A, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_A)][LOBYTE(ChromaSDK::Keyboard::RZKEY_A)]);
	DDX_Control(pDX, IDC_KEY_S, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_S)][LOBYTE(ChromaSDK::Keyboard::RZKEY_S)]);
	DDX_Control(pDX, IDC_KEY_D, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_D)][LOBYTE(ChromaSDK::Keyboard::RZKEY_D)]);
	DDX_Control(pDX, IDC_KEY_F, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_F)][LOBYTE(ChromaSDK::Keyboard::RZKEY_F)]);
	DDX_Control(pDX, IDC_KEY_G, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_G)][LOBYTE(ChromaSDK::Keyboard::RZKEY_G)]);
	DDX_Control(pDX, IDC_KEY_H, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_H)][LOBYTE(ChromaSDK::Keyboard::RZKEY_H)]);
	DDX_Control(pDX, IDC_KEY_J, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_J)][LOBYTE(ChromaSDK::Keyboard::RZKEY_J)]);
	DDX_Control(pDX, IDC_KEY_K, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_K)][LOBYTE(ChromaSDK::Keyboard::RZKEY_K)]);
	DDX_Control(pDX, IDC_KEY_L, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_L)][LOBYTE(ChromaSDK::Keyboard::RZKEY_L)]);
	DDX_Control(pDX, IDC_KEY_COLON , m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_OEM_7)][LOBYTE(ChromaSDK::Keyboard::RZKEY_OEM_7)]);
	DDX_Control(pDX, IDC_KEY_QUOTE, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_OEM_8)][LOBYTE(ChromaSDK::Keyboard::RZKEY_OEM_8)]);
	DDX_Control(pDX, IDC_KEY_ENTER, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_ENTER)][LOBYTE(ChromaSDK::Keyboard::RZKEY_ENTER)]);
	DDX_Control(pDX, IDC_KEY_NUM_4, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_NUMPAD4)][LOBYTE(ChromaSDK::Keyboard::RZKEY_NUMPAD4)]);
	DDX_Control(pDX, IDC_KEY_NUM_5, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_NUMPAD5)][LOBYTE(ChromaSDK::Keyboard::RZKEY_NUMPAD5)]);
	DDX_Control(pDX, IDC_KEY_NUM_6, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_NUMPAD6)][LOBYTE(ChromaSDK::Keyboard::RZKEY_NUMPAD6)]);

	DDX_Control(pDX, IDC_KEY_M4, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_MACRO4)][LOBYTE(ChromaSDK::Keyboard::RZKEY_MACRO4)]);
	DDX_Control(pDX, IDC_KEY_LSHFT, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_LSHIFT)][LOBYTE(ChromaSDK::Keyboard::RZKEY_LSHIFT)]);
	DDX_Control(pDX, IDC_KEY_Z, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_Z)][LOBYTE(ChromaSDK::Keyboard::RZKEY_Z)]);
	DDX_Control(pDX, IDC_KEY_X, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_X)][LOBYTE(ChromaSDK::Keyboard::RZKEY_X)]);
	DDX_Control(pDX, IDC_KEY_C, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_C)][LOBYTE(ChromaSDK::Keyboard::RZKEY_C)]);
	DDX_Control(pDX, IDC_KEY_V, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_V)][LOBYTE(ChromaSDK::Keyboard::RZKEY_V)]);
	DDX_Control(pDX, IDC_KEY_B, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_B)][LOBYTE(ChromaSDK::Keyboard::RZKEY_B)]);
	DDX_Control(pDX, IDC_KEY_N, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_N)][LOBYTE(ChromaSDK::Keyboard::RZKEY_N)]);
	DDX_Control(pDX, IDC_KEY_M, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_M)][LOBYTE(ChromaSDK::Keyboard::RZKEY_M)]);
	DDX_Control(pDX, IDC_KEY_COMMA, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_OEM_9)][LOBYTE(ChromaSDK::Keyboard::RZKEY_OEM_9)]);
	DDX_Control(pDX, IDC_KEY_PERIOD, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_OEM_10)][LOBYTE(ChromaSDK::Keyboard::RZKEY_OEM_10)]);
	DDX_Control(pDX, IDC_KEY_FSLASH, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_OEM_11)][LOBYTE(ChromaSDK::Keyboard::RZKEY_OEM_11)]);
	DDX_Control(pDX, IDC_KEY_RSHFT, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_RSHIFT)][LOBYTE(ChromaSDK::Keyboard::RZKEY_RSHIFT)]);
	DDX_Control(pDX, IDC_KEY_UP, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_UP)][LOBYTE(ChromaSDK::Keyboard::RZKEY_UP)]);
	DDX_Control(pDX, IDC_KEY_NUM_1, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_NUMPAD1)][LOBYTE(ChromaSDK::Keyboard::RZKEY_NUMPAD1)]);
	DDX_Control(pDX, IDC_KEY_NUM_2, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_NUMPAD2)][LOBYTE(ChromaSDK::Keyboard::RZKEY_NUMPAD2)]);
	DDX_Control(pDX, IDC_KEY_NUM_3, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_NUMPAD3)][LOBYTE(ChromaSDK::Keyboard::RZKEY_NUMPAD3)]);

	DDX_Control(pDX, IDC_KEY_M5, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_MACRO5)][LOBYTE(ChromaSDK::Keyboard::RZKEY_MACRO5)]);
	DDX_Control(pDX, IDC_KEY_LCTRL, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_LCTRL)][LOBYTE(ChromaSDK::Keyboard::RZKEY_LCTRL)]);
	DDX_Control(pDX, IDC_KEY_WIN, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_LWIN)][LOBYTE(ChromaSDK::Keyboard::RZKEY_LWIN)]);
	DDX_Control(pDX, IDC_KEY_LALT, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_LALT)][LOBYTE(ChromaSDK::Keyboard::RZKEY_LALT)]);
	DDX_Control(pDX, IDC_KEY_SPACE, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_SPACE)][LOBYTE(ChromaSDK::Keyboard::RZKEY_SPACE)]);
	DDX_Control(pDX, IDC_KEY_RALT, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_RALT)][LOBYTE(ChromaSDK::Keyboard::RZKEY_RALT)]);
	DDX_Control(pDX, IDC_KEY_FN, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_FN)][LOBYTE(ChromaSDK::Keyboard::RZKEY_FN)]);
	DDX_Control(pDX, IDC_KEY_OPT, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_RMENU)][LOBYTE(ChromaSDK::Keyboard::RZKEY_RMENU)]);
	DDX_Control(pDX, IDC_KEY_RCTRL, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_RCTRL)][LOBYTE(ChromaSDK::Keyboard::RZKEY_RCTRL)]);
	DDX_Control(pDX, IDC_KEY_LEFT, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_LEFT)][LOBYTE(ChromaSDK::Keyboard::RZKEY_LEFT)]);
	DDX_Control(pDX, IDC_KEY_DOWN, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_DOWN)][LOBYTE(ChromaSDK::Keyboard::RZKEY_DOWN)]);
	DDX_Control(pDX, IDC_KEY_RIGHT, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_RIGHT)][LOBYTE(ChromaSDK::Keyboard::RZKEY_RIGHT)]);
	DDX_Control(pDX, IDC_KEY_NUM_0, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_NUMPAD0)][LOBYTE(ChromaSDK::Keyboard::RZKEY_NUMPAD0)]);
	DDX_Control(pDX, IDC_KEY_NUM_PERIOD, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_NUMPAD_DECIMAL)][LOBYTE(ChromaSDK::Keyboard::RZKEY_NUMPAD_DECIMAL)]);
	DDX_Control(pDX, IDC_KEY_NUM_ENTER, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZKEY_NUMPAD_ENTER)][LOBYTE(ChromaSDK::Keyboard::RZKEY_NUMPAD_ENTER)]);

	DDX_Control(pDX, IDC_KEY_RAZER_LOGO, m_Keyboard_Buttons[HIBYTE(ChromaSDK::Keyboard::RZLED_LOGO)][LOBYTE(ChromaSDK::Keyboard::RZLED_LOGO)]);

	DDX_Control(pDX, IDC_SELECT, m_Select);
	DDX_Control(pDX, IDC_DESELECT, m_Deselect);
	DDX_Control(pDX, IDC_APPLY, m_Apply);
	DDX_Control(pDX, IDC_DISPLAYTYPE, m_DisplayType);
	DDX_Control(pDX, IDC_STATICCOLOR, m_ColorPicker);
	DDX_Control(pDX, IDC_BRIGHTNESS, m_Brightness);
	DDX_Control(pDX, IDC_PROFILE, m_Profile);
	DDX_Control(pDX, IDC_SAVE, m_Save);
	DDX_Control(pDX, IDC_LOAD, m_Load);
}

BEGIN_MESSAGE_MAP(KenithalsChromaDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_WOWPATH, &KenithalsChromaDlg::OnEnChangeWowpath)
	ON_BN_CLICKED(IDC_SELECT, &KenithalsChromaDlg::OnBnClickedSelect)
	ON_BN_CLICKED(IDC_DESELECT, &KenithalsChromaDlg::OnBnClickedDeselect)
	ON_BN_CLICKED(IDC_APPLY, &KenithalsChromaDlg::OnBnClickedApply)
	ON_BN_CLICKED(IDC_SAVE, &KenithalsChromaDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_LOAD, &KenithalsChromaDlg::OnBnClickedLoad)
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

	m_DisplayType.SetCurSel(2);
	m_Brightness.SetRange(20, 100);
	m_Brightness.SetPos(50);

	m_Profile.SetCurSel(0);

	CString wowPath("C:\\Program Files\\World of Warcraft\\WTF\\Account\\!ACOUNTNAME!\\SavedVariables\\KenithalsChromaApp_WoWAddon.lua");

	m_WOWPATH.SetWindowText(wowPath);

	m_ChromaSDKImpl.SetPath("C:\\Program Files\\World of Warcraft\\WTF\\Account\\!ACOUNTNAME!\\SavedVariables\\KenithalsChromaApp_WoWAddon.lua");

	m_ChromaSDKImpl.setAll(CChromaSDKImpl::Effects::Spectrum, m_Brightness.GetPos());

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

void KenithalsChromaDlg::OnBnClickedSelect()
{
	for (int i = 0; i < ChromaSDK::Keyboard::MAX_ROW; i++)
		for (int j = 0; j < ChromaSDK::Keyboard::MAX_COLUMN; j++)
			if (m_Keyboard_Buttons[i][j])
				m_Keyboard_Buttons[i][j].SetCheck(1);
}

void KenithalsChromaDlg::OnBnClickedDeselect()
{
	for (int i = 0; i < ChromaSDK::Keyboard::MAX_ROW; i++)
		for (int j = 0; j < ChromaSDK::Keyboard::MAX_COLUMN; j++)
			if(m_Keyboard_Buttons[i][j])
				m_Keyboard_Buttons[i][j].SetCheck(0);
}

void KenithalsChromaDlg::OnBnClickedApply()
{
	for (int i = 0; i < ChromaSDK::Keyboard::MAX_ROW; i++)
	{
		for (int j = 0; j < ChromaSDK::Keyboard::MAX_COLUMN; j++)
		{
			if (m_Keyboard_Buttons[i][j] && m_Keyboard_Buttons[i][j].GetCheck() == 1)
			{
				switch (m_DisplayType.GetCurSel())
				{
				case 1:
					m_ChromaSDKImpl.setKey(i, j, CChromaSDKImpl::Effects::Character, m_Brightness.GetPos());
					break;
				case 2:
					m_ChromaSDKImpl.setKey(i, j, CChromaSDKImpl::Effects::Spectrum, m_Brightness.GetPos());
					break;
				case 3:
					m_ChromaSDKImpl.setKey(i, j, CChromaSDKImpl::Effects::Static, GetRValue(m_ColorPicker.GetColor()), GetGValue(m_ColorPicker.GetColor()), GetBValue(m_ColorPicker.GetColor()), m_Brightness.GetPos());
					break;
				default:
					m_ChromaSDKImpl.setKey(i, j, CChromaSDKImpl::Effects::Off, 0);
				}
			}
		}
	}
}

void KenithalsChromaDlg::OnBnClickedSave()
{
	m_ChromaSDKImpl.save(m_Profile.GetCurSel() + 1);
}

void KenithalsChromaDlg::OnBnClickedLoad()
{
	std::string newPath;

	newPath = m_ChromaSDKImpl.load(m_Profile.GetCurSel() + 1);

	CString pathText(newPath.c_str());

	m_WOWPATH.SetWindowText(pathText);
}
