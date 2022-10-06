#pragma once
#include "../core/Particle.h"
#include "ParticleContactGenerator.h"

class ParticleLink : public ParticleContactGenerator {
public:
	// Linked particles
	Particle* particle[2];

public:
	
	// Return the length of the link
	real currentLength() {
		Vector3 relativePos = particle[0]->getPosition() - particle[1]->getPosition();
		return relativePos.magnitude();
	}
	
	virtual unsigned addContact(ParticleContact* contact, unsigned int limit) const = 0;
};