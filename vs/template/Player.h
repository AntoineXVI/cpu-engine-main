#pragma once
#include "Actor.h"

class Player : public Actor
{
public:

	Player();
	~Player();
	void Create(cpu_mesh& m_meshPlayer, XMFLOAT2 posPlayer);
	static void PlayerShader(cpu_ps_io& io);

	void SetNewPosition(XMFLOAT2 posPlayer);

	virtual void Move();

	void Destroy();

	int GetState();

	//void MoveTo(XMFLOAT2 posPlayer);

	cpu_fsm<Player>* GetFSM() { return m_playerFSM; }

	cpu_entity* entity;
private:
	//float m_playerAngle;

	XMFLOAT2 m_posPlayer;
	cpu_material playerMaterial;

	cpu_entity* m_pEntity;

	cpu_fsm<Player>* m_playerFSM;
};

struct StatePlayerIdle
{
	void OnEnter(Player& cur, int from);
	void OnExecute(Player& cur);
	void OnExit(Player& cur, int to);
};

struct StatePlayerMovement
{
	void OnEnter(Player& cur, int from);
	void OnExecute(Player& cur);
	void OnExit(Player& cur, int to);
};

struct StatePlayerCollision
{
	void OnEnter(Player& cur, int from);
	void OnExecute(Player& cur);
	void OnExit(Player& cur, int to);
};

