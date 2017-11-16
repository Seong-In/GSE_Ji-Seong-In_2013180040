#pragma once
#include <cstdlib>

class GameObject
{
public:
	GameObject(float x, float y);
	~GameObject();

	float GetLife();
	float GetLifeTime();

	void Update(float elapsedTime);

	float m_x;
	float m_y;
	float m_vX;
	float m_vY;
	


	float m_size;
	float m_color[4];


	float m_life;
	float m_lifeTime;
};

