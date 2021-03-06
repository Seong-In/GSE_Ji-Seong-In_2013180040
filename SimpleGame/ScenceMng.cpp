#include "stdafx.h"
#include "ScenceMng.h"
#include <iostream>
#include "Sound.h"
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
	m_star = m_renderer->CreatePngTexture("./Resorce/star.png");
	m_background = m_renderer->CreatePngTexture("./Resorce/space.png");
	m_character= m_renderer->CreatePngTexture("./Resorce/effect.png");
	m_particle = m_renderer->CreatePngTexture("./Resorce/test.png");
	m_windowWidth = width;
	m_windowHeight = height;

	m_sound = new Sound();

	soundBG = m_sound->CreateSound("./Dependencies/SoundSamples/likeafool.mp3");
	destroy = m_sound->CreateSound("./Dependencies/SoundSamples/destroy.mp3");

	m_sound->PlaySound(soundBG, true, 0.2f);

	
	for (int i = 0; i < MAX_GameObject_COUNT; i++)
	{
		m_actorGameObjects[i] = NULL;
		m_bulletGameObjects[i] = NULL;
		
	}
}

int g_temp = 0;

void ScenceMng::DrawAllGameObjects()
{
	m_renderer->DrawTexturedRect(0, 0, 0, 800, 1, 1, 1, 1,m_background,0.9);
	
	
	
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
					m_actorGameObjects[i]->m_y - 60,
					0, 80, 10, 1, 0, 0, 1, m_actorGameObjects[i]->m_gauge, 0.5);

				m_renderer->DrawTextW(-40, -200, GLUT_BITMAP_HELVETICA_18, 1, 0, 0, "Red Team");

			}
			
			else if (m_actorGameObjects[i]->m_type == GameObject_BUILDING_BLUE)
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
					m_texBuilding_blue,
					m_actorGameObjects[i]->lev
				);
				m_renderer->DrawSolidRectGauge(
					m_actorGameObjects[i]->m_x,
					m_actorGameObjects[i]->m_y - 60,
					0, 80, 10, 0, 0, 1, 1, m_actorGameObjects[i]->m_gauge, 0.5);
				m_renderer->DrawTextW(-40, 200, GLUT_BITMAP_HELVETICA_18, 0, 0, 1, "Blue Team");
				

			}


			else if (m_actorGameObjects[i]->m_type == GameObject_CHARACTER)
			{
				
				m_renderer->DrawTexturedRectSeq(m_actorGameObjects[i]->m_x,
					m_actorGameObjects[i]->m_y,
					0,
					m_actorGameObjects[i]->m_size,
					m_actorGameObjects[i]->m_color[0],
					m_actorGameObjects[i]->m_color[1],
					m_actorGameObjects[i]->m_color[2],
					m_actorGameObjects[i]->m_color[3], m_character, m_actorGameObjects[i]->m_ani_x,
					m_actorGameObjects[i]->m_ani_y, 5, 6, m_actorGameObjects[i]->lev);
			}
			else if (m_actorGameObjects[i]->m_type == GameObject_BULLET_RED)
			{
				m_renderer->DrawParticle(
					m_actorGameObjects[i]->m_x,
					m_actorGameObjects[i]->m_y,
					0,
					m_actorGameObjects[i]->m_size,
					m_actorGameObjects[i]->m_color[0],
					m_actorGameObjects[i]->m_color[1],
					m_actorGameObjects[i]->m_color[2],
					m_actorGameObjects[i]->m_color[3], 0, -0.5, m_particle, m_actorGameObjects[i]->m_time, m_actorGameObjects[i]->lev);
				
				
			}
			else if (m_actorGameObjects[i]->m_type == GameObject_BULLET_BLUE)
			{
				m_renderer->DrawParticle(
					m_actorGameObjects[i]->m_x,
					m_actorGameObjects[i]->m_y,
					0,
					m_actorGameObjects[i]->m_size,
					m_actorGameObjects[i]->m_color[0],
					m_actorGameObjects[i]->m_color[1],
					m_actorGameObjects[i]->m_color[2],
					m_actorGameObjects[i]->m_color[3], 0, 0.5, m_particle, m_actorGameObjects[i]->m_time, m_actorGameObjects[i]->lev);
				m_renderer->DrawParticleClimate(0, 0, 0, 3, 1, 1, 1, 1, -0.5, -0.5, m_star, m_actorGameObjects[i]->m_time, 0.1);
				

			}
			else if (m_actorGameObjects[i]->m_type == GameObject_WEATHER)
			{
				m_renderer->DrawParticleClimate(0, 0, 0,3, 1, 1, 1, 1, -0.5, -0.5, m_star, m_actorGameObjects[i]->m_weather, 0.1);
			}
		
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
				//아군 총알 생성 (빨간색) 5초에 1번
				if (m_actorGameObjects[i]->GetType() == GameObject_BUILDING_RED)
				{
					
					if (m_actorGameObjects[i]->m_lastBullet > 5)
					{
						int bulletID = AddActorGameObject(
							m_actorGameObjects[i]->m_x,
							m_actorGameObjects[i]->m_y,
							GameObject_BULLET_RED);
						m_actorGameObjects[i]->m_lastBullet = 0.f;
						if (bulletID >= 0)
						{
							m_actorGameObjects[bulletID]->m_parentID = i;
						}
					}
				}
				//적 총알 생성 (파란색) 2초에 한번
				if (m_actorGameObjects[i]->GetType() == GameObject_BUILDING_BLUE)
				{
					
					if (m_actorGameObjects[i]->m_lastBullet > 2)
					{
						int bulletID = AddActorGameObject(
							m_actorGameObjects[i]->m_x,
							m_actorGameObjects[i]->m_y,
							GameObject_BULLET_BLUE);
						m_actorGameObjects[i]->m_lastBullet = 0.f;
						if (bulletID >= 0)
						{
							m_actorGameObjects[bulletID]->m_parentID = i;
						}
					}
				}
				if (m_actorGameObjects[i]->GetType() == GameObject_CHARACTER)
				{
					////fire arrow
					//if (m_actorGameObjects[i]->m_lastArrow > 0.5f)
					//{
					//	int arrowID = AddActorGameObject(
					//		m_actorGameObjects[i]->m_x,
					//		m_actorGameObjects[i]->m_y,
					//		GameObject_ARROW);
					//	m_actorGameObjects[i]->m_lastArrow = 0.f;
					//	if (arrowID >= 0)
					//	{
					//		m_actorGameObjects[arrowID]->m_parentID = i;
					//	}
					//}
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
							(m_actorGameObjects[i]->GetType() ==  GameObject_BUILDING_BLUE)
							&&
							(m_actorGameObjects[j]->GetType() == GameObject_CHARACTER)
							)
						{
							m_actorGameObjects[i]->SetDamage(m_actorGameObjects[j]->GetLife());
							m_actorGameObjects[j]->m_life = 0.f;
							collisionCount++;
						}
						else if (
							(m_actorGameObjects[j]->GetType() ==  GameObject_BUILDING_BLUE)
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
							(m_actorGameObjects[j]->GetType() == GameObject_BULLET_BLUE)
							)
						{
							m_actorGameObjects[i]->SetDamage(m_actorGameObjects[j]->GetLife());
							m_actorGameObjects[j]->m_life = 0.f;
						}
						else if (
							(m_actorGameObjects[j]->GetType() == GameObject_CHARACTER)
							&&
							(m_actorGameObjects[i]->GetType() == GameObject_BULLET_BLUE)
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
							(m_actorGameObjects[i]->GetType() == GameObject_BUILDING_RED || GameObject_BUILDING_BLUE)
							&&
							(m_actorGameObjects[j]->GetType() == GameObject_ARROW)
							)
						{
							m_actorGameObjects[i]->SetDamage(m_actorGameObjects[j]->GetLife());
							m_actorGameObjects[j]->m_life = 0.f;
						}
						else if (
							(m_actorGameObjects[j]->GetType() == GameObject_BUILDING_RED|| GameObject_BUILDING_BLUE)
							&&
							(m_actorGameObjects[i]->GetType() == GameObject_ARROW)
							)
						{
							m_actorGameObjects[j]->SetDamage(m_actorGameObjects[i]->GetLife());
							m_actorGameObjects[i]->m_life = 0.f;
						}

						
						else if (
							(m_actorGameObjects[i]->GetType() == GameObject_BUILDING_RED )
							&&
							(m_actorGameObjects[j]->GetType() == GameObject_BULLET_BLUE)
							)
						{
							m_actorGameObjects[i]->SetDamage(m_actorGameObjects[j]->GetLife());
							m_actorGameObjects[j]->m_life = 0.f;
							collisionCount++;
						}
						else if (
							(m_actorGameObjects[j]->GetType() == GameObject_BUILDING_RED )
							&&
							(m_actorGameObjects[i]->GetType() == GameObject_BULLET_BLUE)
							)
						{
							m_actorGameObjects[j]->SetDamage(m_actorGameObjects[i]->GetLife());
							m_actorGameObjects[i]->m_life = 0.f;
							collisionCount++;
						}

						else if (
							(m_actorGameObjects[i]->GetType() == GameObject_BUILDING_BLUE)
							&&
							(m_actorGameObjects[j]->GetType() == GameObject_BULLET_RED)
							)
						{
							m_actorGameObjects[i]->SetDamage(m_actorGameObjects[j]->GetLife());
							m_actorGameObjects[j]->m_life = 0.f;
							collisionCount++;
						}
						else if (
							(m_actorGameObjects[j]->GetType() == GameObject_BUILDING_BLUE)
							&&
							(m_actorGameObjects[i]->GetType() == GameObject_BULLET_RED)
							)
						{
							m_actorGameObjects[j]->SetDamage(m_actorGameObjects[i]->GetLife());
							m_actorGameObjects[i]->m_life = 0.f;
							collisionCount++;
						}



						else if (
							(m_actorGameObjects[i]->GetType() == GameObject_BULLET_BLUE)
							&&
							(m_actorGameObjects[j]->GetType() == GameObject_BULLET_RED)
							)
						{
							m_actorGameObjects[i]->SetDamage(m_actorGameObjects[j]->GetLife());
							m_actorGameObjects[j]->m_life = 0.f;
							
						}
						else if (
							(m_actorGameObjects[j]->GetType() == GameObject_BULLET_BLUE)
							&&
							(m_actorGameObjects[i]->GetType() == GameObject_BULLET_RED)
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
				if (m_actorGameObjects[i] != NULL && m_actorGameObjects[i]->GetType() == GameObject_BUILDING_RED|| GameObject_BUILDING_BLUE)
				{

					m_actorGameObjects[i]->m_gauge -= 0.1f;
					if (m_actorGameObjects[i]->m_gauge <= 0.1f)
					{
						delete m_actorGameObjects[i];
						m_actorGameObjects[i] = NULL;
						m_sound->PlaySound(destroy, false, 0.2f);
					}
				}
			}
			else
			{
				if (m_actorGameObjects[i] != NULL && m_actorGameObjects[i]->GetType() == GameObject_BUILDING_RED||GameObject_BUILDING_BLUE)
				{
				/*	m_actorGameObjects[i]->m_color[0] = 1;
					m_actorGameObjects[i]->m_color[1] = 1;
					m_actorGameObjects[i]->m_color[2] = 0;
					m_actorGameObjects[i]->m_color[3] = 1;*/
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
