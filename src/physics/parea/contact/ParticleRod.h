#pragma once
#include "ParticleLink.h"

class ParticleRod : public ParticleLink {
public:
	real length;
public:
	unsigned addContact(ParticleContact* contact, unsigned int limit) {
		real currentLen = currentLength();

		// Check if we are overextended
		if (currentLen < length)
			return 0;

		// Otherwise, return the contact
		contact->particle[0] = particle[0];
		contact->particle[1] = particle[1];

		// Calculate the normal
		Vector3 normal = particle[1]->getPosition() - particle[0]->getPosition();
		normal.normalize();

		// Check if we are extending or compressing
		if (currentLen > length) {
			contact->contactNormal = normal;
			contact->penetration = currentLen - length;
		}
		else {
			contact->contactNormal = normal * -1;
			contact->penetration = length - currentLen;
		}

		// Always use zero resitutiton (no bounciness)
		contact->restitution = 0;

		return 1;
	}
};