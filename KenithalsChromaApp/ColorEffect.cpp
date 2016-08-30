#include "stdafx.h"
#include "ColorEffect.h"

ColorEffect::~ColorEffect()
{
}

int ColorEffect::getR()
{
	return r;
}

void ColorEffect::setR(int _r)
{
	r = _r;
}

int ColorEffect::getG()
{
	return g;
}

void ColorEffect::setG(int _g)
{
	g = _g;
}

int ColorEffect::getB()
{
	return b;
}

void ColorEffect::setB(int _b)
{
	b = _b;
}