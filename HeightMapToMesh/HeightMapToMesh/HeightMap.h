#pragma once

class HeightMap
{
private:
	unsigned char* data;
	unsigned int sizeX;
	unsigned int sizeY;

public:

	HeightMap(char* file);

	float Sample(const float& x, const float& y);
};