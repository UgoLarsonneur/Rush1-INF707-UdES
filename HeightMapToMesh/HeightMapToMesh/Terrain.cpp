#include "Terrain.h"

Terrain::Terrain(const HeightMap& heightMap, const unsigned int& _res, const float& scaleH, const float& scaleV, const AspectFitterMode& aspectFitterMode)
	: res(_res)
{
	sommets = new SommetTerrain[res * res];

	//verts = new Vector3[res * res];
	//normals = new Vector3[res * res];
	index = new unsigned int[(res - 1) * (res - 1) * 6];

	setupVerts(heightMap, res, scaleH, scaleV, aspectFitterMode);
	setupNormals();
	setupIndex();
}

/*Terrain::Terrain(const Terrain& other)
{
	//TODO?
}*/

Terrain::~Terrain()
{
	//delete[] verts;
	//delete[] normals;
	delete[] sommets;
	delete[] index;
}

void Terrain::setupVerts(const HeightMap& heightMap, const unsigned int& resolution, const float& scaleH, const float& scaleV, const AspectFitterMode& aspectFitterMode)
{
	float aspect = static_cast<float>(heightMap.getWidth()) / heightMap.getHeight();
	float dX, dY;

	switch (aspectFitterMode)
	{
	case KEEP_WIDTH:
		dX = scaleH;
		dY = scaleH * aspect;
		break;
	case KEEP_HEIGHT:
		dX = scaleH / aspect;
		dY = scaleH;
		break;
	}

	for (unsigned int y = 0; y < res; ++y)
	{
		float tY = static_cast<float>(y) / (res - 1);
		float posY = tY * dX;

		for (unsigned int x = 0; x < res; ++x)
		{
			float tX = static_cast<float>(x) / (res - 1);
			float posX = tX * dY;

			float posZ = (heightMap.Sample(tX, (1.0f-tY)) / 255) * scaleV;

			//verts[x + y * res] = Vector3( posX, posY, posZ );
			sommets[x + y * res].setPos(Vector3(posX, posY, posZ));
			//todo: set uv ?
		}
	}
}

void Terrain::setupNormals()
{
	for (unsigned int y = 0; y < res; ++y)
	{
		for (unsigned int x = 0; x < res; ++x)
		{
			//normals[x + y * res] = calcNormal(x, y);
			sommets[x + y * res].setNormal(calcNormal(x, y));
		}
	}
}

void Terrain::setupIndex()
{
	int k = 0;
	for (unsigned int y = 0; y < res - 1; ++y)
	{
		for (unsigned int x = 0; x < res - 1; ++x)
		{
			index[k++] = y * res + x;
			index[k++] = (y + 1) * res + (x + 1);
			index[k++] = y * res + (x + 1);
			index[k++] = y * res + x;
			index[k++] = (y + 1) * res + x;
			index[k++] = (y + 1) * res + (x + 1);
		}
	}
}

Vector3 Terrain::calcNormal(const unsigned int& x, const unsigned int& y) const
{
	
	Vector3 n1;
	Vector3 n2;
	Vector3 n3;
	Vector3 n4;
	Vector3 v1;
	Vector3 v2;
	Vector3 v3;
	Vector3 v4;

	n1 = n2 = n3 = n4 = Vector3{ 0, 0, 1 }; // Le Z est le haut
	Vector3 ntest = n1 + n2;
	// v1 = p1 – p0, etc...
	if (y < res - 1) v1 = sommets[x + (y + 1) * res].getPos() - sommets[x + y * res].getPos();
	if (x < res - 1) v2 = sommets[x + 1 + y * res].getPos() - sommets[x + y * res].getPos();
	if (y > 0) v3 = sommets[x +(y - 1) * res].getPos() - sommets[x + y * res].getPos();
	if (x > 0) v4 = sommets[x - 1 + y * res].getPos() - sommets[x + y * res].getPos();
	// les produits vectoriels
	if (y < res - 1 && x < res - 1) n1 = produitVectoriel(v2, v1);
	if (y > 0 && x < res - 1) n2 = produitVectoriel(v3, v2);
	if (y > 0 && x > 0) n3 = produitVectoriel(v4, v3);
	if (y < res - 1 && x > 0) n4 = produitVectoriel(v1, v4);
	n1 = n1 + n2 + n3 + n4;
	n1 = n1.getNormalised();
	return n1 * -1;
	

	/*
	XMVECTOR n1;
	XMVECTOR n2;
	XMVECTOR n3;
	XMVECTOR n4;
	XMVECTOR v1;
	XMVECTOR v2;
	XMVECTOR v3;
	XMVECTOR v4;
	n1 = n2 = n3 = n4 = XMVectorSet(0, 0, 1, 0); // Le Z est le haut
	// v1 = p1 – p0, etc...
	if (y < res - 1) v1 = verts[x + (y + 1) * res] - verts[x + y * res];
	if (x < res - 1) v2 = verts[x + 1 + y * res] - verts[x + y * res];
	if (y > 0) v3 = verts[x + (y - 1) * res] - verts[x + y * res];
	if (x > 0) v4 = verts[x - 1 + y * res] - verts[x + y * res];
	// les produits vectoriels
	if (y < res - 1 && x < res - 1) n1 = XMVector3Cross(v2, v1);
	if (y > 0 && x < res - 1) n2 = XMVector3Cross(v3, v2);
	if (y > 0 && x > 0) n3 = XMVector3Cross(v4, v3);
	if (y < res - 1 && x > 0) n4 = XMVector3Cross(v1, v4);
	n1 = n1 + n2 + n3 + n4;
	n1 = XMVector3Normalize(n1);
	XMFLOAT3 resultat;
	XMStoreFloat3(&resultat, n1);
	return {resultat.x, resultat.y, resultat.z};
	*/
}

unsigned int Terrain::getResolution() const
{
	return res;
}

/*
const Vector3* Terrain::getVerts() const
{
	return verts;
}

const Vector3* Terrain::getNormals() const
{
	return normals;
}
*/

const SommetTerrain* Terrain::getSommets() const
{
	return sommets;
}

const unsigned int* Terrain::getIndex() const
{
	return index;
}

std::ostream& operator<<(std::ostream& out, const Terrain& terrain)
{

	size_t vertexCount = terrain.getResolution() * terrain.getResolution();

	//peut être mieux décrire v puis vn puis v puis vn puis...
	out << "# ___VERTEXS___" << '\n';
	for (unsigned int i = 0; i < vertexCount; ++i)
	{
		out << "v " << terrain.getSommets()[i].getPos() << '\n';
	}

	out << '\n' << "# ___NORMALS___" << '\n';
	for (unsigned int i = 0; i < vertexCount; ++i)
	{
		out << "vn " << terrain.getSommets()[i].getNormal() << '\n';
	}

	out << '\n' << "# ___TRIANGLES___" << '\n';
	for (unsigned int i = 0
		; i < (terrain.getResolution() - 1) * (terrain.getResolution() - 1) * 2
		; ++i)
	{
		out << "f "
			<< terrain.getIndex()[i * 3] + 1 << ' '
			<< terrain.getIndex()[i * 3 + 1] + 1 << ' '
			<< terrain.getIndex()[i * 3 + 2] + 1 << ' '
			<< '\n';
	}

	return out;
}
