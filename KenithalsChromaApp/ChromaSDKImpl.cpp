//! \example ChromaSDKImpl.cpp

#include "stdafx.h"
#include "ChromaSDKImpl.h"
#include "SpectrumCycle.h"
#include <string>
#include "Character.h"

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
UINT health = 0, power = 0, bgBrightness = 25, staticR = 0, staticG = 0, staticB = 0, charBrightness = 0, dynamicR = 0, dynamicG = 0, dynamicB = 0;
CChromaSDKImpl::Effects currentBGEffect = CChromaSDKImpl::Spectrum;
CChromaSDKImpl::Effects currentKBEffect = CChromaSDKImpl::Off;
std::string path;

SpectrumCycle spectrumInstance;
Character characterInstance;

CChromaSDKImpl instance;

DWORD WINAPI Thread_MainAnimation(LPVOID lpParameter)
{
	int bgDisplayR, bgDisplayG, bgDisplayB, kbDisplayR, kbDisplayG, kbDisplayB, mDisplayR, mDisplayG, mDisplayB;

	while (Anim)
	{
		if (CreateKeyboardEffect)
		{
			RZRESULT Result = RZRESULT_INVALID;
			ChromaSDK::Keyboard::CUSTOM_KEY_EFFECT_TYPE Effect = {};

			spectrumInstance.iterate();
			characterInstance.iterate();

			switch(currentBGEffect)
			{
			case CChromaSDKImpl::Spectrum:
				bgDisplayR = (int)((bgBrightness / 100.0) * spectrumInstance.getR());
				bgDisplayG = (int)((bgBrightness / 100.0) * spectrumInstance.getG());
				bgDisplayB = (int)((bgBrightness / 100.0) * spectrumInstance.getB());
				break;
			case CChromaSDKImpl::Static:
				bgDisplayR = (int)((bgBrightness / 100.0) * staticR);
				bgDisplayG = (int)((bgBrightness / 100.0) * staticG);
				bgDisplayB = (int)((bgBrightness / 100.0) * staticB);
				break;
			case CChromaSDKImpl::Character:
				bgDisplayR = (int)((bgBrightness / 100.0) * characterInstance.getR());
				bgDisplayG = (int)((bgBrightness / 100.0) * characterInstance.getG());
				bgDisplayB = (int)((bgBrightness / 100.0) * characterInstance.getB());
				break;
			default:
				bgDisplayR = 0;
				bgDisplayG = 0;
				bgDisplayB = 0;
			}

			for (int i = 0; i < ChromaSDK::Keyboard::MAX_ROW; i++)
				for (int j = 0; j < LOBYTE(ChromaSDK::Keyboard::RZKEY_NUMLOCK); j++)
					Effect.Key[i][j] = 0x01000000 | RGB(bgDisplayR, bgDisplayG, bgDisplayB);

			if (numPadBG)
			{
				for (int i = 0; i < ChromaSDK::Keyboard::MAX_ROW; i++)
					for (int j = LOBYTE(ChromaSDK::Keyboard::RZKEY_NUMLOCK); j < LOBYTE(ChromaSDK::Keyboard::MAX_COLUMN); j++)
						Effect.Key[i][j] = 0x01000000 | RGB(bgDisplayR, bgDisplayG, bgDisplayB);
			}

			Effect.Key[HIBYTE(ChromaSDK::Keyboard::RZLED_LOGO)][LOBYTE(ChromaSDK::Keyboard::RZLED_LOGO)] = 0x01000000 | RGB(bgDisplayR, bgDisplayG, bgDisplayB);

			switch(currentKBEffect)
			{
			case CChromaSDKImpl::Spectrum:
				kbDisplayR = (int)((charBrightness / 100.0) * spectrumInstance.getR());
				kbDisplayG = (int)((charBrightness / 100.0) * spectrumInstance.getG());
				kbDisplayB = (int)((charBrightness / 100.0) * spectrumInstance.getB());
				break;
			case CChromaSDKImpl::Static:
				kbDisplayR = (int)((charBrightness / 100.0) * staticR);
				kbDisplayG = (int)((charBrightness / 100.0) * staticG);
				kbDisplayB = (int)((charBrightness / 100.0) * staticB);
				break;
			case CChromaSDKImpl::Character:
				kbDisplayR = (int)((charBrightness / 100.0) * characterInstance.getR());
				kbDisplayG = (int)((charBrightness / 100.0) * characterInstance.getG());
				kbDisplayB = (int)((charBrightness / 100.0) * characterInstance.getB());
				break;
			default:
				kbDisplayR = 0;
				kbDisplayG = 0;
				kbDisplayB = 0;
			}

			if (WASD)
			{
				Effect.Key[HIBYTE(ChromaSDK::Keyboard::RZKEY_W)][LOBYTE(ChromaSDK::Keyboard::RZKEY_W)] = 0x01000000 | RGB(kbDisplayR, kbDisplayG, kbDisplayB);
				Effect.Key[HIBYTE(ChromaSDK::Keyboard::RZKEY_A)][LOBYTE(ChromaSDK::Keyboard::RZKEY_A)] = 0x01000000 | RGB(kbDisplayR, kbDisplayG, kbDisplayB);
				Effect.Key[HIBYTE(ChromaSDK::Keyboard::RZKEY_S)][LOBYTE(ChromaSDK::Keyboard::RZKEY_S)] = 0x01000000 | RGB(kbDisplayR, kbDisplayG, kbDisplayB);
				Effect.Key[HIBYTE(ChromaSDK::Keyboard::RZKEY_D)][LOBYTE(ChromaSDK::Keyboard::RZKEY_D)] = 0x01000000 | RGB(kbDisplayR, kbDisplayG, kbDisplayB);
			}

			if (NUMS)
			{
				for (int i = 2; i < LOBYTE(ChromaSDK::Keyboard::RZKEY_6); i++)
					Effect.Key[1][i] = 0x01000000 | RGB(kbDisplayR, kbDisplayG, kbDisplayB);
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

		if (CreateMouseEffect)
		{
			if (mouseOn)
			{
				mDisplayR = bgDisplayR;
				mDisplayG = bgDisplayG;
				mDisplayB = bgDisplayB;
			}
			else
			{
				mDisplayR = 0;
				mDisplayG = 0;
				mDisplayB = 0;
			}

			ChromaSDK::Mouse::CUSTOM_EFFECT_TYPE Effect = {};
			for(int i = 1; i <= Mouse::RZLED_SIDE_STRIP14; i++)
				Effect.Color[i] = RGB(mDisplayR, mDisplayG, mDisplayB);

			CreateMouseEffect(ChromaSDK::Mouse::CHROMA_CUSTOM, &Effect, NULL);
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

void CChromaSDKImpl::setStaticCharacter(int r, int g, int b)
{
	staticR = r;
	staticG = g;
	staticB = b;
}

void CChromaSDKImpl::StopAnim()
{
	Anim = false;
}

void CChromaSDKImpl::StartAnim()
{
	Anim = true;
}

void CChromaSDKImpl::SetBGEffect(CChromaSDKImpl::Effects newEffect)
{
	currentBGEffect = newEffect;
}

void CChromaSDKImpl::SetPath(std::string newPath)
{
	characterInstance.setPath(newPath);
}

void CChromaSDKImpl::SetKBEffect(Effects newEffect)
{
	currentKBEffect = newEffect;
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

