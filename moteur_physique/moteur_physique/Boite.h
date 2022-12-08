
#include "Primitive.h"


class Boite : public Primitive
{
public:
	Vector3D halfSize;

	/*Vector3D vertices[8] =
	{
		Vector3D{-halfSize.x - halfSize.y -halfSize.z},
		Vector3D{-halfSize.x - halfSize.y + halfSize.z},
		Vector3D{-halfSize.x + halfSize.y - halfSize.z},
		Vector3D{-halfSize.x + halfSize.y + halfSize.z},
		Vector3D{+halfSize.x - halfSize.y - halfSize.z},
		Vector3D{+halfSize.x - halfSize.y + halfSize.z},
		Vector3D{+halfSize.x + halfSize.y - halfSize.z},
		Vector3D{+halfSize.x + halfSize.y + halfSize.z}
	}*/
};