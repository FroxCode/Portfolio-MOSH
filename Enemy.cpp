//Created by Cmag, Dsin
#include "Enemy.h"



Enemy::Enemy(){}
Enemy::~Enemy(){}

Enemy::Enemy(string const &texture, string const &deathSnd, vector<shared_ptr<Vector2f>> nodes) :
animatedSprite(sf::seconds(0.2f), true, false)
{
	startPoint = Vector2f(nodes.at(0)->x -96, nodes.at(0)->y); //set the start node
	endPoint = *nodes.at(0); //set the first end point
	m_nodeIndex = 0;//what node the enemy is on
	animatedSprite.setOrigin(32, 32); //set origin of sprite
	m_position = startPoint; //set the start position
	bounds = IntRect(Vector2i(m_position), Vector2i(64, 64));
	for (int i = 0; i < nodes.size(); i++)
	{
		m_nodes.push_back(Vector2f(nodes.at(i)->x,nodes.at(i)->y)); //read in the path for the enemy to walk
	}
	if (!m_texture.loadFromFile(texture))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	deathSound.reCreate(deathSnd, 60); //set sound for dying
	walkingAnimation.setSpriteSheet(m_texture);					//Frames for animating
	walkingAnimation.addFrame(sf::IntRect(0, 0, 64, 64));
	walkingAnimation.addFrame(sf::IntRect(64, 0, 64, 64));
	walkingAnimation.addFrame(sf::IntRect(128, 0, 64, 64));
	walkingAnimation.addFrame(sf::IntRect(192, 0, 64, 64));
	currentAnimation = &walkingAnimation;
	
	distance = sqrt(((endPoint.x - startPoint.x) * (endPoint.x - startPoint.x)) + ((endPoint.y - startPoint.y) * (endPoint.y - startPoint.y))); //get distance to first point
	direction = Vector2f((endPoint.x - startPoint.x) / distance, (endPoint.y - startPoint.y) / distance);//get direction vector to first point
}
void Enemy::animate()
{
	animatedSprite.setPosition(sf::Vector2f(m_position.x, m_position.y));
	m_time = m_clock.restart();
	animatedSprite.play(*currentAnimation); //plays animation of the guy walking
	animatedSprite.move(Vector2f(1, 0) * m_time.asSeconds());
	animatedSprite.update(m_time);
	
}
void Enemy::render(RenderWindow &window)
{
	if (m_isAlive)
	{
		animate();
		window.draw(animatedSprite);
	}
}
void Enemy::update()
{
	
	switch (state)
	{
	case Enemy::Idle:
		break;
	case Enemy::Walking:
		if (slowed)
		{ //if he's slowed, start a timer
			slowTimer++;
			if (slowTimer >= 180)
			{ //when the timer hits 3 seconds, speed him back up
				slowed = false;
				m_velocity *= 2;
				slowTimer = 0;
			}
		}
		if (health <= 0)
		{ //dead
			state = Death;
			deathSound.playSingle();
		}
		if ( std::abs(m_position.x - endPoint.x) < 2 && std::abs(m_position.y - endPoint.y) < 2)
		{ //if the enemy hits the endpoint
			m_nodeIndex++; //increase the node index
			if (m_nodeIndex >= m_nodes.size())
			{
				state = State::Attacking; //attack if at the end node
				break;
			}
			 
			//reset pathing
			startPoint = endPoint;
			endPoint = m_nodes.at(m_nodeIndex);
			m_position = startPoint;
			distance = sqrt(((endPoint.x - startPoint.x) * (endPoint.x - startPoint.x)) + ((endPoint.y - startPoint.y) * (endPoint.y - startPoint.y)));
			direction = Vector2f((endPoint.x - startPoint.x) / distance, (endPoint.y - startPoint.y) / distance);

		}
		else
		{
			m_position.x += direction.x * m_velocity * FPS; //move towards target node
			m_position.y += direction.y * m_velocity * FPS;
		}
		break;
	case Enemy::Attacking:

		break;
	case Enemy::Death:
		m_isAlive = false; 
		m_position = Vector2f(-100, -100);
		break;
	default:
		break;
	}
	bounds = IntRect(Vector2i(m_position.x - 32, m_position.y - 32), Vector2i(64, 64)); //set bound rectangle
}
void Enemy::slow()
{
	slowed = true;
	m_velocity /= 2;
}
