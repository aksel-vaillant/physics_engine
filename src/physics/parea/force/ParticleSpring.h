#pragma once
#include "ParticleForceGenerator.h"

class ParticleSpring : public ParticleForceGenerator {
private:
	// other anchor
	Particle* other;

	real springConstant;

	real restLenght;
public:
	void updateForce(Particle* particle, real duration) {
		// Calculate the vector of the spring
		Vector3 force = particle->getPosition();
		force -= other->getPosition();

		// Calculate the magnitude of the force
		real magnitude = force.magnitude();
		magnitude = real_abs(magnitude - restLenght);
		magnitude *= springConstant;

		// Calculate the final force and apply it
		force.normalize();
		force *= -magnitude;
		particle->addForce(force);
	}
};