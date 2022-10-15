#pragma once
#include "ParticleForceGenerator.h"

class ParticleBuoyancy : public ParticleForceGenerator {
private:
	// particle properties
	real maxDepth;
	real volume;

	// effect properties
	real waterHeight;
	real liquidDensity = 1000.f;
public:
	void updateForce(Particle* particle, real duration) {
		// Calculate the submersion depth
		real depth = particle->getPosition().y;

		// Check if we're out of the water
		if (depth >= waterHeight + maxDepth) return;
		Vector3 force(0.0f);

		// Check if we're at maximum depth
		if (depth <= waterHeight - maxDepth) {
			force.y = liquidDensity * volume;
			particle->addForce(force);
			return;
		}

		// Otherwise we are partly submerged
		force.y = liquidDensity * volume * (depth - maxDepth - waterHeight) / 2 * maxDepth;
		particle->addForce(force);
	}
};