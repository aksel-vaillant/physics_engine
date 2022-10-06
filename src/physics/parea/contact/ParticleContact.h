#pragma once
#include "../core/Particle.h"
class ParticleContact {
public:
	// Holds the particles that are involved in the contact
	Particle* particle[2];

	// Holds the normal resititution coefficient at the contact
	real restitution;

	// Holds the depth of the penetration at the contact
	real penetration;

	// Holds the direction of the contact inworld coordinates
	Vector3 contactNormal;

	// Resolves this contact for both velocity and interpenetration
	void resolve(real duration) {
		resolveVelocity(duration);
		resolveInterpenetration(duration);
	}

	// Calculates the seperating velocity at this contact
	real calculateSeparatingVelocity() {
		Vector3 relativeVelocity = particle[0]->getVelocity();
		if (particle[1]) relativeVelocity -= particle[1]->getVelocity();
		return relativeVelocity * contactNormal;
	}

private:
	// Handles the impulse calculations for this collision
	void resolveVelocity(real duration) {
		real seperatingVelocity = calculateSeparatingVelocity();

		// Check if it needs to be resolved
		if (seperatingVelocity > 0) return;

		// Calculate the new seperating velocity
		real newSeperatingVelocity = -seperatingVelocity * restitution;
		
		// Calculating the velocity buildup due to acceleration only
		Vector3 accCausedVelocity = particle[0]->getAcceleration();
		if (particle[1]) accCausedVelocity -= particle[1]->getAcceleration();
		real accCausedSepVelocity = accCausedVelocity * contactNormal * duration;
		
		// Check if we have a closing velocity due to aceleration buildup
		if (accCausedSepVelocity < 0) {
			newSeperatingVelocity += restitution * accCausedSepVelocity;
			if (newSeperatingVelocity < 0) newSeperatingVelocity = 0;
		}
		
		real deltaVelocity = newSeperatingVelocity - seperatingVelocity;

		// Calculte the total of inverse mass
		real totalInverseMass = particle[0]->getInverseMass();
		if (particle[1]) totalInverseMass += particle[1]->getInverseMass();

		// If all particles have infinite mass, then impulses have no effect
		if (totalInverseMass <= 0) return;

		// Calculate the impulse to apply
		real impulse = deltaVelocity / totalInverseMass;

		// Find the amount of impulse per unit of inverse mass
		Vector3 impulsePerIMass = contactNormal * impulse;

		// Apply impulses
		particle[0]->setVelocity(
			particle[0]->getVelocity() +
			impulsePerIMass * particle[0]->getInverseMass()
		);

		if (particle[1])
			particle[1]->setVelocity(
				particle[1]->getVelocity() +
				impulsePerIMass * -particle[1]->getInverseMass()
			);
	}

	// Handles the interpenetration resolution for this contact
	void resolveInterpenetration(real duration) {
		// If we don't have any penetration, skip this step
		if (penetration <= 0) return;

		// Calculte the total of inverse mass
		real totalInverseMass = particle[0]->getInverseMass();
		if (particle[1]) totalInverseMass += particle[1]->getInverseMass();

		// If all particles have infinite mass, then we do nothing
		if (totalInverseMass <= 0) return;
	
		// Find the amount of impulse per unit of inverse mass
		Vector3 movePerIMass = contactNormal * (penetration/ totalInverseMass);

		// Calculate the movement amounts
		Vector3 particleMovement[2];
		particleMovement[0] = movePerIMass * particle[0]->getInverseMass();
		if (particle[1])
			particleMovement[1] = movePerIMass * -particle[1]->getInverseMass();
		else
			particleMovement[1].clear();
	
		// Apply the penetration resolution
		particle[0]->setPosition(
			particle[0]->getPosition() + particleMovement[0]
		);

		if(particle[1])
			particle[1]->setPosition(
				particle[1]->getPosition() + particleMovement[1]
			);
	}
};