#include "stdafx.h"
#include "ScenceMng.h"
#include <iostream>
using namespace std;
ScenceMng::ScenceMng(int width, int height)
{
	// Initialize Renderer
	m_renderer = new Renderer(width, height);

	if (!m_renderer->IsInitialized())
	{
		std::cout << "ScenceMng::Renderer could not be initialized.. \n";
	}

	//m_texCharacter = m_renderer->CreatePngTexture("./Resorce/Teamblue.png");
	m_texBuilding = m_renderer->CreatePngTexture("./Resorce/Teamred.png");
	m_texBuilding_blue = m_renderer->CreatePngTexture("./Resorce/Teamblue.png");

	m_windowWidth = width;
	m_windowHeight = height;

	for (int i = 0; i < MAX_GameObject_COUNT; i++)
	{
		m_actorGameObjects[i] = NULL;
		m_bulletGameObjects[i] = NULL;
		
	}
}

int g_temp = 0;

void ScenceMng::DrawAllGameObjects()
{
		
	for (int i = 0; i < MAX_GameObject_COUNT; i++)
	{
		if (m_actorGameObjects[i] != NULL)
		{
			// Renderer Test
			if (m_actorGameObjects[i]->m_type == GameObject_BUILDING_RED)
			{
				m_renderer->DrawTexturedRect(
					m_actorGameObjects[i]->m_x,
					m_actorGameObjects[i]->m_y,
					0,
					m_actorGameObjects[i]->m_size,
					m_actorGameObjects[i]->m_color[0],
					m_actorGameObjects[i]->m_color[1],
					m_actorGameObjects[i]->m_color[2],
					m_actorGameObjects[i]->m_color[3],
					m_texBuilding,
					m_actorGameObjects[i]->lev
				);
				m_renderer->DrawSolidRectGauge(
					m_actorGameObjects[i]->m_x,
					m_actorGameObjects[i]->m_y,
					0, 10, 2, 0, 0, 1, 1, 1, 0.5);
				
			}
			
			
			/*else if(m_actorGameObjects[i]->m_type == GameObject_CHARACTER)
			{
			m_renderer->DrawTexturedRect(
			m_actorGameObjects[i]->m_x,
			m_actorGameObjects[i]->m_y,
			0,
			m_actorGameObjects[i]->m_size,
			m_actorGameObjects[i]->m_color[0],
			m_actorGameObjects[i]->m_color[1],
			m_actorGameObjects[i]->m_color[2],
			m_actorGameObjects[i]->m_color[3],
			m_texCharacter
			);
			}*/
			else
			{
				m_renderer->DrawSolidRect(
					m_actorGameObjects[i]->m_x,
					m_actorGameObjects[i]->m_y,
					0,
					m_actorGameObjects[i]->m_size,
					m_actorGameObjects[i]->m_color[0],
					m_actorGameObjects[i]->m_color[1],
					m_actorGameObjects[i]->m_color[2],
					m_actorGameObjects[i]->m_color[3],
					m_actorGameObjects[i]->lev
				);
				
			}
			m_renderer->DrawTexturedRect(-150, 300, 0,
				m_actorGameObjects[i]->m_size,
				m_actorGameObjects[i]->m_color[0],
				m_actorGameObjects[i]->m_color[1],
				m_actorGameObjects[i]->m_color[2],
				m_actorGameObjects[i]->m_color[3],
				m_texBuilding_blue,0
			);
			m_renderer->DrawTexturedRect(0, 300, 0,
				m_actorGameObjects[i]->m_size,
				m_actorGameObjects[i]->m_color[0],
				m_actorGameObjects[i]->m_color[1],
				m_actorGameObjects[i]->m_color[2],
				m_actorGameObjects[i]->m_color[3],
				m_texBuilding_blue,0
			);
			m_renderer->DrawTexturedRect(150, 300, 0,
				m_actorGameObjects[i]->m_size,
				m_actorGameObjects[i]->m_color[0],
				m_actorGameObjects[i]->m_color[1],
				m_actorGameObjects[i]->m_color[2],
				m_actorGameObjects[i]->m_color[3],
				m_texBuilding_blue,0
			);
		}
	}
}

ScenceMng::~ScenceMng()
{
}

int ScenceMng::AddActorGameObject(float x, float y, int type)
{
	//Find empty slot
	for (int i = 0; i < MAX_GameObject_COUNT; i++)
	{
		if (m_actorGameObjects[i] == NULL)
		{
			m_actorGameObjects[i] = new GameObject(x, y, type);
			return i;
		}
	}

	//slots are full
	std::cout << "slots are full \n";
	return -1;
}

