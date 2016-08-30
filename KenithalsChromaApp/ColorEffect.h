#pragma once
//Pure virtual class as the base for all effects.

class ColorEffect
{
protected:
	int r, g, b;

public:
	virtual ~ColorEffect();

	virtual int getR();
	virtual void setR(int _r);

	virtual int getG();
	virtual void setG(int _g);

	virtual int getB();
	virtual void setB(int _b);

	virtual void iterate() = 0;
};

