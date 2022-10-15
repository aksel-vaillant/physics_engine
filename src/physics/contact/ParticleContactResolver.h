#pragma once
#include "ParticleContact.h"
#include <limits>


class ParticleContactResolver {
protected:
	unsigned iterations;
	unsigned iterationsUsed;
public:

	ParticleContactResolver(unsigned int iterations);

	void setIterations(unsigned int iterations) {
		iterations = iterations;
	}

	void resolveContacts(ParticleContact* contactArray, unsigned int numContacts, real duration) {
		unsigned int i;
		iterationsUsed = 0;

		while (iterationsUsed < iterations) {
			real max = std::numeric_limits<real>::max();
			unsigned maxIndex = numContacts;

			for (i = 0; i < numContacts; i++) {
				real sepVel = contactArray[i].calculateSeparatingVelocity();
				if (sepVel < max &&
					(sepVel < 0 || contactArray[i].penetration > 0)) {
					max = sepVel;
					maxIndex = i;
				}
			}

			// Check if it's worth
			if (maxIndex == numContacts) break;

			// Resolve this contact
			contactArray[maxIndex].resolve(duration);
			iterationsUsed++;
		}
		
	}
};