void ScenceMng::DeleteActorGameObject(int index)
{
	if (m_actorGameObjects[index] != NULL)
	{
		delete m_actorGameObjects[index];
		m_actorGameObjects[index] = NULL;
	}
}

void ScenceMng::UpdateAllActorGameObjects(float elapsedTime)
{
	DoCollisionTest();

	for (int i = 0; i < MAX_GameObject_COUNT; i++)
	{
		if (m_actorGameObjects[i] != NULL)
		{
			if (m_actorGameObjects[i]->GetLife() < 0.0001f || m_actorGameObjects[i]->GetLifeTime() < 0.0001f)
			{
				//kill GameObject
				if (m_actorGameObjects[i]->GetType() == GameObject_CHARACTER)
				{
					//find all arrows and kill them
					for (int j = 0; j < MAX_GameObject_COUNT; j++)
					{
						if (m_actorGameObjects[j] != NULL && m_actorGameObjects[j]->m_type == GameObject_ARROW && m_actorGameObjects[j]->m_parentID == i)
						{
							delete m_actorGameObjects[j];
							m_actorGameObjects[j] = NULL;
						}
					}
				}
				delete m_actorGameObjects[i];
				m_actorGameObjects[i] = NULL;
			}
			else
			{
				m_actorGameObjects[i]->Update(elapsedTime);
				if (m_actorGameObjects[i]->GetType() == GameObject_BUILDING_RED)
				{
					//fire bullet
					if (m_actorGameObjects[i]->m_lastBullet > 3)
					{
						int bulletID = AddActorGameObject(
							m_actorGameObjects[i]->m_x,
							m_actorGameObjects[i]->m_y,
							GameObject_BULLET);
						m_actorGameObjects[i]->m_lastBullet = 0.f;
						if (bulletID >= 0)
						{
							m_actorGameObjects[bulletID]->m_parentID = i;
						}
					}
				}
				if (m_actorGameObjects[i]->GetType() == GameObject_CHARACTER)
				{
					//fire arrow
					if (m_actorGameObjects[i]->m_lastArrow > 0.5f)
					{
						int arrowID = AddActorGameObject(
							m_actorGameObjects[i]->m_x,
							m_actorGameObjects[i]->m_y,
							GameObject_ARROW);
						m_actorGameObjects[i]->m_lastArrow = 0.f;
						if (arrowID >= 0)
						{
							m_actorGameObjects[arrowID]->m_parentID = i;
						}
					}
				}
			}
		}
		if (m_bulletGameObjects[i] != NULL)
		{
			m_bulletGameObjects[i]->Update(elapsedTime);
		}
	}
}

GameObject* ScenceMng::GetActorGameObject(int index)
{
	return m_actorGameObjects[index];
}

int ScenceMng::GetMaxGameObjectCount()
{
	return MAX_GameObject_COUNT;
}

