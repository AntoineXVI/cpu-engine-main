#include "pch.h"
#include "Actor_Manager.h"
#include "Factory.h"

Actor_Manager::Actor_Manager()
{
	s_actorManager = this;
	m_player = nullptr;
	m_score = 0;
}

Actor_Manager::~Actor_Manager()
{
	
}

void Actor_Manager::DestroyAll()
{
	for (Actor* actor : m_actors)
	{
		if (actor->actorEntity != nullptr)
		{
			actor->actorEntity = cpuEngine.Release(actor->actorEntity);
			delete actor;
		}
	}
}

void Actor_Manager::AddPlayer(XMFLOAT2 initPos)
{
	Player* player = factory.CreatePlayer(initPos);
	m_actors.push_back(player);
	m_player = player;
}

void Actor_Manager::AddRail()
{
	Rail* rail = factory.CreateRail();
	m_actors.push_back(rail);
}


void Actor_Manager::AddEnemy(XMFLOAT2 initPos)
{
	Enemy* enemy = factory.CreateEnemy(initPos);
	m_enemies.push_back(enemy);
	m_actors.push_back(enemy);
}


void Actor_Manager::UpdatePlayer(XMFLOAT2 posPlayer)
{
	m_player->SetNewPosition(posPlayer);
	m_player->GetFSM()->ToState(CPU_ID(StatePlayerMovement));
}

void Actor_Manager::StopPlayer()
{
	m_player->GetFSM()->ToState(CPU_ID(StatePlayerIdle));
}

void Actor_Manager::UpdateEnemyPhysics()
{
	/*for (auto enemy = m_enemies.begin(); enemy != m_enemies.end(); enemy++)
	{
		(*enemy)->GetFSM()->ToState(CPU_ID(StateEnemyFall));
	}*/
}

void Actor_Manager::UpdateEnemyCollision()
{
	for (auto enemy = m_enemies.begin(); enemy != m_enemies.end(); enemy++)
	{
		cpu_entity* cpuEnemy = (*enemy)->actorEntity;
		cpu_entity* cpuPlayer = m_player->actorEntity;
		cpu_entity* cpuShadow = (*enemy)->shadowEntity;
		if (cpuEnemy->transform.pos.y < 0.0f)
		{
			(*enemy)->GetFSM()->ToState(CPU_ID(StateEnemyCollisionFloor));
			cpuEngine.Release(cpuEnemy);
			cpuEngine.Release(cpuShadow);
		}
		else if ((cpuEnemy->transform.pos.x < cpuPlayer->transform.pos.x + 0.2f) && (cpuEnemy->transform.pos.x > cpuPlayer->transform.pos.x - 0.2f) &&
			(cpuEnemy->transform.pos.y < cpuPlayer->transform.pos.y + 0.2f) && (cpuEnemy->transform.pos.y > cpuPlayer->transform.pos.y - 0.2f))
		{
			(*enemy)->GetFSM()->ToState(CPU_ID(StateEnemyCollisionPlayer));
			m_player->GetFSM()->ToState(CPU_ID(StatePlayerCollision));
			cpuEngine.Release(cpuEnemy);
			cpuEngine.Release(cpuShadow);
		}
	}	
}

void Actor_Manager::PurgeEnemies()
{
	for (auto enemy = m_enemies.begin(); enemy != m_enemies.end(); )
	{
		cpu_entity* cpuEnemy = (*enemy)->actorEntity;
		if (cpuEnemy->dead )
		{
			enemy = m_enemies.erase(enemy);
		}			
		else
			++enemy;
	}
}

void Actor_Manager::ChangeEnemiesSpeed(float speed)
{
	for (auto enemy = m_enemies.begin(); enemy != m_enemies.end(); enemy++)
	{
		(*enemy)->ChangeSpeed(speed);
	}
}
void Actor_Manager::ResetEnemiesSpeed()
{
	for (auto enemy = m_enemies.begin(); enemy != m_enemies.end(); enemy++)
	{
		(*enemy)->ResetSpeed();
	}
}

void Actor_Manager::IncrementScore()
{
	m_score += 1;
}

void Actor_Manager::DecrementScore()
{
	m_score -= 1;
}

int Actor_Manager::GetScore()
{
	return m_score;
}

int Actor_Manager::GetNumberEnemies()
{
	return m_enemies.size();
}

void Actor_Manager::ClearEnemies()
{
	for (auto enemy = m_enemies.begin(); enemy != m_enemies.end(); enemy++)
	{
		cpu_entity* cpuEnemy = (*enemy)->actorEntity;
		cpu_entity* cpuShadow = (*enemy)->shadowEntity;
		Release(cpuEnemy);
		Release(cpuShadow);
		cpuEngine.Release(cpuEnemy);
		cpuEngine.Release(cpuShadow);
	}
	PurgeEnemies();
}

void Actor_Manager::StopEnemies()
{
	for (auto enemy = m_enemies.begin(); enemy != m_enemies.end(); enemy++)
	{
		(*enemy)->GetFSM()->ToState(CPU_ID(StateEnemyEnd));
	}
}


Player* Actor_Manager::GetPlayer()
{
	return m_player;
}

void Actor_Manager::Release(cpu_entity* p)
{
	if (p == nullptr || p->dead)
		return;
	p->dead = true;

}