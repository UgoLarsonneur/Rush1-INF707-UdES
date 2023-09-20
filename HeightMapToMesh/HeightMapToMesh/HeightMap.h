#pragma once

class HeightMap
{
private:
	unsigned char* data;
	int width;
	int height;

public:

	HeightMap(const char* file);
	~HeightMap();

	float Sample(const float& x, const float& y) const;
};