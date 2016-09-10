//! \example ChromaSDKImpl.cpp

#include "stdafx.h"
#include "ChromaSDKImpl.h"
#include "SpectrumCycle.h"
#include <string>
#include "Character.h"
#include "KeyboardData.h"
#include "MouseData.h"

#ifdef _WIN64
#define CHROMASDKDLL        _T("RzChromaSDK64.dll")
#else
#define CHROMASDKDLL        _T("RzChromaSDK.dll")
#endif

// For convenience on output
#define NL std::endl

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

SpectrumCycle spectrumInstance;
Character characterInstance;
KeyboardData keyboardInstance;
MouseData mouseInstance;

DWORD WINAPI Thread_MainAnimation(LPVOID lpParameter)
{
	while (Anim)
	{
		if (CreateKeyboardEffect)
		{
			RZRESULT Result = RZRESULT_INVALID;
			ChromaSDK::Keyboard::CUSTOM_KEY_EFFECT_TYPE Effect = {};

			spectrumInstance.iterate();
			characterInstance.iterate();

			for (int i = 0; i < ChromaSDK::Keyboard::MAX_ROW; i++)
			{
				for (int j = 0; j < ChromaSDK::Keyboard::MAX_COLUMN; j++)
				{
					switch (keyboardInstance(i, j).getCurrentEffect())
					{
					case CChromaSDKImpl::Spectrum:
						keyboardInstance(i, j).setColor(spectrumInstance.getR(), spectrumInstance.getG(), spectrumInstance.getB());
						break;
					case CChromaSDKImpl::Character:
						keyboardInstance(i, j).setColor(characterInstance.getR(), characterInstance.getG(), characterInstance.getB());
						break;
					case CChromaSDKImpl::Off:
						keyboardInstance(i, j).setColor(0, 0, 0);
						break;
					}

					Effect.Key[i][j] = 0x01000000 | keyboardInstance(i, j).getColor();
				}
			}

			Result = CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_CUSTOM_KEY, &Effect, NULL);

			ASSERT(Result == RZRESULT_SUCCESS);
		}

		if (CreateMouseEffect)
		{
			ChromaSDK::Mouse::CUSTOM_EFFECT_TYPE2 Effect = {};
			for (int i = 0; i < ChromaSDK::Mouse::MAX_ROW; i++)
			{
				for (int j = 0; j < ChromaSDK::Mouse::MAX_COLUMN; j++)
				{
					switch (mouseInstance(i, j).getCurrentEffect())
					{
					case CChromaSDKImpl::Spectrum:
						mouseInstance(i, j).setColor(spectrumInstance.getR(), spectrumInstance.getG(), spectrumInstance.getB());
						break;
					case CChromaSDKImpl::Character:
						mouseInstance(i, j).setColor(characterInstance.getR(), characterInstance.getG(), characterInstance.getB());
						break;
					case CChromaSDKImpl::Off:
						mouseInstance(i, j).setColor(0, 0, 0);
						break;
					}

					Effect.Color[i][j] = mouseInstance(i, j).getColor();
				}
			}

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
		std::string appData = getenv("APPDATA"), folder = appData + "\\KenithalsChromaApp";

		CString Sfolder(folder.c_str());

		CreateDirectory(Sfolder, NULL);

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

void CChromaSDKImpl::setAll(Effects newEffect, int brightness)
{
	keyboardInstance.setAll(newEffect, brightness);
	mouseInstance.setAll(newEffect, brightness);
}

void CChromaSDKImpl::setAll(Effects newEffect, int r, int g, int b, int brightness)
{
	keyboardInstance.setAll(newEffect, r, g, b, brightness);
	mouseInstance.setAll(newEffect, r, g, b, brightness);
}

void CChromaSDKImpl::setKey(int row, int col, CChromaSDKImpl::Effects newEffect, int brightness)
{
	keyboardInstance(row, col).setEffect(newEffect, brightness);
}

void CChromaSDKImpl::setKey(int row, int col, CChromaSDKImpl::Effects newEffect, int r, int g, int b, int brightness)
{
	keyboardInstance(row, col).setEffect(newEffect, r, g, b, brightness);
}

void CChromaSDKImpl::MainAnimation()
{
	HANDLE hWorkerThread = NULL;
	hWorkerThread = CreateThread(NULL, 0, Thread_MainAnimation, this, 0, NULL);
	CloseHandle(hWorkerThread);
}

void CChromaSDKImpl::save(int profileNum)
{
	std::string appData = getenv("APPDATA"), profile = appData + "\\KenithalsChromaApp\\profile" + std::to_string(profileNum);
	
	std::ofstream pos(profile, std::ofstream::out);

	pos << "WoWIntegration: ' " << characterInstance.getPath() << " '" << NL;

	pos << NL << "Keyboard" << NL << "{" << NL;

	for (int i = 0; i < ChromaSDK::Keyboard::MAX_ROW; i++)
	{
		for (int j = 0; j < ChromaSDK::Keyboard::MAX_COLUMN; j++)
		{
			pos << "\tKey " << i << " " << j << NL << "\t{" << NL;
			pos << "\t\trgb: " << std::to_string(GetRValue(keyboardInstance(i, j).getColor())) << " " << std::to_string(GetGValue(keyboardInstance(i, j).getColor())) << " " << std::to_string(GetBValue(keyboardInstance(i, j).getColor())) << NL;
			pos << "\t\tbrightness: " << std::to_string(keyboardInstance(i, j).getBrightness()) << NL;
			pos << "\t\teffect: " << std::to_string(keyboardInstance(i, j).getCurrentEffect()) << NL;
			pos << "\t}" << NL;
		}
	}

	pos << "}" << NL;

	pos << NL << "Mouse" << NL << "{" << NL;

	for (int i = 0; i < ChromaSDK::Mouse::MAX_ROW; i++)
	{
		for (int j = 0; j < ChromaSDK::Mouse::MAX_COLUMN; j++)
		{
			pos << "\tKey " << i << " " << j << NL << "\t{" << NL;
			pos << "\t\trgb: " << std::to_string(GetRValue(mouseInstance(i, j).getColor())) << " " << std::to_string(GetGValue(mouseInstance(i, j).getColor())) << " " << std::to_string(GetBValue(mouseInstance(i, j).getColor())) << NL;
			pos << "\t\tbrightness: " << std::to_string(mouseInstance(i, j).getBrightness()) << NL;
			pos << "\t\teffect: " << std::to_string(mouseInstance(i, j).getCurrentEffect()) << NL;
			pos << "\t}" << NL;
		}
	}

	pos << "}" << NL;

	pos.close();
}

std::string CChromaSDKImpl::load(int profileNum)
{
	std::string appData = getenv("APPDATA"), profile = appData + "\\KenithalsChromaApp\\profile" + std::to_string(profileNum), filler, path;
	int row, col, r, g, b, brightness, effect;

	std::ifstream pis(profile, std::ios::beg);
	path = "";

	if (pis.is_open())
	{
		while (!pis.eof())
		{
			pis >> filler;
			if (filler == "WoWIntegration:")
			{
				pis >> filler >> filler;
				path = "";
				do
				{
					if (path == "")
						path += filler;
					else
						path += " " + filler;
					pis >> filler;
				} while (filler != "'");

				characterInstance.setPath(path);
			}

			if (filler == "Keyboard")
			{
				pis >> filler >> filler;
				do
				{
					if (filler == "Key")
					{
						pis >> row >> col;
						pis >> filler;
						pis >> filler >> r >> g >> b;
						pis >> filler >> brightness;
						pis >> filler >> effect;

						keyboardInstance(row, col).setEffect(CChromaSDKImpl::Effects(effect), r, g, b, brightness);

						pis >> filler >> filler;
					}

				} while (filler != "}");
			}

			if (filler == "Mouse")
			{
				pis >> filler >> filler;
				do
				{
					if (filler == "Key")
					{
						pis >> row >> col;
						pis >> filler;
						pis >> filler >> r >> g >> b;
						pis >> filler >> brightness;
						pis >> filler >> effect;

						mouseInstance(row, col).setEffect(CChromaSDKImpl::Effects(effect), r, g, b, brightness);

						pis >> filler >> filler;
					}

				} while (filler != "}");
			}
		}
	}

	pis.close();

	return path;
}

void CChromaSDKImpl::StopAnim()
{
	Anim = false;
}

void CChromaSDKImpl::StartAnim()
{
	Anim = true;
}

void CChromaSDKImpl::SetPath(std::string newPath)
{
	characterInstance.setPath(newPath);
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

