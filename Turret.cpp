//Created by Connor Maguire
#include "Turret.h"
#include <algorithm>
Turret::Turret(){}
Turret::~Turret(){}

Turret::Turret(sf::Vector2f position, string const &texture, int radius) :
Building(position, texture, radius),
m_enemy(nullptr)
{
	fired.reCreate("assets/turretFire.wav", 50);
	m_sprite.setOrigin(48, 59); //offset for rotation

	//load bullets
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		shared_ptr<CannonBall> cannonBall = make_shared<CannonBall>(Vector2f(0, 0), "assets/turretBullet.png");
		cannonBall->is_alive = false;
		ammunition.push_back(cannonBall);
	}

	//load upgrade textures
	if (!upgradeOne.loadFromFile("assets/Towers/turret2.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	if (!upgradeTwo.loadFromFile("assets/Towers/turret3.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
}
void Turret::setPosition(Vector2f pos)
{

	m_sprite.setPosition(Vector2f(pos.x, pos.y -4));
	m_circle.setOrigin(sf::Vector2f(48 + (2 * 96.f) / 2, 48 + (2 * 96.f) / 2));
	m_circle.setPosition(Vector2f(pos.x -48, pos.y-48 ));
}
void Turret::update()
{
	if (m_enemy != nullptr && (m_enemy->state == Enemy::State::Death || !m_circle.getGlobalBounds().contains(m_enemy->m_position)))
	{ //detarget the enemy
		m_enemy = nullptr;
	}
	coolTimer += 0.01;
	if (coolTimer >= cooldown)
	{
		canFire = true;
		coolTimer = 0;
	}
	m_sprite.rotate(1.0f);
	for (int i = 0; i < ammunition.size(); i++)
	{
		ammunition.at(i)->update();
	}
}
void Turret::render(RenderWindow &window)
{
	if (is_Selected){
		window.draw(m_circle);
	}
	window.draw(m_sprite);
}

void Turret::targetEnemy(shared_ptr<Enemy> enemy)
{ 
	if (m_enemy == nullptr){ m_enemy = enemy; } //assign a new target
	setTowerRotationAngle(Vector2f(m_enemy->m_position.x, m_enemy->m_position.y)); //set angle to rotate
	if (rotateTower()) //rotate, if aligned
	{
		if (canFire) //if cooldown done
		{
			fire(m_enemy->m_position); //fire
			fired.playSingle(); //play sound
		}
	}

}
void Turret::upgrade(int num)
{ //upgrade turrets
	if (num == 1)
	{
		level = 2;
		m_sprite.setTexture(upgradeOne);
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			ammunition.at(i)->damage *= 1.75;
		}
	}
	else if (num == 2)
	{
		level = 3;
		m_sprite.setTexture(upgradeTwo);
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			ammunition.at(i)->damage *= 2;
		}
	}
}

void Turret::fire(Vector2f & target)
{ //fire a bullet
	canFire = false;
	coolTimer = 0;
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (!ammunition.at(i)->is_alive)
		{ 
			ammunition.at(i)->reset(target, m_sprite.getPosition());
			break;
		}
	}
}
vector<shared_ptr<Bullet>> Turret::getBullets()
{ //return alive bullets

	vector<shared_ptr<Bullet>> bullets;
	for (int i = 0; i < ammunition.size(); i++)
	{
		if (ammunition.at(i)->is_alive)
		{
			bullets.push_back(ammunition.at(i));
		}
	}
	return bullets;
}