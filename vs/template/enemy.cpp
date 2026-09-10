#include "pch.h"
#include "enemy.h"

Enemy::Enemy()
{
	m_speed = 0.5f;
}

Enemy::~Enemy()
{
	Destroy();
}

void Enemy::Create(cpu_mesh& m_meshEnemy, cpu_mesh& m_meshShadow, XMFLOAT2 posEnemy)
{
	entity = cpuEngine.CreateEntity();
	entity->pMesh = &m_meshEnemy;
	entity->transform.SetScaling(0.3);
	entity->transform.SetPosition(posEnemy.x, 2.f, posEnemy.y);

	shadowEntity = cpuEngine.CreateEntity();
	shadowEntity->pMesh = &m_meshShadow;
	shadowEntity->transform.SetScaling(0.3);
	shadowEntity->transform.SetPosition(posEnemy.x, 0.05f, posEnemy.y);
	shadowEntity->pMaterial = &shadowMaterial;
	shadowMaterial.ps = ShadowShader;

	m_enemyFSM = cpuEngine.CreateFSM(this);
	m_enemyFSM->SetGlobal<StateEnemyFall>();
	m_enemyFSM->Add<StateEnemyCollisionFloor>("collisionFloor");
	m_enemyFSM->Add<StateEnemyCollisionPlayer>("collisionPlayer");


	this->GetFSM()->ToState(CPU_ID(StateEnemyFall));
}

void Enemy::ShadowShader(cpu_ps_io& io)
{
	io.color = io.p.color;
	io.color = CPU_BLACK;
}

void Enemy::Move()
{

}

void Enemy::ChangeSpeed(float speed) 
{
	m_speed = speed;
}
void Enemy::ResetSpeed() 
{
	m_speed = 0.5f;
}

void Enemy::Fall()
{
	entity->transform.pos.y -= m_speed * cpuTime.delta;
}

void Enemy::Destroy()
{
	if (entity )
	{
		entity = cpuEngine.Release(entity);
		m_enemyFSM = cpuEngine.Release(m_enemyFSM);
		CPU_DELPTR(entity);
	}
	if (shadowEntity)
	{
		shadowEntity = cpuEngine.Release(shadowEntity);
		CPU_DELPTR(shadowEntity);
	}
}

void StateEnemyFall::OnEnter(Enemy& cur, int from)
{

}

void StateEnemyFall::OnExecute(Enemy& cur)
{
	cur.Fall();
}

void StateEnemyFall::OnExit(Enemy& cur, int to)
{
	//hide ?
}

void StateEnemyCollisionFloor::OnEnter(Enemy& cur, int from)
{
	Actor_Manager::GetInstance().DecrementScore();
}

void StateEnemyCollisionFloor::OnExecute(Enemy& cur)
{
	//play music fail 0.1s
	//cpuEngine.Release(cur.entity);
	//cpuEngine.Release(cur.shadowEntity);
}

void StateEnemyCollisionFloor::OnExit(Enemy& cur, int to)
{

}

void StateEnemyCollisionPlayer::OnEnter(Enemy& cur, int from)
{
	Actor_Manager::GetInstance().IncrementScore();
}

void StateEnemyCollisionPlayer::OnExecute(Enemy& cur)
{
	//cpuEngine.Release(cur.entity);
	//cpuEngine.Release(cur.shadowEntity);
}

void StateEnemyCollisionPlayer::OnExit(Enemy& cur, int to)
{

}