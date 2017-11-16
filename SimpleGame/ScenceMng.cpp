#include "stdafx.h"
#include "ScenceMng.h"
using namespace std;


ScenceMng::ScenceMng(int width, int height)
{
	// Initialize Renderer
	m_renderer = new Renderer(width, height);

	if (!m_renderer->IsInitialized())
	{
		std::cout << "ScenceMng::Renderer could not be initialized.. \n";
	}

	m_windowWidth = width;
	m_windowHeight = height;

	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		m_actorObjects[i] = NULL;
		m_bulletObjects[i] = NULL;
		
	}
}
//오브젝트 그리기
void ScenceMng::DrawAllObjects()
{
	m_renderer->DrawSolidRect(0, 0, 0, m_windowWidth, 0, 0, 0, 0.4);

	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		if (m_actorObjects[i] != NULL)
		{
			// Renderer Test
			m_renderer->DrawSolidRect(
				m_actorObjects[i]->m_x,
				m_actorObjects[i]->m_y,
				0,
				m_actorObjects[i]->m_size,
				m_actorObjects[i]->m_color[0],
				m_actorObjects[i]->m_color[1],
				m_actorObjects[i]->m_color[2],
				m_actorObjects[i]->m_color[3]
			);
		}
	}
	
	
	m_renderer->DrawTexturedRect(0, 0, 0, 50, 1, 1, 0, 1, m_texbulding);
	
	
	
	//에로우
	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		if (m_ArrowObjects[i] != NULL)
		{
			// Renderer Test
			m_renderer->DrawSolidRect(
				m_ArrowObjects[i]->m_x+10,
				m_ArrowObjects[i]->m_y,
				0,
				m_ArrowObjects[i]->m_size-5,
				m_ArrowObjects[i]->m_color[0]-1,
				m_ArrowObjects[i]->m_color[1],
				m_ArrowObjects[i]->m_color[2]-1,
				m_ArrowObjects[i]->m_color[3]
			);
		}
	}
}

ScenceMng::~ScenceMng()
{
}
//생성
int ScenceMng::AddActorObject(float x, float y, float type)
{
	//Find empty slot
	if (type == Object_Player)
	{
		for (int i = 0; i < MAX_OBJECT_COUNT; i++)
		{
			if (m_actorObjects[i] == NULL)
			{
				m_actorObjects[i] = new GameObject(x, y);
				return i;
			}
		}
	}
	if (type == Object_Arrow)
	{
		for (int i = 0; i < MAX_OBJECT_COUNT; i++)
		{
			if (m_ArrowObjects[i] == NULL)
			{
				m_ArrowObjects[i] = new GameObject(x, y);
				return i;
			}
		}
	}



	//slots are full
	std::cout << "slots are full \n";

	return -1;
}

void ScenceMng::DeleteActorObject(int index)
{
	if (m_actorObjects[index] != NULL)
	{
		//delete m_actorObjects[index];
		//m_actorObjects[index] = NULL;
	}
}
// 업데이트
void ScenceMng::UpdateAllActorObjects(float elapsedTime)
{
	DoCollisionTest();

	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		if (m_actorObjects[i] != NULL)
		{
			m_actorObjects[i]->Update(elapsedTime);
			m_ArrowObjects[i]->Update(elapsedTime);
		}
		if (m_bulletObjects[i] != NULL)
		{
			m_bulletObjects[i]->Update(elapsedTime);
			m_ArrowObjects[i]->Update(elapsedTime);
		}
	}

}

GameObject* ScenceMng::GetActorObject(int index)
{
	return m_actorObjects[index];
}

int ScenceMng::GetMaxObjectCount()
{
	return MAX_OBJECT_COUNT;
}

//충돌체크
void ScenceMng::DoCollisionTest()
{
	int collisionCount = 0;
	

	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		collisionCount = 0;
		if (m_actorObjects[i] != NULL)
		{
			for (int j = 0; j < MAX_OBJECT_COUNT; j++)
			{
				if (i == j)
					continue;

				if (m_actorObjects[j] != NULL)
				{
					float minX, minY;
					float maxX, maxY;

					float minX1, minY1;
					float maxX1, maxY1;

					float Arrow_minX, Arrow_minY;
					float Arrow_maxX, Arrow_maxY;

					float Arrow_minX1, Arrow_minY1;
					float Arrow_maxX1, Arrow_maxY1;
					

					minX = m_actorObjects[i]->m_x - m_actorObjects[i]->m_size / 2.f;
					minY = m_actorObjects[i]->m_y - m_actorObjects[i]->m_size / 2.f;
					maxX = m_actorObjects[i]->m_x + m_actorObjects[i]->m_size / 2.f;
					maxY = m_actorObjects[i]->m_y + m_actorObjects[i]->m_size / 2.f;
					minX1 = m_actorObjects[j]->m_x - m_actorObjects[j]->m_size / 2.f;
					minY1 = m_actorObjects[j]->m_y - m_actorObjects[j]->m_size / 2.f;
					maxX1 = m_actorObjects[j]->m_x + m_actorObjects[j]->m_size / 2.f;
					maxY1 = m_actorObjects[j]->m_y + m_actorObjects[j]->m_size / 2.f;

					Arrow_minX = m_ArrowObjects[i]->m_x - m_ArrowObjects[i]->m_size / 2.f;
					Arrow_minY = m_ArrowObjects[i]->m_y - m_ArrowObjects[i]->m_size / 2.f;
					Arrow_maxX = m_ArrowObjects[i]->m_x + m_ArrowObjects[i]->m_size / 2.f;
					Arrow_maxY = m_ArrowObjects[i]->m_y + m_ArrowObjects[i]->m_size / 2.f;
					Arrow_minX1 = m_ArrowObjects[j]->m_x - m_ArrowObjects[j]->m_size / 2.f;
					Arrow_minY1 = m_ArrowObjects[j]->m_y - m_ArrowObjects[j]->m_size / 2.f;
					Arrow_maxX1 = m_ArrowObjects[j]->m_x + m_ArrowObjects[j]->m_size / 2.f;
					Arrow_maxY1 = m_ArrowObjects[j]->m_y + m_ArrowObjects[j]->m_size / 2.f;

					//플레이어간의 충돌
					/*if (BoxBoxCollisionTest(minX, minY, maxX, maxY, minX1, minY1, maxX1, maxY1))
					{
						collisionCount++;
					}*/ 
					// 중앙 박스 충돌 
					if (BoxBoxCollisionTest(minX, minY, maxX, maxY,-25,-25,25,25))
					{
						collisionCount++;
					}
					if (BoxBoxCollisionTest(Arrow_minX, Arrow_minY, Arrow_maxX, Arrow_maxY, -25, -25, 25, 25))
					{
						collisionCount++;
						
					}
				}
			}
			
			
			//충돌되면 사라짐
			if (collisionCount > 0)
			{
				
				delete m_actorObjects[i];
				m_actorObjects[i] = NULL;
				delete m_ArrowObjects[i];
				m_ArrowObjects[i] = NULL;
				/*m_actorObjects[i]->m_color[0] = 1;
				m_actorObjects[i]->m_color[1] = 0;
				m_actorObjects[i]->m_color[2] = 0;
				m_actorObjects[i]->m_color[3] = 1;*/
			}
			else
			{
				/*m_actorObjects[i]->m_color[0] = 1;
				m_actorObjects[i]->m_color[1] = 1;
				m_actorObjects[i]->m_color[2] = 1;
				m_actorObjects[i]->m_color[3] = 1;*/
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
