#pragma once

#include "../core/particle.h"
#include "ParticleForceGenerator.h"
#include <vector>

class ParticleForceRegistry {
private:
	struct ParticleForceEntry {
		Particle *particle;
		ParticleForceGenerator *forceGenerator;
	};

	typedef std::vector<ParticleForceEntry> Registry;
	Registry registries;

public:
	void add(Particle *particle, ParticleForceGenerator *forceGenerator);
	void remove(Particle *particle, ParticleForceGenerator *forceGenerator);
	void clear();

	void updateForces(real duration) {
		Registry::iterator it;
		for (it = registries.begin(); it != registries.end(); it++) {
			it->forceGenerator->updateForce(it->particle, duration);
		}
	}
};