void ScenceMng::DoCollisionTest()
{
	int collisionCount = 0;

	for (int i = 0; i < MAX_GameObject_COUNT; i++)
	{
		collisionCount = 0;
		if (m_actorGameObjects[i] != NULL)
		{
			for (int j = 0; j < MAX_GameObject_COUNT; j++)
			{
				if (i == j)
					continue;

				if (m_actorGameObjects[j] != NULL && m_actorGameObjects[i] != NULL)
				{
					float minX, minY;
					float maxX, maxY;

					float minX1, minY1;
					float maxX1, maxY1;

					minX = m_actorGameObjects[i]->m_x - m_actorGameObjects[i]->m_size / 2.f;
					minY = m_actorGameObjects[i]->m_y - m_actorGameObjects[i]->m_size / 2.f;
					maxX = m_actorGameObjects[i]->m_x + m_actorGameObjects[i]->m_size / 2.f;
					maxY = m_actorGameObjects[i]->m_y + m_actorGameObjects[i]->m_size / 2.f;
					minX1 = m_actorGameObjects[j]->m_x - m_actorGameObjects[j]->m_size / 2.f;
					minY1 = m_actorGameObjects[j]->m_y - m_actorGameObjects[j]->m_size / 2.f;
					maxX1 = m_actorGameObjects[j]->m_x + m_actorGameObjects[j]->m_size / 2.f;
					maxY1 = m_actorGameObjects[j]->m_y + m_actorGameObjects[j]->m_size / 2.f;
					if (BoxBoxCollisionTest(minX, minY, maxX, maxY, minX1, minY1, maxX1, maxY1))
					{
						if (
							(m_actorGameObjects[i]->GetType() == GameObject_BUILDING_RED)
							&&
							(m_actorGameObjects[j]->GetType() == GameObject_CHARACTER)
							)
						{
							m_actorGameObjects[i]->SetDamage(m_actorGameObjects[j]->GetLife());
							m_actorGameObjects[j]->m_life = 0.f;
							collisionCount++;
						}
						else if (
							(m_actorGameObjects[j]->GetType() == GameObject_BUILDING_RED)
							&&
							(m_actorGameObjects[i]->GetType() == GameObject_CHARACTER)
							)
						{
							m_actorGameObjects[j]->SetDamage(m_actorGameObjects[i]->GetLife());
							m_actorGameObjects[i]->m_life = 0.f;
							collisionCount++;
						}
						else if (
							(m_actorGameObjects[i]->GetType() == GameObject_CHARACTER)
							&&
							(m_actorGameObjects[j]->GetType() == GameObject_BULLET)
							)
						{
							m_actorGameObjects[i]->SetDamage(m_actorGameObjects[j]->GetLife());
							m_actorGameObjects[j]->m_life = 0.f;
						}
						else if (
							(m_actorGameObjects[j]->GetType() == GameObject_CHARACTER)
							&&
							(m_actorGameObjects[i]->GetType() == GameObject_BULLET)
							)
						{
							m_actorGameObjects[j]->SetDamage(m_actorGameObjects[i]->GetLife());
							m_actorGameObjects[i]->m_life = 0.f;
						}
						else if (
							(m_actorGameObjects[i]->GetType() == GameObject_CHARACTER)
							&&
							(m_actorGameObjects[j]->GetType() == GameObject_ARROW)
							&&
							(m_actorGameObjects[j]->m_parentID != i)
							)
						{
							m_actorGameObjects[i]->SetDamage(m_actorGameObjects[j]->GetLife());
							m_actorGameObjects[j]->m_life = 0.f;
						}
						else if (
							(m_actorGameObjects[j]->GetType() == GameObject_CHARACTER)
							&&
							(m_actorGameObjects[i]->GetType() == GameObject_ARROW)
							&&
							(m_actorGameObjects[i]->m_parentID != j)
							)
						{
							m_actorGameObjects[j]->SetDamage(m_actorGameObjects[i]->GetLife());
							m_actorGameObjects[i]->m_life = 0.f;
						}
						else if (
							(m_actorGameObjects[i]->GetType() == GameObject_BUILDING_RED)
							&&
							(m_actorGameObjects[j]->GetType() == GameObject_ARROW)
							)
						{
							m_actorGameObjects[i]->SetDamage(m_actorGameObjects[j]->GetLife());
							m_actorGameObjects[j]->m_life = 0.f;
						}
						else if (
							(m_actorGameObjects[j]->GetType() == GameObject_BUILDING_RED)
							&&
							(m_actorGameObjects[i]->GetType() == GameObject_ARROW)
							)
						{
							m_actorGameObjects[j]->SetDamage(m_actorGameObjects[i]->GetLife());
							m_actorGameObjects[i]->m_life = 0.f;
						}
					}
				}
			}
			if (collisionCount > 0)
			{
				if (m_actorGameObjects[i] != NULL && m_actorGameObjects[i]->GetType() == GameObject_BUILDING_RED)
				{
					m_actorGameObjects[i]->m_color[0] = 1;
					m_actorGameObjects[i]->m_color[1] = 0;
					m_actorGameObjects[i]->m_color[2] = 0;
					m_actorGameObjects[i]->m_color[3] = 1;
				}
			}
			else
			{
				if (m_actorGameObjects[i] != NULL && m_actorGameObjects[i]->GetType() == GameObject_BUILDING_RED)
				{
					m_actorGameObjects[i]->m_color[0] = 1;
					m_actorGameObjects[i]->m_color[1] = 1;
					m_actorGameObjects[i]->m_color[2] = 0;
					m_actorGameObjects[i]->m_color[3] = 1;
				}
			}
		}
	}
}

bool ScenceMng::BoxBoxCollisionTest(float minX, float minY, float maxX, float maxY, float minX1, float minY1, float maxX1, float maxY1)
{
	if (minX > maxX1)
		return false;
	if (maxX < minX1)
		return false;

	if (minY > maxY1)
		return false;
	if (maxY < minY1)
		return false;

	return true;
}
