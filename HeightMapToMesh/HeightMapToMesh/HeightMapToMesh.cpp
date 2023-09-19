

#include <iostream>
#include <cmath>
#include "HeightMap.h"

int main(int argc, char** argv)
{
	HeightMap hmap(argv[1]);
	std::cout << hmap.Sample(0.5f, 0.87998f) << std::endl;
}