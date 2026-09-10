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
	entity = cpuEngine.CreateEntity();
	entity->pMesh = &m_meshEnemy;
	entity->transform.SetScaling(1.f);
	entity->transform.SetPosition(0.f, 0.f, 0.f);
}


void Rail::Move()
{

}

void Rail::Destroy()
{
	if (entity)
	{
		entity = cpuEngine.Release(entity);
		CPU_DELPTR(entity);
	}
}