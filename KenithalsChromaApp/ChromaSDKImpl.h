
#ifndef _CHROMASDKIMPL_H_
#define _CHROMASDKIMPL_H_

#pragma once

#include "ChromaSDK\inc\RzChromaSDKDefines.h"
#include "ChromaSDK\inc\RzChromaSDKTypes.h"
#include "ChromaSDK\inc\RzErrors.h"
#include <string>

const COLORREF BLACK = RGB(0,0,0);
const COLORREF WHITE = RGB(255,255,255);
const COLORREF RED = RGB(255,0,0);
const COLORREF GREEN = RGB(0,255,0);
const COLORREF BLUE = RGB(0,0,255);
const COLORREF YELLOW = RGB(255,255,0);
const COLORREF PURPLE = RGB(128,0,128);
const COLORREF CYAN = RGB(00,255,255);
const COLORREF ORANGE = RGB(255,165,00);
const COLORREF PINK = RGB(255,192,203);
const COLORREF GREY = RGB(125, 125, 125);

#define DEATHKNIGHT		255, 0, 5
#define	DEMONHUNTER		80, 0, 255
#define DRUID			255, 60, 0
#define HUNTER			10, 255, 10
#define MAGE			50, 150, 255
#define MONK			0, 255, 90
#define PALADIN			255, 50, 90
#define PRIEST			255, 255, 255
#define ROGUE			255, 245, 20
#define SHAMAN			0, 55, 255
#define WARLOCK			200, 60, 255
#define WARRIOR			255, 150, 40
#define DEFAULT			0, 0, 0

#define ALL_DEVICES         0
#define KEYBOARD_DEVICES    1
#define MOUSEMAT_DEVICES    2
#define MOUSE_DEVICES       3
#define HEADSET_DEVICES     4
#define KEYPAD_DEVICES      5

#define SPECTRUM_CHANGE_RATE 1

class CChromaSDKImpl
{
public:
    CChromaSDKImpl();
    ~CChromaSDKImpl();

    BOOL Initialize();
    BOOL UnInitialize();

	enum Effects {
		Off = 0,
		Spectrum,
		Static,
		Character
	};

	void setAll(Effects newEffect, int brightness);
	void setAll(Effects newEffect, int r, int g, int b, int brightness);
	void setKeyboardKey(int row, int col, Effects newEffect, int brightness);
	void setKeyboardKey(int row, int col, Effects newEffect, int r, int g, int b, int brightness);
	void setMouseKey(int row, int col, Effects newEffect, int brightness);
	void setMouseKey(int row, int col, Effects newEffect, int r, int g, int b, int brightness);
	void SetPath(std::string newPath);
	void MainAnimation();
	void StartAnim();
	void StopAnim();
    void ResetEffects(UINT DeviceType);
	void save(int profileNum);
	std::string load(int profileNum);
    BOOL IsDeviceConnected(RZDEVICEID DeviceId);

private:
    HMODULE m_ChromaSDKModule;
	
};

#endif
