#pragma once
#include "ParticleForceGenerator.h"

class ParticleAnchoredSpring : public ParticleForceGenerator {
private:
	// other anchor
	Vector3 *anchor;

	real springConstant;

	real restLenght;
public:
	void updateForce(Particle* particle, real duration) {
		// Calculate the vector of the spring
		Vector3 force = particle->getPosition();
		force -= *anchor;

		// Calculate the magnitude of the force
		real magnitude = force.magnitude();
		magnitude = (magnitude - restLenght) * springConstant;

		// Calculate the final force and apply it
		force.normalize();
		force *= magnitude;
		particle->addForce(force);
	}
};