

#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stdb_image.h"

//TODO: enlever ça :)
// Standard parameters:
//    int *x                 -- outputs image width in pixels
//    int *y                 -- outputs image height in pixels
//    int *channels_in_file  -- outputs # of image components in image file
//    int desired_channels   -- if non-zero, # of image components requested in result
//
// The return value from an image loader is an 'unsigned char *' which points
// to the pixel data, or NULL on an allocation failure or if the image is
// corrupt or invalid. The pixel data consists of *y scanlines of *x pixels,
// with each pixel consisting of N interleaved 8-bit components; the first
// pixel pointed to is top-left-most in the image. There is no padding between
// image scanlines or between pixels, regardless of format. The number of
// components N is 'desired_channels' if desired_channels is non-zero, or
// *channels_in_file otherwise. If desired_channels is non-zero,
// *channels_in_file has the number of components that _would_ have been
// output otherwise. E.g. if you set desired_channels to 4, you will always
// get RGBA output, but you can check *channels_in_file to see if it's trivially
// opaque because e.g. there were only 3 channels in the source image.

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: HeightMapToMesh <Filename>" << std::endl;
        return -1;
    }

    int x, y, n;
    unsigned char* data = stbi_load(argv[1], &x, &y, &n, 3);
    unsigned char r = data[0];
    unsigned char g = data[1];
    unsigned char b = data[2];

    stbi_image_free(data);
}