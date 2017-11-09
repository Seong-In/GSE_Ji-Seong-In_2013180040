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

ScenceMng *g_ScenceMng = NULL;

DWORD g_prevTime = 0;

bool g_LButtonDown = false;

void RenderScene(void)
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	DWORD currTime = timeGetTime();
	DWORD elapsedTime = currTime - g_prevTime;
	g_prevTime = currTime;

	g_ScenceMng->UpdateAllActorObjects((float)elapsedTime);
	g_ScenceMng->DrawAllObjects();
	
	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}


void MouseInput(int button, int state, int x, int y)
{
	

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		for (int i = 0; i < 1; i++) {
			g_ScenceMng->AddActorObject(x - 250, -y + 250, Object_Player);
		}

	}

	RenderScene();
}

void MotionInput(int x, int y)
{
	//마우스 드래그
	if (g_LButtonDown)
	{
		//clicked
		for (int i = 0; i < 100; i++)
		{
			//g_ScenceMng->AddActorObject(x - 250, -y + 250);
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
	glutInitWindowSize(500, 500);
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

	g_ScenceMng = new ScenceMng(500, 500);
	/*for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		float x = 250.f * 2.f * ((float)std::rand() / (float)RAND_MAX - 0.5f);
		float y = 250.f * 2.f * ((float)std::rand() / (float)RAND_MAX - 0.5f);

		g_ScenceMng->AddActorObject(x, y);
	}*/
	
	g_prevTime = timeGetTime();

	glutMainLoop();

	delete g_ScenceMng;
	
	return 0;
}

