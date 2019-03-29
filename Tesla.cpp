//Created by Connor Maguire
#include  "Tesla.h"

Tesla::Tesla(){}
Tesla::~Tesla(){}

Tesla::Tesla(sf::Vector2f position, string const &texture, int radius) :
Turret(position, texture, radius)
{
	fired.reCreate("assets/teslaFired.wav", 50);
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		shared_ptr<ShockBlast> shockBlaster = make_shared<ShockBlast>(Vector2f(0, 0), "assets/teslaBullet.png");
		shockBlaster->is_alive = false;
		ammunition.push_back(shockBlaster);
	}
	if (!upgradeOne.loadFromFile("assets/Towers/tesla2.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	if (!upgradeTwo.loadFromFile("assets/Towers/tesla3.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
}
void Tesla::setPosition(Vector2f pos){

	m_sprite.setPosition(Vector2f(pos.x, pos.y - 4));
	m_circle.setOrigin((1 * 96.f) / 2, (1 * 96.f) / 2);
	m_circle.setPosition(Vector2f(pos.x - 48, pos.y - 48));

}
void Tesla::update()
{
	if (m_enemy != nullptr && (m_enemy->state == Enemy::State::Death || !m_circle.getGlobalBounds().contains(m_enemy->m_position) || m_enemy->slowed))
	{
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
void Tesla::upgrade(int num)
{
	if (num == 1)
	{
		level = 2;
		m_sprite.setTexture(upgradeOne);
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			ammunition.at(i)->damage *= 1.5;
			slow += 1;
		}
	}
	else if (num == 2)
	{
		level = 3;
		m_sprite.setTexture(upgradeTwo);
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			ammunition.at(i)->damage *= 1.5;
			slow += 1;
		}
	}
}
void Tesla::targetEnemy(shared_ptr<Enemy> enemy)
{
	if (m_enemy == nullptr || m_enemy->slowed){ m_enemy = enemy; }
	setTowerRotationAngle(Vector2f(m_enemy->m_position.x, m_enemy->m_position.y));
	if (rotateTower())
	{
		if (canFire)
		{
			fire(m_enemy->m_position);
			fired.playSingle();
		}
	}

}
void Tesla::fire(Vector2f & target)
{
	canFire = false;
	coolTimer = 0;
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (!ammunition.at(i)->is_alive)
		{
			
			ammunition.at(i)->reset(target, m_sprite.getPosition());
			ammunition.at(i)->m_sprite.rotate(m_sprite.getRotation());
			break;
		}
	}
}
vector<shared_ptr<Bullet>> Tesla::getBullets()
{

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