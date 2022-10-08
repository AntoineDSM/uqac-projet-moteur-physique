//Date de création : 19/09/22
//Créer par : Victor GUIRAUD
//Date de dernière modification : 19/09/22
//Modifié par : Victor GUIRAUD

#include "Forces/ParticleForceRegistry.h"
#include "Vector3D/Vector3D.h"

using namespace moteurJeux; 


void ParticleForceRegistry::updateForces(float duration) { 




Registry::iterator i = registrations.begin(); 


for (; i != registrations.end(); i++) {


 i->forceGenerator->updateForce(i->particle, duration);


}
}
