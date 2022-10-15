#pragma once
#include "ParticleLink.h"

class ParticleCable : public ParticleLink {
public:
	real maxLength;
	real restitution;
public:
	unsigned addContact(ParticleContact* contact, unsigned int limit) {
		real length = currentLength();

		// Check if we are overextended
		if (length < maxLength)
			return 0;

		// Otherwise, return the contact
		contact->particle[0] = particle[0];
		contact->particle[1] = particle[1];

		// Calculate the normal
		Vector3 normal = particle[1]->getPosition() - particle[0]->getPosition();
		normal.normalize();
		contact->contactNormal = normal;

		contact->penetration = length - maxLength;
		contact->restitution = restitution;

		return 1;
	}
};