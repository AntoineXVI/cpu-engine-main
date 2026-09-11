#include "pch.h"
#include "Rail.h"

Rail::Rail()
{	
}

Rail::~Rail()
{
	Destroy();
}
void Rail::Create(cpu_mesh& m_meshEnemy)
{
	actorEntity = cpuEngine.CreateEntity();
	actorEntity->pMesh = &m_meshEnemy;
	actorEntity->transform.SetScaling(1.f);
	actorEntity->transform.SetPosition(0.f, 0.f, 0.f);
}


void Rail::Move()
{

}

void Rail::Destroy()
{
	if (actorEntity)
	{
		actorEntity = cpuEngine.Release(actorEntity);
		CPU_DELPTR(actorEntity);
	}
}