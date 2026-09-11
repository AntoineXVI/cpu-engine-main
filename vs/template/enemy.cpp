#include "pch.h"
#include "enemy.h"

Enemy::Enemy()
{
	m_speed = 0.005f;
}

Enemy::~Enemy()
{
	Destroy();
}

void Enemy::Create(cpu_mesh& m_meshEnemy, cpu_mesh& m_meshShadow, XMFLOAT2 posEnemy)
{
	actorEntity = cpuEngine.CreateEntity();
	actorEntity->pMesh = &m_meshEnemy;
	actorEntity->transform.SetScaling(0.3);
	actorEntity->transform.SetPosition(posEnemy.x, 2.f, posEnemy.y);

	shadowEntity = cpuEngine.CreateEntity();
	shadowEntity->pMesh = &m_meshShadow;
	shadowEntity->transform.SetScaling(0.3);
	shadowEntity->pMaterial = &shadowMaterial;
	shadowMaterial.ps = ShadowShader;
	shadowEntity->transform.SetPosition(posEnemy.x, 0.05f, posEnemy.y);

	m_enemyFSM = cpuEngine.CreateFSM(this);
	m_enemyFSM->SetGlobal<StateEnemyFall>();
	m_enemyFSM->Add<StateEnemyCollisionFloor>("collisionFloor");
	m_enemyFSM->Add<StateEnemyCollisionPlayer>("collisionPlayer");
	m_enemyFSM->Add<StateEnemyEnd>("End");

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
	m_speed = 0.005f;
}

void Enemy::Fall()
{
	actorEntity->transform.pos.y -= m_speed;
}

void Enemy::Destroy()
{
	if ((actorEntity != nullptr) && (shadowEntity != nullptr))
	{
		actorEntity = cpuEngine.Release(actorEntity);
		m_enemyFSM = cpuEngine.Release(m_enemyFSM);
		CPU_DELPTR(actorEntity);

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

	/*cur.actorEntity = cpuEngine.Release(cur.actorEntity);
	cur.shadowEntity = cpuEngine.Release(cur.shadowEntity);*/
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
	/*cur.actorEntity = cpuEngine.Release(cur.actorEntity);
	cur.shadowEntity = cpuEngine.Release(cur.shadowEntity);*/
}

void StateEnemyCollisionPlayer::OnExit(Enemy& cur, int to)
{

}

void StateEnemyEnd::OnEnter(Enemy& cur, int from)
{
	
}

void StateEnemyEnd::OnExecute(Enemy& cur)
{
	cur.actorEntity->visible = false;
	cur.shadowEntity->visible = false;
}

void StateEnemyEnd::OnExit(Enemy& cur, int to)
{

}
