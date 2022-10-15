#pragma once

#include "Particle.h"
#include <cassert>

/* ---------- CONSTRUCTORS ---------- */

Particle::Particle(Vector3 p)
{
	position = p;
	velocity = Vector3(0.0f);
	acceleration = Vector3(0.0f);

	//hard values for testing
	inverseMass = 1.0f;
	damping = 1.0f;
}

Particle::Particle(Vector3 p, Vector3 v)
{
	position = p;
	velocity = v;
	acceleration = Vector3(0.0f);

	//hard values for testing
	inverseMass = 1.0f;
	damping = 1.0f;
}


void Particle::integrate(real duration) {
	//Can not integrate object with infinite mass
	if (!hasFiniteMass()) return;

	assert(duration > 0.0);

	acceleration = Vector3(0.0f, -9.81f, 0.0f);

	position.addScaledVector(velocity, duration);

	Vector3 resultingAcc = acceleration;

	velocity.addScaledVector(resultingAcc, duration);
	velocity *= real_pow(damping, duration);
	
	clearAccumulator();

	if (position.y < 1.0f)
		position.y = 1.0f;

	/*
	acceleration = Vector3(0.0f, gravityConstant, 0.0f);
	velocity += acceleration * duration;
	//velocity -= damping * dt;
	position += velocity * duration + acceleration * duration * duration;
	*/
}

void Particle::clearAccumulator() {
	forceAccum.clear();
}

bool Particle::hasFiniteMass()
{
	if (inverseMass <= 0.0f)
		return false;
	else
		return true;
}

void Particle::addForce(const Vector3 &force) {
	forceAccum += force;
}

