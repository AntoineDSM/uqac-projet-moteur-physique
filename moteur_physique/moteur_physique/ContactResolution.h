

#include "Sphere.h"
#include "Plan.h"
#include "Boite.h"
#include "Vector3D/Vector3D.h"
#include "CollisionData.h"

class ContactResolutions {

public:
	//Methode resolveContacts()

	static int CollisionSphereSphere(Sphere& sphere1, Sphere& sphere2, CollisionData* data) {}

	static int CollisionSpherePlan(Sphere& sphere, Plan& plan, CollisionData* data) {}

	static int CollisionBoitePlan(const Boite& boite, const Plan& plan, CollisionData* data) {}

	static int CollisionBoiteSphere(const Sphere& sphere, const Boite& boite, CollisionData* data) {}

	static int CollisionBoiteBoite(const Boite& boite1, const Boite& boite2, CollisionData* data) {}
};