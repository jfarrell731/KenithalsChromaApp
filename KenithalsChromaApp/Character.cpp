#include "stdafx.h"
#include "Character.h"
#include "ChromaSDKImpl.h"

Character::Character()
{
	r = g = b = 0;
	path = "";
}

Character::~Character()
{
}

void Character::setPath(std::string newPath)
{
	path = newPath;
}

void Character::setColor(int _r, int _g, int _b)
{
	r = _r;
	g = _g;
	b = _b;
}

void Character::iterate()
{
	std::ifstream ifs;
	std::string str;
	ifs.open(path);

	if (ifs)
	{
		while (ifs >> str)
		{
			if (str.compare("[\"Class\"]") == 0)
			{
				ifs >> str >> str;
				break;
			}
		}

		if (str.compare("\"Death") == 0)
		{
			setColor(DEATHKNIGHT);
		}
		else if (str.compare("\"Demon") == 0)
		{
			setColor(DEMONHUNTER);
		}
		else if (str.compare("\"Druid\",") == 0)
		{
			setColor(DRUID);
		}
		else if (str.compare("\"Hunter\",") == 0)
		{
			setColor(HUNTER);
		}
		else if (str.compare("\"Mage\",") == 0)
		{
			setColor(MAGE);
		}
		else if (str.compare("\"Monk\",") == 0)
		{
			setColor(MONK);
		}
		else if (str.compare("\"Paladin\",") == 0)
		{
			setColor(PALADIN);
		}
		else if (str.compare("\"Priest\",") == 0)
		{
			setColor(PRIEST);
		}
		else if (str.compare("\"Rogue\",") == 0)
		{
			setColor(ROGUE);
		}
		else if (str.compare("\"Shaman\",") == 0)
		{
			setColor(SHAMAN);
		}
		else if (str.compare("\"Warlock\",") == 0)
		{
			setColor(WARLOCK);
		}
		else if (str.compare("\"Warrior\",") == 0)
		{
			setColor(WARRIOR);
		}
		else
		{
			setColor(0, 0, 0);
		}
	}

}