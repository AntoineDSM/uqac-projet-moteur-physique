
//Date de création :
//Créer par :
//Date de dernière modification : 16/09/22
//Modifié par : Victor GUIRAUD

#include "assert.h"
#include "Particle.h"
#include "Vector3D.h"



using namespace moteurJeux;
//using namespace Particle;

//void integrate(double duration) { 
    /*
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
    
    
    void setMass(const double mass)
    {
        assert(mass != 0);
        inverseMass = 1.0f / mass;
    }

    double getMass() 
    {
        
            return 1.0f / inverseMass;
        
    }

    void setInverseMass(const double inverseMass)
    {
        inverseMass = inverseMass;
    }

    double getInverseMass() 
    {
        return inverseMass;
    }



    void setDamping(const double damping)
    {
        damping = damping;
    }

    double getDamping() 
    {
        return damping;
    }

    void setPosition(const Vector3D& position)
    {
        position = position;
    }

    void setPosition(const double x, const double y, const double z)
    {
        position.x = x;
        position.y = y;
        position.z = z;
    }

    void getPosition(Vector3D* position) 
    {
        *position = position;
    }

    Vector3D getPosition() 
    {
        return position;
    }

    void setVelocity(const Vector3D& velocity)
    {
        Particle::velocity = velocity;
    }

    void setVelocity(const double x, const double y, const double z)
    {
        velocity.x = x;
        velocity.y = y;
        velocity.z = z;
    }

    void getVelocity(Vector3D* velocity) 
    {
        *velocity = velocity;
    }

    Vector3D getVelocity() 
    {
        return velocity;
    }

    void setAcceleration(const Vector3D& acceleration)
    {
        acceleration = acceleration;
    }

    void setAcceleration(const double x, const double y, const double z)
    {
        acceleration.x = x;
        acceleration.y = y;
        acceleration.z = z;
    }

    void getAcceleration(Vector3D* acceleration) 
    {
        *acceleration = acceleration;
    }

    Vector3D getAcceleration()
    {
        return acceleration;
    }

    void clearAccumulator()
    {
        forceAccum.clear();
    }
	*/