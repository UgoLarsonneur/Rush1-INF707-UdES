#include "HeightMap.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stdb_image.h"

#include <cmath>

HeightMap::HeightMap(char* file)
{
    data = stbi_load(file, &width, &height, NULL, 3);
}

HeightMap::~HeightMap()
{
    stbi_image_free(data);
}


//linéaire
float HeightMap::Sample(const float& _x, const float& _y)
{
    //warp coords
    float x = _x > 1.0f || _x < 0.0f ? std::fmodf(_x, 1.0f) : _x;
    float y = _y > 1.0f || _y < 0.0f ? std::fmodf(_y, 1.0f) : _y;

    unsigned int x1, x2, y1, y2;
    x1 = std::floorf(x * (width  - 1));
    x2 = std::ceilf( x * (width  - 1));
    y1 = std::floorf(y * (height - 1));
    y2 = std::ceilf( y * (height - 1));

    unsigned char s21 = data[(x2 + y1 * width) * 3];
    unsigned char s12 = data[(x1 + y2 * width) * 3];
    unsigned char s11 = data[(x1 + y1 * width) * 3];
    unsigned char s22 = data[(x2 + y2 * width) * 3];
    
    //0-> vers x1, 1 -> vers x2
    float weightX = x * width - x1;
    float weightY = y * height - y1;

    unsigned char raw = data[width + height * width];

    return s11 * (1.0f - weightX) * (1.0f - weightY) +
           s21 * weightX * (1.0f - weightY) +
           s12 * (1.0f - weightX) * weightY +
           s22 * weightX * weightY;

}
