#pragma once
class Actor: public cpu_object
{

public:
	Actor();
	virtual ~Actor();

	virtual void Move() = 0;
	void Destroy();

	cpu_mesh pMesh;
	float m_speed ;

	cpu_entity* actorEntity;
};

