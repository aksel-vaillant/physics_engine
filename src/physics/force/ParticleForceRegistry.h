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
	void add(Particle* particle, ParticleForceGenerator* forceGenerator) {
		ParticleForceEntry pfe;
		pfe.particle = particle;
		pfe.forceGenerator = forceGenerator;

		registries.push_back(pfe);
	}

	void remove(Particle* particle, ParticleForceGenerator* forceGenerator) {
		ParticleForceEntry pfe;
		pfe.particle = particle;
		pfe.forceGenerator = forceGenerator;
		registries.erase(std::remove(registries.begin(), registries.end(), pfe), registries.end());
	}
	
	void clear() {
		registries.clear();
	}

	void updateForces(real duration) {
		Registry::iterator it;
		for (it = registries.begin(); it != registries.end(); it++) {
			it->forceGenerator->updateForce(it->particle, duration);
		}
	}
};