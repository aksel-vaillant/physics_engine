#pragma once

#include "Vector3.h"

class Particle {
private:
	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;

	real damping;
	real inverseMass;

	Vector3 forceAccum;

public:
	/* ---------- Constructors ---------- */

	Particle();
	Particle(Vector3 position);
	Particle(Vector3 position, Vector3 velocity);
	
	/* ---------- Functions ---------- */

	void integrate(real duration);

	void addForce(const Vector3 &force);
	
	void clearAccumulator();

	bool hasFiniteMass() {
		if (inverseMass <= 0.0f)
			return false;
		else
			return true;
	}
	/* ---------- Getters & Setters ---------- */

	Vector3 getPosition() { return position; }
	void setPosition(Vector3 position) { position = position; }

	Vector3 getVelocity() { return velocity; }
	void setVelocity(Vector3 velocity) { velocity = velocity; }
	
	Vector3 getAcceleration() { return acceleration; }
	void setAcceleration(Vector3 acceleration) { acceleration = acceleration; }

	real getMass() { return 1 / inverseMass; }
	void setMass(real mass) { inverseMass = 1 / mass; }

	real getInverseMass() { return inverseMass; }
	void setInverseMass(real inverseMass) { inverseMass = inverseMass; }
};
