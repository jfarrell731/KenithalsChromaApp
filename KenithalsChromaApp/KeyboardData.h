#include "ChromaSDKImpl.h"
#include "Key.h"

#pragma once
class KeyboardData
{
private:
	Key keySet[ChromaSDK::Keyboard::MAX_ROW][ChromaSDK::Keyboard::MAX_COLUMN];

public:
	KeyboardData();
	~KeyboardData();

	void setAll(CChromaSDKImpl::Effects newEffect);
	void setAll(CChromaSDKImpl::Effects newEffect, int r, int g, int b);
	void setAll(CChromaSDKImpl::Effects newEffect, int brightness);
	void setAll(CChromaSDKImpl::Effects newEffect, int r, int g, int b, int brightness);
	void setAll(int r, int g, int b);
	void setAll(int r, int g, int b, int brightness);
	void setAll(int brightness);
	
	Key &operator()(int row, int col);
};

