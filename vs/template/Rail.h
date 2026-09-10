#pragma once
#include "Actor.h"

class Rail : public Actor
{
public:

	Rail();
	~Rail();

	void Create(cpu_mesh& m_meshRail);

	virtual void Move();

	void Destroy();

	cpu_entity* entity;
};

