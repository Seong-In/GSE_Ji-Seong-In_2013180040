#pragma once
class GameObject
{
	float dx, dy, dz, obj_size, obj_r, obj_g, obj_b, obj_a;
	int x_dir=1, y_dir=1;
public:
	GameObject(float x, float y, float z, float size, float r, float g, float b, float a);
	~GameObject();

	float PosX();
	float PosY();
	float PosZ();
	float PosSize();
	float PosR();
	float PosG();
	float PosB();
	float PosA();

	void MouseX(float x);
	void MouseY(float y);
	void MouseZ(float z);

	void Update();

};

