//Date de cr�ation : 19/09/22
//Cr�er par : Victor GUIRAUD
//Date de derni�re modification : 19/09/22
//Modifi� par : Victor GUIRAUD

#include "ParticleForceRegistry.h"

using namespace moteurJeux; 


void ParticleForceRegistry::updateForces(float duration) { 




Registry::iterator i = registrations.begin(); 


for (; i != registrations.end(); i++) {


 i->fg->updateForce(i->particle, duration);


}
}
