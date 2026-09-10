#include "pch.h"
#include "Factory.h"
#include "Actor.h"

Factory::Factory()
{

}

Factory::~Factory()
{

}

Player* Factory::CreatePlayer(XMFLOAT2 initPos)
{
	m_meshPlayer.CreateCylinder(0.5f, 0.5f, 20);
	Player* player = new Player();
	player->Create(m_meshPlayer, initPos);
	return player;
}

Enemy* Factory::CreateEnemy(XMFLOAT2 initPos)
{
	m_meshEnemy.CreateSphere(0.5f);
	m_meshShadowEnemy.CreateCircle(0.5f, 20);
	Enemy* enemy = new Enemy();
	enemy->Create(m_meshEnemy, m_meshShadowEnemy, initPos);
	return enemy;
}

Rail* Factory::CreateRail()
{
	m_meshRail.CreateCircle(2.f, 40);
	Rail* rail = new Rail();
	rail->Create(m_meshRail);
	return rail;
}

