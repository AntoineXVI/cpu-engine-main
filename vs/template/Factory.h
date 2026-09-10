#pragma once
#include "enemy.h"
#include "Player.h"
#include "Rail.h"

class Factory
{
public:
	Factory();
	~Factory();

	Player* CreatePlayer(XMFLOAT2 initPos);
	Enemy* CreateEnemy(XMFLOAT2 initPos);
	Rail* CreateRail();


	cpu_mesh m_meshRail;
	cpu_mesh m_meshPlayer;
	cpu_mesh m_meshEnemy;
	cpu_mesh m_meshShadowEnemy;
};
