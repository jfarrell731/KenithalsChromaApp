#pragma once
#include "ColorEffect.h"
class SpectrumCycle : public ColorEffect
{
	int changeRate;
public:
	SpectrumCycle();
	~SpectrumCycle();

	void iterate();

	void setChangeRate(int newChangeRate);
};

