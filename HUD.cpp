//created by Connor Maguire
#include "HUD.h"

HUD::HUD(){};
HUD::~HUD(){};

HUD::HUD(shared_ptr<GameData> &data) :
m_tokens(0),
m_credits(0)
{


}
void HUD::subtract(int amount, int type)
{
	if (type == 1)
	{
		m_tokens -= amount;
	}
	else if (type == 2)
	{
		m_credits -= amount;
	}


}
void HUD::add(int amount, int type)
{
	if (type == 1)
	{
		m_tokens += amount;
	}
	else if (type == 2)
	{
		m_credits += amount;
	}
}
