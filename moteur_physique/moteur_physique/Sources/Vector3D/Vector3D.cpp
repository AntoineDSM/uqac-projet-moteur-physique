//Date de création :
//Créer par :
//Date de modification : 
//Modifié par : 

#include <iostream>
#include "assert.h"
#include "Vector3D/Vector3D.h"

using namespace moteurJeux;

//---------------------------------------------------------------USEFULL METHOD ON VECTOR3D------------------------------------------------------------

//Retour d'une base orthonormee, sera utile lors de la gestion des collisions par exemple.
Vector3D::orthonormalBasis createOrthonormalBasis(Vector3D& vect1, Vector3D& vect2)
{
	//On normalise nos deux vecteurs.
	vect1 = Vector3D::get_normalization(vect1);
	vect2 = Vector3D::get_normalization(vect2);
	//On effectue le produit vectoriel entre les deux, ce qui nous donne un vecteur orthogonal au deux autres.
	Vector3D vect3 = Vector3D::vectorialProduct(vect1, vect2);
	//Si le resultat de ce produit vectoriel est de 0, les deux vecteurs etaient parallele, impossible de construire une base orthonomee a partir des deux initiaux.
	if (!Vector3D::isNULL(vect3))
	{
		//Nous modifion un des deux vecteurs initiaux, en effet le 3eme est orthogonal au deux premiers, mais les deux premiers entre eux ne le sont pas.
		vect2 = Vector3D::vectorialProduct(vect1, vect3);
		Vector3D::orthonormalBasis myBase;
		//Nous avons nos coordonnees de chacun des trois vecteurs pour construire notre base. Possibilite de retourner un std::vector<Vector3D>(3) plutot que la liste des coordonees. 
		double list[9] = { vect1.x, vect1.y, vect1.z, vect2.x, vect2.y, vect2.z, vect3.x, vect3.y, vect3.z };
		memcpy(myBase.basis, list, sizeof(list));
		return myBase;
	}
	else//Si le produit vectoriel est null.
		std::cout << "Theses vector are parallel, creating a basis is impossible\n";
}

//-----------------------------------------------------------------OPERATION ON VECTOR3D-----------------------------------------------------

Vector3D Vector3D::vectorialProduct(Vector3D& vect)
{
	return Vector3D(y * vect.z - z * vect.y, z * vect.x - x * vect.z, x * vect.y - y * vect.x);
}

//obtenir le produit scalaire entre le vecteur actuel et un second.
<<<<<<< HEAD
double Vector3D::scalarProduct(const Vector3D& vect)
=======
double Vector3D::scalarProduct(Vector3D& vect)
>>>>>>> origin/Victor
{
	return x * vect.x + y * vect.y + z * vect.z;
}

//obtenir la multiplication entre notre vecteur et un second.
Vector3D Vector3D::multiplyBy(Vector3D& vect)
{
	return (*this) *= vect;
}

//ajouter un vecteur multiplie par un facteur. Utile lors de l'evolution de la position et de la vitesse (pos = pos + vit*t & vit = vit + acc*t).
void Vector3D::addScaledVector(const Vector3D& vector, double scale)
{
	x += vector.x * scale;
	y += vector.y * scale;
	z += vector.z * scale;
}

//Meme methode que addScaledVector() mais implementation differente.
void Vector3D::addMultipliedVector(Vector3D& vect, double facteur)
{
	Vector3D multiplied = vect * facteur;
	(*this) += multiplied;
}

//---------------------------------------------------------------------VERIFICATION ON VECTOR3D--------------------------------------------------

