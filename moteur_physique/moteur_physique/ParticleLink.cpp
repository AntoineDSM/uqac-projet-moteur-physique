#include "Particlelink.h"
#include "Vector3D.h"

float ParticleLink::currentLength() const { 


 Vector3D relativePos = particle[0]->getPosition() - particle[1]->getPosition();

 return relativePos.get_magnitude();

}
