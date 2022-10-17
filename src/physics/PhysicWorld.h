#pragma once

#include <vector>

#include "core/Particle.h"
#include "contact/ParticleContactGenerator.h"
#include "contact/ParticleContactResolver.h"
#include "force/ParticleForceRegistry.h"


class PhysicWorld
{
public:
	typedef std::vector<Particle*> Particles;
	// typedef std::vector<ParticleContactGenerator*> ContactGenerators;

	Particles particles;
	// ParticleForceRegistry registry;
	// ParticleContactResolver resolver;
	// ContactGenerators contactGenerators;
	
	// Hold the list of contacts
	// ParticleContact* contacts;
	// Hold the maximum number of contacts
	// unsigned maxContacts;

public:
	PhysicWorld();

	// PhysicWorld(unsigned maxContacts, unsigned iterations = 0);
	
	// Initialize the world for a simulation frame
	// void startFrame();

	// Report their contacts and return the number of generated contacts
	// unsigned generateContacts();

	// Integrate all the particles in the world in time
	void integrate(real duration);

	// Process all the physics for the physic world
	// void runPhysics(real duration);
};
