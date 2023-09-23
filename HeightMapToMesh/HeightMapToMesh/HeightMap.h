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

	int getWidth() const;
	int getHeight() const;

	float Sample(const float& x, const float& y) const;
};