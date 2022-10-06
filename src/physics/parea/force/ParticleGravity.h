#pragma once
#include "ParticleForceGenerator.h"

class ParticleGravity : public ParticleForceGenerator {
private:
	Vector3 gravity;
public:
	ParticleGravity(const Vector3& gravity);

	void updateForce(Particle* particle, real duration) {
		// Check that we do not have infinite mass
		if (!particle->hasFiniteMass()) return;
		
		// Apply the mass-scaled force to the particule
		particle->addForce(gravity * particle->getMass());
	}
};