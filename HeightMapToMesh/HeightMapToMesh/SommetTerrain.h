#pragma once

#include "Vector3.h"

class SommetTerrain {
private:
	Vector3 pos;
	Vector3 normal;

public:
	SommetTerrain();
	SommetTerrain(const Vector3& _pos, const Vector3& _normal);

	Vector3 getPos() const;
	Vector3 getNormal() const;

	void setPos(const Vector3& _pos);
	void setNormal(const Vector3& _normal);
};