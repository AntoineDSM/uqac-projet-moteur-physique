
//Date de création :
//Créer par :
//Date de dernière modification : 16/09/22
//Modifié par : Victor GUIRAUD

#include "assert.h"
#include "Particles/Particle.h"
#include "Vector3D/Vector3D.h"

using namespace moteurJeux;

void Particle::integrate(double duration) { 
    
	//Si nous avons une masse infinie nous ne pouvons pas integrer.
	if (inverseMass <= 0.0f) return;
	assert(duration > 0.0);

	//on applique notre accumulateur sur notre velocite
	//velocity.multiplyBy(forceAccum);
	
	//nous actualisons la position en fonction de la vitesse et de la duree de la derniere frame. Vu que nous n'avons pas encore le temps de la frame courante
	//et le temps que les calculs vont nous prendre, nous nous callons sur la duree de la frame n-1. Nous gardons un decalage de 1 pour se preserver des pertes
	//de performances eventuelles. p = p + vt
	position.addScaledVector(velocity, duration);

	//Nous avons actualise la position, maintenant nous actualisons l'evolution de la vitesse en fonction de l'acceleration positive ou negative.
	//Cette vitesse agira sur la position a la frame suivante. v = v + at
	velocity.addScaledVector(acceleration, duration); 
	//Damping correspond au facteur d'ammortissement (les frottements par exemple dus a la composition du milieu ambiant). Ainsi cette ammortissement agis sur notre vitesse.
	//Car doit ralentir notre objet.
	velocity *= pow(damping, duration); 

	//on nettoie notre accumulateur de force, une force à l'instant t n'est peut etre plus appliquee à t+1
	//clearAccumulator();
}

//Dans la prochaine phase nous viendront accumuler des forces sur un vecteur force qui s'ajouterons et permettrons d'agir sur le comportement de notre particule.
//void Particle::clearAccumulator()
//{
//    forceAccum.clear();
//}
//
////Pour ajouter une nouvelle force a cette accumulateur de force et agir en consequence sur la particule.
//void Particle::addForce(const Vector3D& force)
//{
//	forceAccum += force;
//}
