#pragma once
#include "Actor.h"

class Enemy : public Actor
{

public:

	Enemy();
	~Enemy();

	void Create(cpu_mesh& m_meshEnemy, cpu_mesh& m_meshShadow, XMFLOAT2 posEnemy);

	static void ShadowShader(cpu_ps_io& io);

	virtual void Move();

	void ChangeSpeed(float speed);

	void ResetSpeed();

	void Fall();

	void Destroy();

	cpu_fsm<Enemy>* GetFSM() { return m_enemyFSM; }

	cpu_entity* shadowEntity;
	cpu_material shadowMaterial;	

protected:
	cpu_fsm<Enemy>* m_enemyFSM;
};

struct StateEnemyFall
{
	void OnEnter(Enemy& cur, int from);
	void OnExecute(Enemy& cur);
	void OnExit(Enemy& cur, int to);
};

struct StateEnemyCollisionFloor
{
	void OnEnter(Enemy& cur, int from);
	void OnExecute(Enemy& cur);
	void OnExit(Enemy& cur, int to);
};

struct StateEnemyCollisionPlayer
{
	void OnEnter(Enemy& cur, int from);
	void OnExecute(Enemy& cur);
	void OnExit(Enemy& cur, int to);
};

struct StateEnemyEnd
{
	void OnEnter(Enemy& cur, int from);
	void OnExecute(Enemy& cur);
	void OnExit(Enemy& cur, int to);
};
