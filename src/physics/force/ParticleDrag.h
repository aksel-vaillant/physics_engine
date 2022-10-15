#pragma once
#include "ParticleForceGenerator.h"

class ParticleDrag : public ParticleForceGenerator {
private:
	// drag coefficients
	real k1;
	real k2;
public:
	void updateForce(Particle* particle, real duration) {
		Vector3 force = particle->getVelocity();

		// Calcultate the total drag coefficient
		real dragCoeff = force.magnitude();
		dragCoeff = k1 * dragCoeff + k2 * dragCoeff * dragCoeff;

		// Calculate the final force and apply it
		force.normalize();
		force *= -dragCoeff;
		particle->addForce(force);
	}
};