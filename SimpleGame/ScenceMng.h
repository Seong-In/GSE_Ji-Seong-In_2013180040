#pragma once
#include <cstdlib>
#include <iostream>

#include "Renderer.h"
#include "GameObject.h"

#define MAX_OBJECT_COUNT 20
#define Object_Player 1
#define Object_Bulding 2
#define Object_Bullet 3
#define Object_Arrow 4
class ScenceMng
{
public:
	ScenceMng(int width, int height);
	~ScenceMng();

	int AddActorObject(float x, float y,float type);
	void DeleteActorObject(int index);
	void UpdateAllActorObjects(float elapsedTime);
	GameObject* GetActorObject(int index);
	int GetMaxObjectCount();
	void DrawAllObjects();

private:
	bool BoxBoxCollisionTest(float minX, float minY, float maxX, float maxY, float minX1, float minY1, float maxX1, float maxY1);
	void DoCollisionTest();
	GameObject *m_actorObjects[MAX_OBJECT_COUNT];
	GameObject *m_bulletObjects[MAX_OBJECT_COUNT];

	Renderer *m_renderer;

	int m_windowWidth;
	int m_windowHeight;
};

