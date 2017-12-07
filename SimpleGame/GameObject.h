#pragma once
#include <cstdlib>

class GameObject
{
public:
	GameObject(float x, float y, int type);
	~GameObject();

	float GetLife();
	float GetLifeTime();
	int GetType();
	void SetDamage(float amount);

	void Update(float elapsedTime);

	float m_x;
	float m_y;
	float m_vX;
	float m_vY;

	float m_size;
	float m_color[4];

	float m_life;
	float m_lifeTime;
	float lev;
	int m_type;

	float m_lastBullet;
	float m_lastArrow;

	float m_velo;

	float m_ani_x;
	float m_ani_y;

	int m_parentID;
};

