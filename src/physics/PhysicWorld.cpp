#include "PhysicWorld.h"


/*unsigned PhysicWorld::generateContacts()
{
	unsigned limit = maxContacts;
	ParticleContact* nextContact = contacts;

	ContactGenerators::iterator i;
	for (i = contactGenerators.begin(); i != contactGenerators.end(); i++) {
		unsigned used = (*i)->addContact(nextContact, limit);
		limit -= used;
		nextContact += used;

		// Check if we run out of contacts
		if (limit <= 0) break;
	}

	// Return the number of contacts used
	return maxContacts - limit;
}*/

PhysicWorld::PhysicWorld()
{
}

void PhysicWorld::integrate(real duration)
{
	Particles::iterator p;
	for (p = particles.begin(); p != particles.end(); p++) {
		(*p)->integrate(duration);
	}
}

/*
void PhysicWorld::runPhysics(real duration)
{
	registry.updateForces(duration);
	integrate(duration);

	unsigned int usedContacts = generateContacts();

	if (usedContacts) {
		//if (calculateIterations)
		//	resolver.setIterations(usedContacts * 2);
		
		resolver.resolveContacts(contacts, usedContacts, duration);
	}
}*/