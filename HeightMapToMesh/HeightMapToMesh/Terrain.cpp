#include "Terrain.h"

Terrain::Terrain(const HeightMap& heightMap, const int& _res, const float& scaleH, const float& scaleV) : res(_res)
{
	verts = new Vector3[res * res];
	normals = new Vector3[res * res];
	tris = new unsigned int[(res - 1) * (res - 1) * 6];
}

void Terrain::setupVerts(const HeightMap& heightMap, const int& resolution, const float& scaleH, const float& scaleV)
{
	for (size_t y = 0; y < res; ++y)
	{
		float tY = static_cast<float>(y) / (res - 1);
		float posY = tY * scaleH;

		for (size_t x = 0; x < res; ++x)
		{
			float tX = static_cast<float>(x) / (res - 1);
			float posX = tX * scaleH;

			float posZ = (heightMap.Sample(tX, tY) / 255) * scaleV;

			verts[x + y * res] = Vector3{ posX, posY, posZ };
			//todo: set uv ?
		}
	}
}

void Terrain::setupNormals()
{
	for (size_t y = 0; y < res; ++y)
	{
		for (size_t x = 0; x < res; ++x)
		{
			normals[x + y * res] = Vector3{ 0, 0, 1 };
		}
	}
}

void Terrain::setupTris()
{
	int k = 0;
	for (int y = 0; y < res - 1; ++y)
	{
		for (int x = 0; x < res - 1; ++x)
		{
			tris[k++] = y * res + x;
			tris[k++] = (y + 1) * res + (x + 1);
			tris[k++] = y * res + (x + 1);
			tris[k++] = y * res + x;
			tris[k++] = (y + 1) * res + x;
			tris[k++] = (y + 1) * res + (x + 1);
		}
	}
}
