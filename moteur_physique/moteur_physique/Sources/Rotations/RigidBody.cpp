#include "Rotations/RigidBody.h"


void RigidBody::Integrate(float duration) {
	
	//1. Mettre à jour la position : 𝒑 ′ = 𝒑 + 𝒑ሶ𝒕 
	position.addScaledVector(velocity,duration);

	//2. Mettre à jour l’orientation : 
	position.addScaledVector(rotation,duration);

	//3. Calculer les valeurs dérivées(matrice de transformation et 𝛪 −1 ′) 
	CalculateDerivedData();

	//4. Calculer l’accélération linéaire : 𝒑ሷ = 𝟏 𝒎 𝒇 
	linearAcceleration = acceleration;
	linearAcceleration.addScaledVector(m_forceAccum, inverseMasse);

	//5. Calculer l’accélération angulaire : 𝜽ሷ = 𝛪 −1 ′ 𝝉 	
	angularAcceleration = inverseInertiaTensorWorld.transform(m_torqueAccum);

	//6. Mettre à jour la vélocité linéaire : 𝒑ሷ ′ = 𝒑ሶ(𝑑𝑎𝑚𝑝) 𝑡 + 𝒑ሷ𝒕;

	velocity.addScaledVector(linearAcceleration, duration);
	//7. Mettre à jour la vélocité angulaire : 𝜽ሶ ′ = 𝜽ሶ(𝑑𝑎𝑚𝑝) 𝑡 + 𝜽ሷ𝑡;

	rotation.addScaledVector(angularAcceleration, duration);

	//8. Remettre à zéro les accumulateurs(forces et couples).
	clearAccumulator();

}
void  CalculatetransformMatrix(Matrix34& transformMatrix, Vector3D& position, Quaternion& orientation) {

	//on transforme chaque valeur de la matrice avec les valeurs du quaternion d'orientation
	transformMatrix.values[0] = 1 - (2 * orientation.j * orientation.j) - (2 * orientation.k * orientation.k);
	transformMatrix.values[1] = (2 * orientation.i * orientation.j) - (2 * orientation.w * orientation.k);
	transformMatrix.values[2] = (2 * orientation.i * orientation.k) + (2 * orientation.w * orientation.j);
	transformMatrix.values[3] = position.x; 
	transformMatrix.values[4] = 2 * (orientation.i * orientation.j) + (2 * orientation.w * orientation.k);
	transformMatrix.values[5] = 1 - (2 * orientation.i * orientation.i) - (2 * orientation.k * orientation.k);
	transformMatrix.values[6] = (2 * orientation.j * orientation.k) - (2 * orientation.w * orientation.w);
	transformMatrix.values[7] = position.y;
    transformMatrix.values[8] = (2 * orientation.i * orientation.k) - (2 * orientation.w * orientation.j); 
	transformMatrix.values[9] = (2 * orientation.j * orientation.k) + (2 * orientation.w * orientation.w); 
	transformMatrix.values[10] = 1 - (2 * orientation.i * orientation.i) - (2 * orientation.j * orientation.j);
	transformMatrix.values[11] = position.z;
}
void  RigidBody::CalculateDerivedData() {
	
	CalculatetransformMatrix(transformMatrix,  position, orientation);

}

//pas besoin
void  RigidBody::AddForce(const Vector3D& force) {
	
	m_forceAccum += force;
}

//ptet besoin
// a modifier
void  RigidBody::AddForceAtPoint(const Vector3D& force,
	const Vector3D& point)
{
	
	Vector3D point2= point;
	point2 -= position;

	m_forceAccum += force;
	m_torqueAccum += point2 % force;
}
//ptet besoin
//a modifier

void RigidBody::AddForceAtBodyPoint(const Vector3D& force,
	const Vector3D& point)
{

	Vector3D point2 = getPointInWorldSpace(point);
	AddForceAtPoint(force, point2);

}

void RigidBody::clearAccumulator()
{
	
	m_forceAccum.clear();
	m_torqueAccum.clear();

}



Vector3D RigidBody::getPointInWorldSpace(const Vector3D& point) 
{
	return transformMatrix.transform(point);
}

/*Matrix34 RigidBody::getTransform() const
{
	return transformMatrix;
}*/