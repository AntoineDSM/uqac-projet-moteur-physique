//Date de création :
//Créer par :
//Date de modification : 
//Modifié par : 

#include "Vector3D.h"
#include "assert.h"

using namespace moteurJeux;

//---------------------------------------------------------------USEFULL METHOD ON VECTOR3D------------------------------------------------------------

//return an orthonormal basis, 3 vectors.
Vector3D::orthonormalBasis createOrthonormalBasis(Vector3D& vect1, Vector3D& vect2)
{
	vect1 = Vector3D::get_normalization(vect1);
	vect2 = Vector3D::get_normalization(vect2);
	Vector3D vect3 = Vector3D::vectorialProduct(vect1, vect2);
	if (!isNULL(vect3))
	{
		vect2 = vectorialProduct(vect1, vect3);
		Vector3D::orthonormalBasis myBase;
		double list[9] = { vect1.x, vect1.y, vect1.z, vect2.x, vect2.y, vect2.z, vect3.x, vect3.y, vect3.z };
		memcpy(myBase.basis, list, sizeof(list));
		return myBase;
	}
}

//-----------------------------------------------------------------OPERATION ON VECTOR3D-----------------------------------------------------

Vector3D Vector3D::vectorialProduct(Vector3D& vect)
{
	return Vector3D(y * vect.z - z * vect.y, z * vect.x - x * vect.z, x * vect.y - y * vect.x);
}

//get vectorial product between 2 specified vectors
static Vector3D vectorialProduct(Vector3D& vect1, Vector3D& vect2)
{
	return Vector3D(vect1.y * vect2.z - vect1.z * vect2.y, vect1.z * vect2.x - vect1.x * vect2.z, vect1.x * vect2.y - vect1.y * vect2.x);
}

//get scalar product between our objet and another vector
double Vector3D::scalarProduct(Vector3D& vect)
{
	return x * vect.x + y * vect.y + z * vect.z;
}

//multiply our Vecteur3D with another one
Vector3D Vector3D::multiplyBy(Vector3D& vect)
{
	return (*this) *= vect;
}

void Vector3D::addScaledVector(const Vector3D& vector, double scale)
{
	x += vector.x * scale;
	y += vector.y * scale;
	z += vector.z * scale;
}

void Vector3D::addMultipliedVector(Vector3D& vect, double facteur)
{
	Vector3D multiplied = vect * facteur;
	(*this) += multiplied;
}

//---------------------------------------------------------------------VERIFICATION ON VECTOR3D--------------------------------------------------

static bool isNULL(Vector3D& vect1)
{
	if (vect1.x == 0)
		if (vect1.y == 0)
			if (vect1.z == 0)
				return true;
	return false;
}

