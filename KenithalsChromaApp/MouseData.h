#include "ChromaSDKImpl.h"
#include "Key.h"

#pragma once
class MouseData
{
private:
	Key keySet[ChromaSDK::Mouse::MAX_ROW][ChromaSDK::Mouse::MAX_COLUMN];
public:
	MouseData();
	~MouseData();

	void setAll(CChromaSDKImpl::Effects newEffect);
	void setAll(CChromaSDKImpl::Effects newEffect, int r, int g, int b);
	void setAll(CChromaSDKImpl::Effects newEffect, int brightness);
	void setAll(CChromaSDKImpl::Effects newEffect, int r, int g, int b, int brightness);
	void setAll(int r, int g, int b);
	void setAll(int r, int g, int b, int brightness);
	void setAll(int brightness);

	Key &operator()(int row, int col);
};

