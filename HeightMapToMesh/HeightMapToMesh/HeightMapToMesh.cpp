#include <iostream>
#include <cmath>
#include "HeightMap.h"
#include "Terrain.h"

const int res = 50;

const float scale = 10;

struct Vector3 {
	float x;
	float y;
	float z;
};

int main(const int argc, const char** argv)
{
	const char* fileName;

	if (argc != 2)
	{
		std::cerr << "Usage: HeightMapToMesh <source image>" << std::endl;
		return -1;
	}

	HeightMap hmap(argv[1]);

	Terrain(hmap, 100, 10, 2);
	

	float x = 0.54848;
	float y = 0.31781;
	float test = hmap.Sample(x, y);
	std::cout << test << std::endl;


	return 0;
}