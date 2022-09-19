
//Date de création :
//Créer par :
//Date de dernière modification : 16/09/22
//Modifié par : Victor GUIRAUD

#include "assert.h"
#include "Particle.h"
#include "Vector3D.h"

using namespace moteurJeux;

void Particle::integrate(double duration) { 
    
	// We don’t integrate things with infinite mass.
	if (inverseMass <= 0.0f) return; assert(duration > 0.0); 
	// Update linear position. 
	position.addScaledVector(velocity, duration); 
	
	// Work out the acceleration from the force. 
	// (We’ll add to this vector when we come to generate forces.) 
	Vector3D resultingAcc = acceleration; 
	// Update linear velocity from the acceleration. 
	velocity.addScaledVector(resultingAcc, duration); 
	// Impose drag. 
	velocity *= pow(damping, duration); 
}

// Clear the forces. 
//clearAccumulator();

void Particle::setMass(const double mass)
{
    assert(mass != 0);
    inverseMass = 1.0f / mass;
}

double Particle::getMass() const
{
    
        return 1.0f / inverseMass;
    
}

void Particle::setInverseMass(const double inverseMassValue)
{
    inverseMass = inverseMassValue;
}

double Particle::getInverseMass()
{
    return inverseMass;
}

void Particle::setDamping(const double dampingValue)
{
    damping = dampingValue;
}

double Particle::getDamping() const
{
    return damping;
}

void Particle::setPosition(const Vector3D& newPosition)
{
    position = newPosition;
}

void Particle::setPosition(const double x, const double y, const double z)
{
    position.x = x;
    position.y = y;
    position.z = z;
}

//void Particle::getPosition(Vector3D* position) const
//{
//    *position->position;
//}

Vector3D Particle::getPosition() const
{
    return position;
}

void Particle::setVelocity(const Vector3D& newVelocity)
{
    velocity = newVelocity;
}

void Particle::setVelocity(const double x, const double y, const double z)
{
    velocity.x = x;
    velocity.y = y;
    velocity.z = z;
}

//void Particle::getVelocity(Vector3D* velocity)
//{
//    *velocity = velocity;
//}

Vector3D Particle::getVelocity() const
{
    return velocity;
}

void Particle::setAcceleration(const Vector3D& newAcceleration)
{
    acceleration = newAcceleration;
}

void Particle::setAcceleration(const double x, const double y, const double z)
{
    acceleration.x = x;
    acceleration.y = y;
    acceleration.z = z;
}

Vector3D Particle::getAcceleration()
{
    return acceleration;
}

void Particle::clearAccumulators()
{
    //forceAccum.clear();
}