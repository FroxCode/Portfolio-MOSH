//Created by Emre Ozdemir, Dale Sinnott
#include <BaseTower.h>
#include <cmath>
#include <iostream>
BaseTower::BaseTower(){}
BaseTower::~BaseTower(){}

BaseTower::BaseTower(shared_ptr<GameData> &data, int radius) :
Building(Vector2f(data->basePositionX, data->basePositionY), data->baseImage, radius),
healthLabel(data->font, "Health: 2000", Vector2f(1025, 300), 8)
{ //calls the base class, sets its health label
	m_sprite.setOrigin(48, 59); //offset for rotation
	fired.reCreate("assets/baseFire.wav", 50); //reinitialise sound for firing
	for (int i = 0; i < MAX_BULLETS; i++)
	{ //create the base towers bullets
		shared_ptr<Rocket> rocket = make_shared<Rocket>(Vector2f(0, 0), "assets/baseBullet.png");
		rocket->is_alive = false;
		ammunition.push_back(rocket);
	}

}
void BaseTower::setPosition(Vector2f pos){
	//moves tower
	m_sprite.setPosition(Vector2f(pos.x, pos.y));

}
void BaseTower::update()
{ //Works cooldown for firing bullets and updates them
	coolTimer += 0.01;
	if (coolTimer >= cooldown)
	{
		canFire = true;
		coolTimer = 0;
	}
	for (int i = 0; i < ammunition.size(); i++)
	{
		ammunition.at(i)->update();
	}
}
void BaseTower::render(RenderWindow & window)
{//draw the base tower and its health label
	window.draw(m_sprite);
	healthLabel.render(window);
	
}

void BaseTower::fire(Vector2f & target)
{ 
	if (canFire)
	{//check to see if it can fire now
		canFire = false; //start the cooldown
		coolTimer = 0;
		for (int i = 0; i < MAX_BULLETS; i++)
		{ //loop to check for a bullet not in use
			if (!ammunition.at(i)->is_alive)
			{
				ammunition.at(i)->reset(target, m_sprite.getPosition()); //create a new bullet
				shaders->flash(m_sprite.getPosition()); //use shaders to make a flash on the base towers light
				fired.playSingle(); //play the firing sound
				break; //end the loop after finding a bullet
			}
		}
	}
}
void BaseTower::subtractHealth(int damage)
{ //decrement health
	m_health -= damage;
	healthLabel.setString("Health: " + to_string(m_health)); //update label
}
vector<shared_ptr<Rocket>> BaseTower::getBullets()
{ //returns a vector of the bullets that are alive 

	vector<shared_ptr<Rocket>> bullets;
	for (int i = 0; i < ammunition.size(); i++)
	{
		if (ammunition.at(i)->is_alive)
		{
			bullets.push_back(ammunition.at(i));
		}
	}
	return bullets;
}