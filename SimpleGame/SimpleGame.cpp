/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include "windows.h"

#include "ScenceMng.h"
#include "GameObject.h"

#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

using namespace std;
ScenceMng *g_ScenceMng = NULL;

DWORD g_prevTime = 0;

bool g_LButtonDown = false;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.f);

	DWORD currTime = timeGetTime();
	DWORD elapsedTime = currTime - g_prevTime;
	g_prevTime = currTime;

	g_ScenceMng->UpdateAllActorGameObjects((float)elapsedTime);
	g_ScenceMng->DrawAllGameObjects();

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

//button
//GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON
//state
//GLUT_UP, GLUT_DOWN
void MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		g_LButtonDown = true;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (g_LButtonDown)
		{
			//clicked
			for (int i = 0; i < 1; i++)
				g_ScenceMng->AddActorGameObject(x - 250, -y + 400, GameObject_CHARACTER);
		}
		g_LButtonDown = false;
	}

	RenderScene();
}

void MotionInput(int x, int y)
{
	if (g_LButtonDown)
	{
		//clicked
		for (int i = 0; i < 1; i++)
		{
			//g_ScenceMng->AddActorGameObject(x - 250, -y + 250, GameObject_CHARACTER);
		}
	}
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 800);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMotionFunc(MotionInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	g_ScenceMng = new ScenceMng(500, 800);
	g_ScenceMng->AddActorGameObject(-150, -300, GameObject_BUILDING_RED);
	g_ScenceMng->AddActorGameObject(0, -300, GameObject_BUILDING_RED);
	g_ScenceMng->AddActorGameObject(150, -300, GameObject_BUILDING_RED);
	g_ScenceMng->AddActorGameObject(-150, 300, GameObject_BUILDING_BLUE);
	g_ScenceMng->AddActorGameObject(0, 300, GameObject_BUILDING_BLUE);
	g_ScenceMng->AddActorGameObject(150, 300, GameObject_BUILDING_BLUE);

	g_prevTime = timeGetTime();

	glutMainLoop();

	delete g_ScenceMng;

	return 0;
}

