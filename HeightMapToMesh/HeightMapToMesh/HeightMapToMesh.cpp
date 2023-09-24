#include "HeightMap.h"
#include "Terrain.h"
#include "SommetTerrain.h"

#include <iostream>
#include <fstream>
#include <exception>
#include <string>
#include <algorithm>



struct MeshInfo {
	SommetTerrain* sommets;
	unsigned int* index;

	int vertexCount;
	int triCount;
};

//Retourne les informations lues. 
MeshInfo ParseObj(const char* fileName) 
{
	//Utilisation de vecteurs, car on ne sais pas encore combien d'élements seront à allouer
	//TODO: tester si lire fichier 2 fois est plus rapide
	std::vector<Vector3> posVec;
	std::vector<Vector3> normalsVec;
	std::vector<unsigned int> indexVec;

	std::ifstream objFile(fileName);
	if (!objFile)
		throw std::invalid_argument("bad file");

	std::string lineStart = "";
	while (objFile >> lineStart) //lecture du fichier
	{
		
		if (lineStart == "v")
		{
			float x, y, z;
			objFile >> x >> y >> z;
			posVec.push_back(Vector3{x, y , z});
		}
		else if (lineStart == "vn")
		{
			float x, y, z;
			objFile >> x >> y >> z;
			normalsVec.push_back(Vector3{ x, y , z });
		}
		else if (lineStart == "f")
		{
			unsigned int v1, v2, v3;
			objFile >> v1 >> v2 >> v3;
			indexVec.push_back(v1);
			indexVec.push_back(v2);
			indexVec.push_back(v3);
		}

		objFile.ignore(LLONG_MAX, '\n'); //prochaine ligne
	}

	//Creation du tableu de sommet (erreur si il n'y a pas autant de normales que de sommets...)
	SommetTerrain* sommets = new SommetTerrain[posVec.size()];
	for (size_t i = 0; i < posVec.size(); i++)
	{
		sommets[i].setPos(posVec[i]);
		sommets[i].setNormal(normalsVec[i]);
	}

	unsigned int* index = new unsigned int[indexVec.size()];
	std::copy(indexVec.begin(), indexVec.end(), index);
	
	MeshInfo meshInfo {
		sommets,
		index,
		posVec.size(),
		indexVec.size()
	};

	//std::copy(verts.begin(), verts.end(), meshInfo.pos);
	//std::copy(normals.begin(), normals.end(), meshInfo.normals);

	return meshInfo;
}


int main(const int argc, const char** argv)
{
	if (argc < 3 || argc > 4)
	{
		std::cerr << "Usage: HeightMapToMesh <source image> <vertex resolution> [destination]" << std::endl;
		return -1;
	}

	HeightMap hmap(argv[1]);
	
	unsigned int res = std::atoi(argv[2]);
	Terrain terrain(hmap, res, 10, 1.5f);

	const char* filename = argc == 4 ? argv[3] : "out.obj";
	std::ofstream os(filename);

	os << terrain;
	os.close();

	ParseObj(filename);

	return 0;
}