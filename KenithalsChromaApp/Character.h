#pragma once
#include "ColorEffect.h"
#include <string>
#include <fstream>
#include <iostream>

class Character : public ColorEffect
{
private:
	std::string path;

	void setColor(int _r, int _g, int _b);
public:
	Character();
	~Character();

	void setPath(std::string newPath);
	std::string getPath();
	void iterate();
};

