#include "stdafx.h"
#include "KeyboardData.h"


KeyboardData::KeyboardData()
{
}

KeyboardData::~KeyboardData()
{
}

void KeyboardData::setAll(CChromaSDKImpl::Effects newEffect)
{
	for (int i = 0; i < ChromaSDK::Keyboard::MAX_ROW; i++)
		for (int j = 0; j < ChromaSDK::Keyboard::MAX_COLUMN; j++)
			keySet[i][j].setEffect(newEffect);
}

void KeyboardData::setAll(CChromaSDKImpl::Effects newEffect, int r, int g, int b)
{
	for (int i = 0; i < ChromaSDK::Keyboard::MAX_ROW; i++)
		for (int j = 0; j < ChromaSDK::Keyboard::MAX_COLUMN; j++)
			keySet[i][j].setEffect(newEffect, r, g, b);
}

void KeyboardData::setAll(CChromaSDKImpl::Effects newEffect, int brightness)
{
	for (int i = 0; i < ChromaSDK::Keyboard::MAX_ROW; i++)
		for (int j = 0; j < ChromaSDK::Keyboard::MAX_COLUMN; j++)
			keySet[i][j].setEffect(newEffect, brightness);
}

void KeyboardData::setAll(CChromaSDKImpl::Effects newEffect, int r, int g, int b, int brightness)
{
	for (int i = 0; i < ChromaSDK::Keyboard::MAX_ROW; i++)
		for (int j = 0; j < ChromaSDK::Keyboard::MAX_COLUMN; j++)
			keySet[i][j].setEffect(newEffect, r, g, b, brightness);
}

void KeyboardData::setAll(int r, int g, int b)
{
	for (int i = 0; i < ChromaSDK::Keyboard::MAX_ROW; i++)
		for (int j = 0; j < ChromaSDK::Keyboard::MAX_COLUMN; j++)
			keySet[i][j].setColor(r, g, b);
}

void KeyboardData::setAll(int r, int g, int b, int brightness)
{
	for (int i = 0; i < ChromaSDK::Keyboard::MAX_ROW; i++)
		for (int j = 0; j < ChromaSDK::Keyboard::MAX_COLUMN; j++)
			keySet[i][j].setColor(r, g, b, brightness);
}

void KeyboardData::setAll(int brightness)
{
	for (int i = 0; i < ChromaSDK::Keyboard::MAX_ROW; i++)
		for (int j = 0; j < ChromaSDK::Keyboard::MAX_COLUMN; j++)
			keySet[i][j].setBrightness(brightness);
}

Key &KeyboardData::operator()(int row, int col)
{
	return keySet[row][col];
}
