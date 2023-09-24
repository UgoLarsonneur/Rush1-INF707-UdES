#pragma once

#include <ostream>
#include <vector>
#include "HeightMap.h"
#include "Vector3.h"
#include "SommetTerrain.h"

class Terrain
{
private:

	//Vector3* verts;
	//Vector3* normals;
	//TODO: add uv ?
	SommetTerrain* sommets;
	unsigned int* index;

	unsigned int res;

public:

	
	///Pour garder le ratio largeur/hauteur(de la texture).
	///KEEP_WIDTH pour que la largeur = scaleH et longueur déterminée par la scaleH et le ratio
	///KEEP_HEIGHT pour l'inverse
	enum AspectFitterMode
	{
		KEEP_WIDTH, KEEP_HEIGHT
	};

	Terrain(const HeightMap& heightMap, const unsigned int& resolution, const float& scaleH, const float& scaleV, const AspectFitterMode& aspectFitterMode = KEEP_WIDTH);
	//Terrain(const Terrain& other);
	~Terrain();

	void setupVerts(const HeightMap& heightMap, const unsigned int& resolution, const float& scaleH, const float& scaleV, const AspectFitterMode& aspectFitterMode);
	void setupNormals();
	void setupIndex();

	Vector3 calcNormal(const unsigned int& x, const unsigned int& y) const;

	unsigned int getResolution() const;
	//const Vector3* getVerts() const;
	//const Vector3* getNormals() const;
	const SommetTerrain* getSommets() const;
	const unsigned int* getIndex() const;

};

std::ostream& operator<<(std::ostream& out, const Terrain& terrain);