#include <iostream>
#include <cmath>
#include "HeightMap.h"
#include "Terrain.h"
#include <fstream>
#include <exception>
#include <string>
#include <algorithm>




struct MeshInfo {
	Vector3* verts;
	Vector3* normals;
	unsigned int* tris;

	int vertexCount;
	int triCount;
};

MeshInfo ParseObj(const char* fileName) //à mettre plutot dans la classe qui réprésente une mesh dans le moteur
{
	//Utilisation de vecteurs, car on ne sais pas encore combien d'élements seront à allouer
	//TODO: tester si lire fichier 2 fois est plus rapide
	std::vector<Vector3> verts;
	std::vector<Vector3> normals;
	std::vector<unsigned int> tris;

	std::ifstream objFile(fileName);
	if (!objFile)
		throw std::invalid_argument("bad file");

	std::string lineStart = "";
	while (objFile >> lineStart)
	{
		
		if (lineStart == "v")
		{
			float x, y, z;
			objFile >> x >> y >> z;
			verts.push_back(Vector3{x, y , z});
		}
		else if (lineStart == "vn")
		{
			float x, y, z;
			objFile >> x >> y >> z;
			normals.push_back(Vector3{ x, y , z });
		}
		else if (lineStart == "f")
		{
			unsigned int v1, v2, v3;
			objFile >> v1 >> v2 >> v3;
			tris.push_back(v1);
			tris.push_back(v2);
			tris.push_back(v3);
		}

		objFile.ignore(LLONG_MAX, '\n'); //prochaine ligne
	}

	MeshInfo meshInfo{
		new Vector3[verts.size()],
		new Vector3[normals.size()],
		new unsigned int[tris.size()],
		verts.size(),
		tris.size()
	};

	std::copy(verts.begin(), verts.end(), meshInfo.verts);
	std::copy(normals.begin(), normals.end(), meshInfo.normals);
	std::copy(tris.begin(), tris.end(), meshInfo.tris);

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