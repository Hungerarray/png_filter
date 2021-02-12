#include "lodepng.h"
#include "helpers.h"
#include <stdlib.h>

int decodeImg(const char *fn, IMG_P img)
{
    unsigned error = lodepng_decode24_file(&img->image_data, &img->width, &img->height, fn);
    return error;
}

void GetRGB(const IMG_P img, Pixel_array * parray)
{
    parray->height = img->height;
    parray->width = img->width;
    parray->sz = img->width * img->height;
    size_t pos, sz = parray->sz;
    parray->array = (Pixel_P) malloc(img->height * img->width * sizeof(Pixel)); 

    Pixel_P array = parray->array;

    for (pos = 0; pos < sz; ++pos)
    {
        array[pos].r = (unsigned) img->image_data[pos*3];
        array[pos].g = (unsigned) img->image_data[pos*3 + 1];
        array[pos].b = (unsigned) img->image_data[pos*3 + 2];
    }
} 

int encodeImg(const char *fn, const IMG_P img)
{
    unsigned error = lodepng_encode24_file(fn, img->image_data, img->width, img->height);
    return error;
}

void SetRGB(const Pixel_array * parray, IMG_P img)
{
    img->width = parray->width;
    img->height = parray->height;
    for (int i = 0; i < parray->sz; ++i)
    {
        img->image_data[i*3] = (unsigned char) parray->array[i].r;
        img->image_data[i*3 + 1] = (unsigned char) parray->array[i].g;
        img->image_data[i*3 + 2] = (unsigned char) parray->array[i].b;     
    }
}