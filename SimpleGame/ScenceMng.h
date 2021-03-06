#pragma once
#include <cstdlib>
#include <iostream>

#include "Renderer.h"
#include "GameObject.h"
#include "Sound.h"

#define MAX_GameObject_COUNT 1000

#define GameObject_CHARACTER 0
#define GameObject_BUILDING_RED 1
#define GameObject_BULLET_RED 2
#define GameObject_BULLET_BLUE 3
#define GameObject_ARROW 4
#define GameObject_BUILDING_BLUE 5
#define GameObject_WEATHER 6
class ScenceMng
{
public:
	ScenceMng(int width, int height);
	~ScenceMng();

	int AddActorGameObject(float x, float y, int type);
	void DeleteActorGameObject(int index);
	void UpdateAllActorGameObjects(float elapsedTime);
	GameObject* GetActorGameObject(int index);
	int GetMaxGameObjectCount();
	void DrawAllGameObjects();

private:
	bool BoxBoxCollisionTest(float minX, float minY, float maxX, float maxY, float minX1, float minY1, float maxX1, float maxY1);
	void DoCollisionTest();
	GameObject *m_actorGameObjects[MAX_GameObject_COUNT];
	GameObject *m_bulletGameObjects[MAX_GameObject_COUNT];

	Renderer *m_renderer;

	int m_windowWidth;
	int m_windowHeight;

	GLuint m_texCharacter = 0;
	GLuint m_texBuilding = 0;
	GLuint m_texBuilding_blue = 0;
	GLuint m_star = 0;
	GLuint m_background = 0;
	GLuint m_character = 0;
	GLuint m_particle = 0;
	Sound* m_sound;
	int	soundBG;
	int destroy;
	

};

