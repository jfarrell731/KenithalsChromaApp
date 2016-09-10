#include "ChromaSDKImpl.h"
#pragma once
class Key
{
private:
	CChromaSDKImpl::Effects currentEffect;
	int r, g, b, brightness;

public:
	Key();
	~Key();

	void setEffect(CChromaSDKImpl::Effects newEffect);
	void setEffect(CChromaSDKImpl::Effects newEffect, int _r, int _g, int _b);
	void setEffect(CChromaSDKImpl::Effects newEffect, int _brightness);
	void setEffect(CChromaSDKImpl::Effects newEffect, int _r, int _g, int _b, int _brightness);
	void setColor(int _r, int _g, int _b);
	void setColor(int _r, int _g, int _b, int _brightness);
	void setBrightness(int _brightness);
	int getBrightness();

	CChromaSDKImpl::Effects getCurrentEffect();
	COLORREF getColor();
};

