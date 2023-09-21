#pragma once

#include <ostream>
#include <vector>
#include "HeightMap.h"
#include "Vector3.h"

class Terrain
{
private:
	Vector3* verts;
	Vector3* normals;
	unsigned int* tris;

	unsigned int res;

public:

	Terrain(const HeightMap& heightMap, const unsigned int& resolution, const float& scaleH, const float& scaleV);
	Terrain(const Terrain& other);
	~Terrain();

	void setupVerts(const HeightMap& heightMap, const unsigned int& resolution, const float& scaleH, const float& scaleV);
	void setupNormals();
	void setupTris();

	Vector3 calcNormal(const unsigned int& x, const unsigned int& y) const;

	unsigned int getResolution() const;
	const Vector3* getVerts() const;
	const Vector3* getNormals() const;
	const unsigned int* getTris() const;

};

std::ostream& operator<<(std::ostream& out, const Terrain& terrain);