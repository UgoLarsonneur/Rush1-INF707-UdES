#pragma once

#include <vector>
#include "HeightMap.h"

struct Vector3 {
	float x;
	float y;
	float z;
};

class Terrain
{
private:
	Vector3* verts;
	Vector3* normals;
	unsigned int* tris;

	int res;

public:

	Terrain(const HeightMap& heightMap, const int& resolution, const float& scaleH, const float& scaleV);

	void setupVerts(const HeightMap& heightMap, const int& resolution, const float& scaleH, const float& scaleV);
	void setupNormals();
	void setupTris();

};