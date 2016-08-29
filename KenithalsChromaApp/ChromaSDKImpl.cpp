//! \example ChromaSDKImpl.cpp

#include "stdafx.h"
#include "ChromaSDKImpl.h"

#ifdef _WIN64
#define CHROMASDKDLL        _T("RzChromaSDK64.dll")
#else
#define CHROMASDKDLL        _T("RzChromaSDK.dll")
#endif

using namespace ChromaSDK;
using namespace ChromaSDK::Keyboard;
using namespace ChromaSDK::Keypad;
using namespace ChromaSDK::Mouse;
using namespace ChromaSDK::Mousepad;
using namespace ChromaSDK::Headset;

typedef RZRESULT (*INIT)(void);
typedef RZRESULT (*UNINIT)(void);
typedef RZRESULT (*CREATEEFFECT)(RZDEVICEID DeviceId, ChromaSDK::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT (*CREATEKEYBOARDEFFECT)(ChromaSDK::Keyboard::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT (*CREATEHEADSETEFFECT)(ChromaSDK::Headset::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT (*CREATEMOUSEPADEFFECT)(ChromaSDK::Mousepad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT (*CREATEMOUSEEFFECT)(ChromaSDK::Mouse::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT (*CREATEKEYPADEFFECT)(ChromaSDK::Keypad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT (*SETEFFECT)(RZEFFECTID EffectId);
typedef RZRESULT (*DELETEEFFECT)(RZEFFECTID EffectId);
typedef RZRESULT (*REGISTEREVENTNOTIFICATION)(HWND hWnd);
typedef RZRESULT (*UNREGISTEREVENTNOTIFICATION)(void);
typedef RZRESULT (*QUERYDEVICE)(RZDEVICEID DeviceId, ChromaSDK::DEVICE_INFO_TYPE &DeviceInfo);

INIT Init = NULL;
UNINIT UnInit = NULL;
CREATEEFFECT CreateEffect = NULL;
CREATEKEYBOARDEFFECT CreateKeyboardEffect = NULL;
CREATEMOUSEEFFECT CreateMouseEffect = NULL;
CREATEHEADSETEFFECT CreateHeadsetEffect = NULL;
CREATEMOUSEPADEFFECT CreateMousepadEffect = NULL;
CREATEKEYPADEFFECT CreateKeypadEffect = NULL;
SETEFFECT SetEffect = NULL;
DELETEEFFECT DeleteEffect = NULL;
QUERYDEVICE QueryDevice = NULL;

bool Anim = false, numPadBG = true, numPadBars = false, mouseOn = true, WASD = false, NUMS = false;
UINT health = 0, power = 0, bgBrightness = 100, charR = 0, charG = 0, charB = 0, charBrightness = 50;
CChromaSDKImpl::BGEffects currentBGEffect = CChromaSDKImpl::Spectrum;

DWORD WINAPI Thread_MainAnimation(LPVOID lpParameter)
{
	int r = 255, g = 255, b = 255, displayR, displayG, displayB, charDisplayR, charDisplayG, charDisplayB;

	while (Anim)
	{
		if (CreateKeyboardEffect)
		{
			RZRESULT Result = RZRESULT_INVALID;
			ChromaSDK::Keyboard::CUSTOM_KEY_EFFECT_TYPE Effect = {};

			if (currentBGEffect == CChromaSDKImpl::Spectrum)
			{
				displayR = (int)((bgBrightness / 100.0) * r);
				displayG = (int)((bgBrightness / 100.0) * g);
				displayB = (int)((bgBrightness / 100.0) * b);

				if (r == 255 && g > 0 && b > 0)
					g = b -= SPECTRUM_CHANGE_RATE;
				else if (r == 255 && g < 255 && b == 0)
					g += SPECTRUM_CHANGE_RATE;
				else if (r > 0 && g == 255 && b == 0)
					r -= SPECTRUM_CHANGE_RATE;
				else  if (r == 0 && g == 255 && b < 255)
					b += SPECTRUM_CHANGE_RATE;
				else if (r == 0 && g > 0 && b == 255)
					g -= SPECTRUM_CHANGE_RATE;
				else if (r < 255 && g == 0 && b == 255)
					r += SPECTRUM_CHANGE_RATE;
				else if (r == 255 && g == 0 && b > 0)
					b -= SPECTRUM_CHANGE_RATE;

				if (r < 0) r = 0;
				if (g < 0) g = 0;
				if (b < 0) b = 0;

				if (r > 255) r = 255;
				if (g > 255) g = 255;
				if (b > 255) b = 255;
			}
			else
			{
				displayR = 0;
				displayG = 0;
				displayB = 0;
			}

			for (int i = 0; i < ChromaSDK::Keyboard::MAX_ROW; i++)
				for (int j = 0; j < LOBYTE(ChromaSDK::Keyboard::RZKEY_NUMLOCK); j++)
					Effect.Key[i][j] = 0x01000000 | RGB(displayR, displayG, displayB);

			if (numPadBG)
			{
				for (int i = 0; i < ChromaSDK::Keyboard::MAX_ROW; i++)
					for (int j = LOBYTE(ChromaSDK::Keyboard::RZKEY_NUMLOCK); j < LOBYTE(ChromaSDK::Keyboard::MAX_COLUMN); j++)
						Effect.Key[i][j] = 0x01000000 | RGB(displayR, displayG, displayB);
			}

			Effect.Key[HIBYTE(ChromaSDK::Keyboard::RZLED_LOGO)][LOBYTE(ChromaSDK::Keyboard::RZLED_LOGO)] = 0x01000000 | RGB(displayR, displayG, displayB);;

			charDisplayR = (int)((charBrightness / 100.0) * charR);
			charDisplayG = (int)((charBrightness / 100.0) * charG);
			charDisplayB = (int)((charBrightness / 100.0) * charB);

			if (WASD)
			{
				Effect.Key[HIBYTE(ChromaSDK::Keyboard::RZKEY_W)][LOBYTE(ChromaSDK::Keyboard::RZKEY_W)] = 0x01000000 | RGB(charDisplayR, charDisplayG, charDisplayB);
				Effect.Key[HIBYTE(ChromaSDK::Keyboard::RZKEY_A)][LOBYTE(ChromaSDK::Keyboard::RZKEY_A)] = 0x01000000 | RGB(charDisplayR, charDisplayG, charDisplayB);
				Effect.Key[HIBYTE(ChromaSDK::Keyboard::RZKEY_S)][LOBYTE(ChromaSDK::Keyboard::RZKEY_S)] = 0x01000000 | RGB(charDisplayR, charDisplayG, charDisplayB);
				Effect.Key[HIBYTE(ChromaSDK::Keyboard::RZKEY_D)][LOBYTE(ChromaSDK::Keyboard::RZKEY_D)] = 0x01000000 | RGB(charDisplayR, charDisplayG, charDisplayB);
			}

			if (NUMS)
			{
				for (int i = 2; i < LOBYTE(ChromaSDK::Keyboard::RZKEY_6); i++)
					Effect.Key[1][i] = 0x01000000 | RGB(charDisplayR, charDisplayG, charDisplayB);
			}

			if (numPadBars)
			{
				// Function keys as health
				UINT RemainingHealth = UINT(health / 100.0 * 50.0); // Number of rows to fill based on hp

				COLORREF HpColor = RGB((((50 - RemainingHealth) / 50.0) * 255), ((RemainingHealth / 50.0) * 255), 0);

				for (UINT i = 0; i <= RemainingHealth / 11; i++)
					for (UINT j = LOBYTE(RZKEY_NUMLOCK); j <= LOBYTE(RZKEY_NUMPAD_DIVIDE); j++)
						Effect.Key[(ChromaSDK::Keyboard::MAX_ROW - 1) - i][j] = 0x01000000 | HpColor;

				UINT RemainingAmmo = UINT(power / 100.0 * 50.0); // Number of rows to fill based on mana

				COLORREF ManaColor = RGB(0, (((50 - RemainingAmmo) / 50.0) * 120), (((20 + RemainingAmmo) / 70.0) * 255));

				for (UINT i = 0; i <= RemainingAmmo / 11; i++)
					for (UINT j = LOBYTE(RZKEY_NUMPAD_MULTIPLY); j <= LOBYTE(RZKEY_NUMPAD_SUBTRACT); j++)
						Effect.Key[(ChromaSDK::Keyboard::MAX_ROW - 1) - i][j] = 0x01000000 | ManaColor;
			}
			Result = CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_CUSTOM_KEY, &Effect, NULL);

			ASSERT(Result == RZRESULT_SUCCESS);
		}

		if (CreateMouseEffect && mouseOn)
		{
			ChromaSDK::Mouse::CUSTOM_EFFECT_TYPE Effect = {};
			for(int i = 1; i <= Mouse::RZLED_SIDE_STRIP14; i++)
				Effect.Color[i] = RGB(displayR, displayG, displayB);

			CreateMouseEffect(ChromaSDK::Mouse::CHROMA_CUSTOM, &Effect, NULL);
		}
		else if (CreateMouseEffect)
		{
			CreateMouseEffect(ChromaSDK::Mouse::CHROMA_NONE, NULL, NULL);
		}

		Sleep(50);
	}

	return 0;
}

CChromaSDKImpl::CChromaSDKImpl():m_ChromaSDKModule(NULL)
{
}

CChromaSDKImpl::~CChromaSDKImpl()
{
}

BOOL CChromaSDKImpl::Initialize()
{
    if(m_ChromaSDKModule == NULL)
    {
        m_ChromaSDKModule = LoadLibrary(CHROMASDKDLL);
        if(m_ChromaSDKModule == NULL)
        {
            ASSERT(GetLastError() == ERROR_SUCCESS);
            return FALSE;
        }
    }

    if(Init == NULL)
    {
        RZRESULT Result = RZRESULT_INVALID;
        Init = (INIT)GetProcAddress(m_ChromaSDKModule, "Init");
        if(Init)
        {
            Result = Init();
            if(Result == RZRESULT_SUCCESS)
            {
                CreateEffect = (CREATEEFFECT)GetProcAddress(m_ChromaSDKModule, "CreateEffect");
                CreateKeyboardEffect = (CREATEKEYBOARDEFFECT)GetProcAddress(m_ChromaSDKModule, "CreateKeyboardEffect");
                CreateMouseEffect = (CREATEMOUSEEFFECT)GetProcAddress(m_ChromaSDKModule, "CreateMouseEffect");
                CreateHeadsetEffect = (CREATEHEADSETEFFECT)GetProcAddress(m_ChromaSDKModule, "CreateHeadsetEffect");
                CreateMousepadEffect = (CREATEMOUSEPADEFFECT)GetProcAddress(m_ChromaSDKModule, "CreateMousepadEffect");
                CreateKeypadEffect = (CREATEKEYPADEFFECT)GetProcAddress(m_ChromaSDKModule, "CreateKeypadEffect");
                SetEffect = (SETEFFECT)GetProcAddress(m_ChromaSDKModule, "SetEffect");
                DeleteEffect = (DELETEEFFECT)GetProcAddress(m_ChromaSDKModule, "DeleteEffect");
                QueryDevice = (QUERYDEVICE)GetProcAddress(m_ChromaSDKModule, "QueryDevice");

                if(CreateEffect &&
                    CreateKeyboardEffect &&
                    CreateMouseEffect &&
                    CreateHeadsetEffect &&
                    CreateMousepadEffect &&
                    CreateKeypadEffect &&
                    SetEffect &&
                    DeleteEffect &&
                    QueryDevice)
                {
                    return TRUE;
                }
                else
                {
                    return FALSE;
                }
            }
        }
    }

    return TRUE;
}

BOOL CChromaSDKImpl::UnInitialize()
{
    if(m_ChromaSDKModule != NULL)
    {
        RZRESULT Result = RZRESULT_INVALID;
        UNINIT UnInit = (UNINIT)GetProcAddress(m_ChromaSDKModule, "UnInit");
        if(UnInit)
        {
            Result = UnInit();
            ASSERT(Result == RZRESULT_SUCCESS);
        }

        FreeLibrary(m_ChromaSDKModule);
        m_ChromaSDKModule = NULL;

        return TRUE;
    }

    return FALSE;
}

void CChromaSDKImpl::UpdateBGBrightness(UINT Brightness)
{
	bgBrightness = Brightness;
}

void CChromaSDKImpl::UpdateCharacterBrightness(UINT Brightness)
{
	charBrightness = Brightness;
}

void CChromaSDKImpl::MainAnimation()
{
	HANDLE hWorkerThread = NULL;
	hWorkerThread = CreateThread(NULL, 0, Thread_MainAnimation, this, 0, NULL);
	CloseHandle(hWorkerThread);
}

void CChromaSDKImpl::ShowLevel(UINT Hp, UINT Ammo)
{
	health = Hp;
	power = Ammo;
}

void CChromaSDKImpl::setCharacter(int r, int g, int b)
{
	charR = r;
	charG = g;
	charB = b;
}

void CChromaSDKImpl::StopAnim()
{
	Anim = false;
}

void CChromaSDKImpl::StartAnim()
{
	Anim = true;
}

void CChromaSDKImpl::SetBGEffect(CChromaSDKImpl::BGEffects newEffect)
{
	currentBGEffect = newEffect;
}

void CChromaSDKImpl::SetMouseBG(bool On)
{
	mouseOn = On;
}

void CChromaSDKImpl::SetNPBG(bool On)
{
	numPadBG = On;
}

void CChromaSDKImpl::SetNPBars(bool On)
{
	numPadBars = On;
}

void CChromaSDKImpl::SetWoWWASD(bool On)
{
	WASD = On;
}

void CChromaSDKImpl::SetWoWNUMS(bool On)
{
	NUMS = On;
}

void CChromaSDKImpl::ResetEffects(UINT DeviceType)
{
        if(CreateKeyboardEffect)
        {
            CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_NONE, NULL, NULL);
        }
        if(CreateMouseEffect)
        {
            CreateMouseEffect(ChromaSDK::Mouse::CHROMA_NONE, NULL, NULL);
        }
}

BOOL CChromaSDKImpl::IsDeviceConnected(RZDEVICEID DeviceId)
{
    if(QueryDevice != NULL)
    {
        ChromaSDK::DEVICE_INFO_TYPE DeviceInfo = {};
        RZRESULT Result = QueryDevice(DeviceId, DeviceInfo);

        ASSERT(Result == RZRESULT_SUCCESS);

        return DeviceInfo.Connected;
    }

    return FALSE;
}

