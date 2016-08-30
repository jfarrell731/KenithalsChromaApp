#include "stdafx.h"
#include "SpectrumCycle.h"


SpectrumCycle::SpectrumCycle()
{
	r = g = b = 0;
	changeRate = 1;
}

SpectrumCycle::~SpectrumCycle()
{
}

void SpectrumCycle::iterate()
{
	if (r > 0 && g > 0 && b > 0)
		g = b -= changeRate * 2;
	else if (r == 255 && g < 255 && b == 0)
		g += changeRate;
	else if (r > 0 && g == 255 && b == 0)
		r -= changeRate;
	else  if (r == 0 && g == 255 && b < 255)
		b += changeRate;
	else if (r == 0 && g > 0 && b == 255)
		g -= changeRate;
	else if (r < 255 && g == 0 && b == 255)
		r += changeRate;
	else if (r == 255 && g == 0 && b > 0)
		b -= changeRate;
	else
		r += changeRate * 2;

	if (r < 0) r = 0;
	if (g < 0) g = 0;
	if (b < 0) b = 0;

	if (r > 255) r = 255;
	if (g > 255) g = 255;
	if (b > 255) b = 255;
}

void SpectrumCycle::setChangeRate(int newChangeRate)
{
	changeRate = newChangeRate;
}