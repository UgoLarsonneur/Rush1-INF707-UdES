#include "SommetTerrain.h"

SommetTerrain::SommetTerrain()
{
}

SommetTerrain::SommetTerrain(const Vector3& _pos, const Vector3& _normal) : pos(_pos), normal(_normal)
{
}

Vector3 SommetTerrain::getPos() const
{
	return pos;
}

Vector3 SommetTerrain::getNormal() const
{
	return normal;
}

void SommetTerrain::setPos(const Vector3& _pos)
{
	pos = _pos;;
}

void SommetTerrain::setNormal(const Vector3& _normal)
{
	normal = _normal;
}
