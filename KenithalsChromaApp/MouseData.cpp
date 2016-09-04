#include "stdafx.h"
#include "MouseData.h"


MouseData::MouseData()
{
}


MouseData::~MouseData()
{
}

void MouseData::setAll(CChromaSDKImpl::Effects newEffect)
{
	for (int i = 0; i < ChromaSDK::Keyboard::MAX_ROW; i++)
		for (int j = 0; j < ChromaSDK::Keyboard::MAX_COLUMN; j++)
			keySet[i][j].setEffect(newEffect);
}

void MouseData::setAll(CChromaSDKImpl::Effects newEffect, int r, int g, int b)
{
	for (int i = 0; i < ChromaSDK::Keyboard::MAX_ROW; i++)
		for (int j = 0; j < ChromaSDK::Keyboard::MAX_COLUMN; j++)
			keySet[i][j].setEffect(newEffect, r, g, b);
}

void MouseData::setAll(CChromaSDKImpl::Effects newEffect, int brightness)
{
	for (int i = 0; i < ChromaSDK::Keyboard::MAX_ROW; i++)
		for (int j = 0; j < ChromaSDK::Keyboard::MAX_COLUMN; j++)
			keySet[i][j].setEffect(newEffect, brightness);
}

void MouseData::setAll(CChromaSDKImpl::Effects newEffect, int r, int g, int b, int brightness)
{
	for (int i = 0; i < ChromaSDK::Keyboard::MAX_ROW; i++)
		for (int j = 0; j < ChromaSDK::Keyboard::MAX_COLUMN; j++)
			keySet[i][j].setEffect(newEffect, r, g, b, brightness);
}

void MouseData::setAll(int r, int g, int b)
{
	for (int i = 0; i < ChromaSDK::Keyboard::MAX_ROW; i++)
		for (int j = 0; j < ChromaSDK::Keyboard::MAX_COLUMN; j++)
			keySet[i][j].setColor(r, g, b);
}

void MouseData::setAll(int r, int g, int b, int brightness)
{
	for (int i = 0; i < ChromaSDK::Keyboard::MAX_ROW; i++)
		for (int j = 0; j < ChromaSDK::Keyboard::MAX_COLUMN; j++)
			keySet[i][j].setColor(r, g, b, brightness);
}

void MouseData::setAll(int brightness)
{
	for (int i = 0; i < ChromaSDK::Keyboard::MAX_ROW; i++)
		for (int j = 0; j < ChromaSDK::Keyboard::MAX_COLUMN; j++)
			keySet[i][j].setBrightness(brightness);
}

Key &MouseData::operator()(int row, int col)
{
	return keySet[row][col];
}