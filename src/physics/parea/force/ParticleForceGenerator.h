#pragma once
#include "../core/particle.h"

class ParticleForceGenerator{
public:
	virtual void updateForce(Particle* particle, real duration) = 0;
};

