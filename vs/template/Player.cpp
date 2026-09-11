#include "pch.h"
#include "Player.h"

Player::Player()
{
	//m_playerAngle = 0.f;
}

Player::~Player()
{
	Destroy();
}

void Player::Create(cpu_mesh& m_meshPlayer, XMFLOAT2 posPlayer)
{
	actorEntity = cpuEngine.CreateEntity();
	actorEntity->pMesh = &m_meshPlayer;
	actorEntity->transform.SetScaling(0.2);
	actorEntity->transform.SetPosition(posPlayer.x, 0.1f, posPlayer.y);
	m_posPlayer = posPlayer;
	actorEntity->pMaterial = &playerMaterial;
	playerMaterial.ps = PlayerShader;

	m_playerFSM = cpuEngine.CreateFSM(this);
	//m_playerFSM->SetGlobal<StatePlayerIdle>();
	m_playerFSM->Add<StatePlayerIdle>("Idle");
	m_playerFSM->Add<StatePlayerCollision>("Collision");
	m_playerFSM->Add<StatePlayerMovement>("Movement");

	this->GetFSM()->ToState(CPU_ID(StatePlayerIdle));
}

void Player::PlayerShader(cpu_ps_io& io)
{
	io.color = io.p.color;
	io.color = CPU_RED;
}

void Player::SetNewPosition(XMFLOAT2 posPlayer)
{
	m_posPlayer.x = posPlayer.x;
	m_posPlayer.y = posPlayer.y;
}

void Player::Move()
{
	actorEntity->transform.pos.x = m_posPlayer.x;
	actorEntity->transform.pos.z = m_posPlayer.y;
}


void Player::Destroy()
{
	if (actorEntity != nullptr)
	{
		actorEntity = cpuEngine.Release(actorEntity);
		m_playerFSM = cpuEngine.Release(m_playerFSM);
		CPU_DELPTR(actorEntity);
	}
}

int Player::GetState()
{
	return this->GetFSM()->state;
}

void StatePlayerIdle::OnEnter(Player& cur, int from)
{

}

void StatePlayerIdle::OnExecute(Player& cur)
{
	cur.m_speed = 0.f;
}

void StatePlayerIdle::OnExit(Player& cur, int to)
{

}

void StatePlayerMovement::OnEnter(Player& cur, int from)
{
	cur.m_speed = 1.f;
	//cur.m_speed = 0.1f;
}

void StatePlayerMovement::OnExecute(Player& cur)
{
	/*if (cur.m_speed < 1.f)
	{
		cur.m_speed += 0.1f;
	}*/
	cur.Move();
	cur.GetFSM()->ToState(CPU_ID(StatePlayerIdle));
}

void StatePlayerMovement::OnExit(Player& cur, int to)
{

}

void StatePlayerCollision::OnEnter(Player& cur, int from)
{

}

void StatePlayerCollision::OnExecute(Player& cur)
{
	//collide with other (enemy) 
	
	//
		
	if (cur.GetFSM()->totalTime < 0.1f)
	{
		//play music 0.1s
	}
	else
	{
		cur.GetFSM()->ToState(CPU_ID(StatePlayerIdle));
	}
}

void StatePlayerCollision::OnExit(Player& cur, int to)
{

}
