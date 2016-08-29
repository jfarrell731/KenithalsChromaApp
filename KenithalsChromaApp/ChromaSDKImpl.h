
#ifndef _CHROMASDKIMPL_H_
#define _CHROMASDKIMPL_H_

#pragma once

#include "ChromaSDK\inc\RzChromaSDKDefines.h"
#include "ChromaSDK\inc\RzChromaSDKTypes.h"
#include "ChromaSDK\inc\RzErrors.h"

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

	enum BGEffects {
		None = 0,
		Spectrum
	};

    void ShowLevel(UINT Hp, UINT Ammo);
	void UpdateBGBrightness(UINT Brightness);
	void UpdateCharacterBrightness(UINT Brightness);
	void setCharacter(int r, int g, int b);
	void SetBGEffect(BGEffects newEffect);
	void SetMouseBG(bool On);
	void SetNPBG(bool On);
	void SetNPBars(bool On);
	void SetWoWWASD(bool On);
	void SetWoWNUMS(bool On);
	void MainAnimation();
	void StartAnim();
	void StopAnim();
    void ResetEffects(UINT DeviceType);
    BOOL IsDeviceConnected(RZDEVICEID DeviceId);

private:
    HMODULE m_ChromaSDKModule;
};

#endif
