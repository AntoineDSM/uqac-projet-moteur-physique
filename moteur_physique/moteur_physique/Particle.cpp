
//Date de création :
//Créer par :
//Date de dernière modification : 19/09/22
//Modifié par : Victor GUIRAUD

#include "assert.h"
#include "Particle.h";
#include "Vector3D.h"



using namespace moteurJeux;
//using namespace Particle;
Particle p;

void integrate(double duration) { 
    
	// We don’t integrate things with infinite mass.
	if (p.inverseMass <= 0.0f) return; assert(duration > 0.0); 
	// Update linear position. 
	p.position.addScaledVector(p.velocity, duration); 
	
	// Work out the acceleration from the force. 
	// (We’ll add to this vector when we come to generate forces.) 
	Vector3D resultingAcc = p.acceleration; 
	// Update linear velocity from the acceleration. 
	p.velocity.addScaledVector(resultingAcc, duration); 
	// Impose drag. 
	p.velocity *= pow(p.damping, duration); 
} 
    // Clear the forces. 
    //clearAccumulator();
    
    
    void setMass(const double mass)
    {
        assert(mass != 0);
         p.inverseMass = 1.0f / mass;
    }


    double getMass() 
    {
        
            return 1.0f / p.inverseMass;
        
    }

    void setInverseMass(const double inverseMass)
    {
        p.inverseMass = inverseMass;
    }

    double getInverseMass() 
    {
        return p.inverseMass;
    }

    bool Particle::hasFiniteMass() const
    {
        return inverseMass >= 0.0f;
    }

    void setDamping(const double damping)
    {
        p.damping = damping;
    }

    double getDamping() 
    {
        return p.damping;
    }

    void setPosition(const Vector3D& position)
    {
        p.position = position;
    }

    void setPosition(const double x, const double y, const double z)
    {
        p.position.x = x;
        p.position.y = y;
        p.position.z = z;
    }

    void getPosition(Vector3D& position) 
    {
        p.position = position;
    }

    Vector3D getPosition() 
    {
        return p.position;
    }

    void setVelocity(const Vector3D& velocity)
    {
        p.velocity = velocity;
    }

    void setVelocity(const double x, const double y, const double z)
    {
        p.velocity.x = x;
        p.velocity.y = y;
        p.velocity.z = z;
    }

    void getVelocity(Vector3D& velocity) 
    {
       p.velocity = velocity;
    }

    Vector3D getVelocity() 
    {
        return p.velocity;
    }

    void setAcceleration(const Vector3D& acceleration)
    {
        p.acceleration = acceleration;
    }

    void setAcceleration(const double x, const double y, const double z)
    {
        p.acceleration.x = x;
        p.acceleration.y = y;
        p.acceleration.z = z;
    }

    void getAcceleration(Vector3D& acceleration) 
    {
        p.acceleration = acceleration;
    }

    Vector3D getAcceleration()
    {
        return p.acceleration;
    }

    void clearAccumulator()
    {
       // p.forceAccum.clear();
    }
    
	
=======
 // Clear the forces. 
 void Particle::clearAccumulators(){
    forceAccum.clear();
 }

 void Particle::addForce(Vector3D& force) { 
	 forceAccum += force;
 } 

