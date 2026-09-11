#pragma once
#include "Actor.h"
#include "enemy.h"
#include "Player.h"
#include "Factory.h"

class Actor_Manager
{
public:
	Actor_Manager();
	~Actor_Manager();

	void DestroyAll();

	static Actor_Manager& GetInstance() { return *s_actorManager; }

	void AddEnemy(XMFLOAT2 initPos);

	void AddPlayer(XMFLOAT2 initPos);

	void AddRail();

	
	void UpdatePlayer(XMFLOAT2 posPlayer);
	void StopPlayer();
	void UpdateEnemyPhysics();
	void UpdateEnemyCollision();

	void PurgeEnemies();

	void ChangeEnemiesSpeed(float speed);

	void ResetEnemiesSpeed();

	void IncrementScore();
	void DecrementScore();

	int GetScore();

	int GetNumberEnemies();

	void ClearEnemies();

	void StopEnemies();

	Player* GetPlayer();

	void Release(cpu_entity* p);
	
	Factory factory;

private:
	inline static Actor_Manager* s_actorManager = nullptr;

	std::vector<Actor*> m_actors; //gestion memoire
	std::vector<Enemy*> m_enemies;

	Player* m_player;
	int m_score;

};

