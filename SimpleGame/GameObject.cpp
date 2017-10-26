#include "stdafx.h"
#include "GameObject.h"
#include <time.h>
#include <stdlib.h>
#define MAXCOUNT 20
bool check=true;
GameObject::GameObject(float x, float y, float z, float size, float r, float g, float b, float a)
{
	
	dx = x;
	dy = y;
	dz = z;
	obj_size = size;
	obj_r = r;
	obj_g = g;
	obj_b = b;
	obj_a = a;
}


GameObject::~GameObject()
{
}

float GameObject::PosX()
{
	return dx;
}
float GameObject::PosY()
{
	return dy;
}
float GameObject::PosZ()
{
	return dz;
}
float GameObject::PosSize()
{
	return obj_size;
}
float GameObject::PosR()
{
	return obj_r;
}
float GameObject::PosG()
{
	return obj_g;
}
float GameObject::PosB()
{
	return obj_b;
}
float GameObject::PosA()
{
	return obj_a;
}

void GameObject::MouseX(float x)
{
	dx = x;
}
void GameObject::MouseY(float y)
{
	dx = y;
}
void GameObject::MouseZ(float z)
{
	dx = z;
}

void GameObject::Update(float elapseTime)
{
	
	float elapseTimeInSecond = elapseTime / 1000.f;
	if (dx<500)
	{
		dx =dx+ x_dir*elapseTimeInSecond;
		
	}
	if(dx>=240)
	{ 
		check = false;
	}
	if (check == false)
	{
		dx -= elapseTimeInSecond;
		
	if (dx <= -240)
	{
		check = true;
	}
	
}