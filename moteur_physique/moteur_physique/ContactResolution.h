

#include "Sphere.h"
#include "Plan.h"
#include "Boite.h"
#include "Vecteur3D.h"

class ContactResolutions {

public:
	void CollisionSphereSphere(Sphere& sphere1, Sphere& sphere2) {}

	void CollisionSpherePlan(Sphere& sphere, Plan& plan) {}

	void CollisionBoitePlan(const Boite& boite, const Plan& plan) {}

	void CollisionBoiteSphere(const Sphere& sphere, const Boite& boite) {}

	void CollisionBoiteBoite(const Boite& boite1, const Boite& boite2) {}
};