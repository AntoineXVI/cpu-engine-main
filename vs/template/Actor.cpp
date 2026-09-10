#include "pch.h"
#include "Actor.h"

Actor::Actor()
{
	m_speed = 0.f;
}

Actor::~Actor()
{

}

void Actor::Destroy()
{
	//actor = cpuEngine.Release(actor);
}
