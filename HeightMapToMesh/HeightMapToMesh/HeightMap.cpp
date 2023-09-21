#include "HeightMap.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stdb_image.h"

#include <cmath>

HeightMap::HeightMap(const char* file)
{
    data = stbi_load(file, &width, &height, NULL, 1);
}

HeightMap::~HeightMap()
{
    stbi_image_free(data);
}


//bilinéaire
float HeightMap::Sample(const float& _x, const float& _y) const
{
    //warp coords
    float x = _x > 1.0f || _x < 0.0f ? std::fmodf(_x, 1.0f) : _x;
    float y = _y > 1.0f || _y < 0.0f ? std::fmodf(_y, 1.0f) : _y;

    unsigned int x1, x2, y1, y2;
    x1 = static_cast<unsigned int>(std::floorf(x * (width  - 1)));
    x2 = static_cast<unsigned int>(std::ceilf( x * (width  - 1)));
    y1 = static_cast<unsigned int>(std::floorf(y * (height - 1)));
    y2 = static_cast<unsigned int>(std::ceilf( y * (height - 1)));

    //     x1      x2
    //  y1 * ----- *
    //     | point |  <- une valeure de pixel par *
    //     |   *   |
    //  y2 * ----- *
    //
    
    unsigned char s11 = data[(x1 + y1 * width)];
    unsigned char s21 = data[(x2 + y1 * width)];
    unsigned char s12 = data[(x1 + y2 * width)];
    unsigned char s22 = data[(x2 + y2 * width)];
    
    float weightX = x * width - x1; //0-> vers x1, 1 -> vers x2
    float weightY = y * height - y1;

    return s11 * (1.0f - weightX) * (1.0f - weightY) +
           s21 * weightX * (1.0f - weightY) +
           s12 * (1.0f - weightX) * weightY +
           s22 * weightX * weightY;

}
