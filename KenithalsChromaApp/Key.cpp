#include "stdafx.h"
#include "Key.h"


Key::Key()
{
	r = g = b = brightness = 0;
	currentEffect = CChromaSDKImpl::Off;
}


Key::~Key()
{
}

void Key::setEffect(CChromaSDKImpl::Effects newEffect)
{
	currentEffect = newEffect;
}

void Key::setEffect(CChromaSDKImpl::Effects newEffect, int _r, int _g, int _b)
{
	currentEffect = newEffect;
	setColor(_r, _g, _b);
}

void Key::setEffect(CChromaSDKImpl::Effects newEffect, int _brightness)
{
	currentEffect = newEffect;
	setBrightness(_brightness);
}

void Key::setEffect(CChromaSDKImpl::Effects newEffect, int _r, int _g, int _b, int _brightness)
{
	currentEffect = newEffect;
	setColor(_r, _g, _b);
	setBrightness(_brightness);
}

void Key::setColor(int _r, int _g, int _b)
{
	r = _r;
	g = _g;
	b = _b;
}

void Key::setColor(int _r, int _g, int _b, int _brightness)
{
	r = _r;
	g = _g;
	b = _b;
	setBrightness(_brightness);
}

void Key::setBrightness(int _brightness)
{
	brightness = _brightness;
}

CChromaSDKImpl::Effects Key::getCurrentEffect()
{
	return currentEffect;
}

COLORREF Key::getColor()
{
	int _r, _g, _b;

	_r = (int)((brightness / 100.0) * r);
	_g = (int)((brightness / 100.0) * g);
	_b = (int)((brightness / 100.0) * b);

	return RGB(_r, _g, _b);
}
