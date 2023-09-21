#include <iostream>
#include <cmath>
#include "HeightMap.h"
#include "Terrain.h"
#include <fstream>


int main(const int argc, const char** argv)
{
	if (argc < 3 || argc > 4)
	{
		std::cerr << "Usage: HeightMapToMesh <source image> <vertex resolution> [destination]" << std::endl;
		return -1;
	}


	HeightMap hmap(argv[1]);

	float x = 0.54848f;
	float y = 0.31781f;
	float test = hmap.Sample(x, y);
	std::cout << test << std::endl;
	
	unsigned int res = std::atoi(argv[2]);
	Terrain terrain(hmap, res, 10, 2);

	const char* filename = argc == 4 ? argv[3] : "out.obj";
	std::ofstream os(filename);


	os << terrain;

	os.close();

	return 0;
}