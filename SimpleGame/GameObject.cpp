#include "stdafx.h"
#include "GameObject.h"
#include "ScenceMng.h"
#include <math.h>


GameObject::GameObject(float x, float y, int type)
{
	m_x = x;
	m_y = y;

	m_type = type;

	m_lastBullet = 0.f;
	m_lastArrow = 0.f;

	m_parentID = -1;

	if (type ==GameObject_BUILDING_RED)
	{
		m_color[0] = 1;
		m_color[1] = 1;
		m_color[2] = 0;
		m_color[3] = 1;

		m_vX = 0;
		m_vY = 0;
		lev = 0.1f;
		m_size = 80;
		m_life = 500;

		m_lifeTime = 100000.f;


	}
	else if (type == GameObject_CHARACTER)
	{
		m_color[0] = 1;
		m_color[1] = 1;
		m_color[2] = 1;
		m_color[3] = 1;

		m_vX = 300.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_vY = 300.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		lev = 0.2f;
		m_size = 20;
		m_life = 10;

		m_lifeTime = 100000.f;
	}
	else if (type == GameObject_BULLET)
	{
		m_color[0] = 1;
		m_color[1] = 0;
		m_color[2] = 0;
		m_color[3] = 1;

		m_vX = 600.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_vY = 600.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		lev = 0.3f;
		m_size = 2;
		m_life = 20;

		m_lifeTime = 100000.f;
	}
	else if (type == GameObject_ARROW)
	{
		m_color[0] = 0;
		m_color[1] = 1;
		m_color[2] = 0;
		m_color[3] = 1;
		lev = 0.3f;
		m_vX = 100.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_vY = 100.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);

		m_size = 2;
		m_life = 10;

		m_lifeTime = 100000.f;
	}
	else
	{
		std::cout << "Wrong GameObject Type " << type << " \n";
	}
}


GameObject::~GameObject()
{

}

void GameObject::Update(float elapsedTime)
{
	float elapsedTimeInSecond = elapsedTime / 1000.f;

	m_lastBullet += elapsedTimeInSecond;
	m_lastArrow += elapsedTimeInSecond;

	m_x = m_x + m_vX * elapsedTimeInSecond;
	m_y = m_y + m_vY * elapsedTimeInSecond;

	if (m_x > 250)
	{
		if (m_type != GameObject_BULLET || m_type != GameObject_ARROW)
		{
			m_vX = -m_vX;
		}
	}
	if (m_x < -250)
	{
		if (m_type != GameObject_BULLET || m_type != GameObject_ARROW)
		{
			m_vX = -m_vX;
		}
	}

	if (m_y > 400)
	{
		if (m_type != GameObject_BULLET || m_type != GameObject_ARROW)
		{
			m_vY = -m_vY;
		}
	}

	if (m_y < -400)
	{
		if (m_type != GameObject_BULLET || m_type != GameObject_ARROW)
		{
			m_vY = -m_vY;
		}
	}

	if (m_life > 0.f)
	{
		if (m_type !=GameObject_BUILDING_RED)
		{
			//m_life -= 0.5f;
		}
	}

	if (m_lifeTime > 0.f)
	{
		//		m_lifeTime -= elapsedTimeInSecond;
	}
}

float GameObject::GetLife()
{
	return m_life;
}

float GameObject::GetLifeTime()
{
	return m_lifeTime;
}

int GameObject::GetType()
{
	return m_type;
}

void GameObject::SetDamage(float amount)
{
	m_life -= amount;
}
