#pragma once
#include <stdlib.h>
#include <limits.h>


typedef struct pixel
{
    unsigned r;
    unsigned g;
    unsigned b;
} Pixel;

typedef Pixel * Pixel_P;

typedef struct Pixel_array
{
    Pixel_P array;
    size_t width;
    size_t height;
    size_t sz;
}Pixel_array;

typedef struct image
{
    unsigned width;
    unsigned height;
    unsigned char *image_data;
} IMG;
typedef IMG * IMG_P;
typedef IMG_P * IMG_PP;

int decodeImg(const char *filename, IMG_P image);
int encodeImg(const char *filename, const IMG_P image);
void GetRGB(const IMG_P img, Pixel_array * pixel_data);
void SetRGB(const Pixel_array * parray, IMG_P img);