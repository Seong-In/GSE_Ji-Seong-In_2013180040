#include "stdafx.h"
#include "GameObject.h"
#include <math.h>
#include <iostream>
using namespace std;


GameObject::GameObject(float x, float y)
{
	m_x = x;
	m_y = y;
	m_vX = 200.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
	m_vY = 200.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);

	m_size = 10;
	m_color[0] = 1;
	m_color[1] = 1;
	m_color[2] = 1;
	m_color[3] = 1;

	m_life = 100.f;
	m_lifeTime = 100000.f;
}


GameObject::~GameObject()
{

}

void GameObject::Update(float elapsedTime)
{
	float elapsedTimeInSecond = elapsedTime / 1000.f;

	m_x = m_x + m_vX * elapsedTimeInSecond;
	m_y = m_y + m_vY * elapsedTimeInSecond;

	if (m_x > 250)
	{
		m_vX = -m_vX;
	}

	if (m_x < -250)
	{
		m_vX = -m_vX;
	}

	if (m_y > 250)
	{
		m_vY = -m_vY;
	}

	if (m_y < -250)
	{
		m_vY = -m_vY;
	}

	if (m_life > 0.f)
	{
		m_life -= 0.01f;
	}

	if (m_lifeTime > 0.f)
	{
		m_lifeTime -= elapsedTimeInSecond;
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
