#include "helpers.h"
#include <stdio.h>

typedef struct coords
{
    size_t x;
    size_t y;
} coords;

coords posToCoord(size_t width, size_t pos)
{
    coords coords = {pos % width, pos / width};
    return coords;
}

size_t CoordToPos(size_t width, coords coords)
{
    return coords.y * width + coords.x;
}

void mid_blur(Pixel_array *data, size_t pos)
{
    Pixel new_value = {0, 0, 0};
    coords cord = posToCoord(data->width, pos);

    for (int x = cord.x - 1; x <= cord.x + 1; ++x)
    {
        for (int y = cord.y - 1; y <= cord.y + 1; ++y)
        {
            coords c = {x, y};
            new_value.r += data->array[CoordToPos(data->width, c)].r;
            new_value.g += data->array[CoordToPos(data->width, c)].g;
            new_value.b += data->array[CoordToPos(data->width, c)].b;
        }
    }

    new_value.r /= 9;
    new_value.g /= 9;
    new_value.b /= 9;

    data->array[pos] = new_value;
}

void top_blur(Pixel_array *data, size_t pos)
{
    Pixel new_value = {0, 0, 0};
    coords curr = posToCoord(data->width, pos);

    for (int x = curr.x; x <= curr.x + 2; ++x)
    {
        for (int y = curr.y - 1; y <= curr.y + 1; ++y)
        {
            coords c = {x, y};

            new_value.r += data->array[CoordToPos(data->width, c)].r;
            new_value.g += data->array[CoordToPos(data->width, c)].g;
            new_value.b += data->array[CoordToPos(data->width, c)].b;
        }
    }
    new_value.r /= 9;
    new_value.g /= 9;
    new_value.b /= 9;

    data->array[pos] = new_value;
}

void bottom_blur(Pixel_array *data, size_t pos)
{
    Pixel new_value = {0, 0, 0};
    coords curr = posToCoord(data->width, pos);

    for (int x = curr.x - 2; x <= curr.x; ++x)
    {
        for (int y = curr.y - 1; y <= curr.y + 1; ++y)
        {
            coords c = {x, y};

            new_value.r += data->array[CoordToPos(data->width, c)].r;
            new_value.g += data->array[CoordToPos(data->width, c)].g;
            new_value.b += data->array[CoordToPos(data->width, c)].b;
        }
    }
    new_value.r /= 9;
    new_value.g /= 9;
    new_value.b /= 9;

    data->array[pos] = new_value;
}

void left_blur(Pixel_array *data, size_t pos)
{
    Pixel new_value = {0, 0, 0};
    coords curr = posToCoord(data->width, pos);

    for (int x = curr.x - 1; x <= curr.x + 1; ++x)
    {
        for (int y = curr.y; y <= curr.y + 2; ++y)
        {
            coords c = {x, y};

            new_value.r += data->array[CoordToPos(data->width, c)].r;
            new_value.g += data->array[CoordToPos(data->width, c)].g;
            new_value.b += data->array[CoordToPos(data->width, c)].b;
        }
    }
    new_value.r /= 9;
    new_value.g /= 9;
    new_value.b /= 9;

    data->array[pos] = new_value;
}

void right_blur(Pixel_array *data, size_t pos)
{
    Pixel new_value = {0, 0, 0};
    coords curr = posToCoord(data->width, pos);

    for (int x = curr.x - 1; x <= curr.x + 1; ++x)
    {
        for (int y = curr.y - 2; y <= curr.y; ++y)
        {
            coords c = {x, y};

            new_value.r += data->array[CoordToPos(data->width, c)].r;
            new_value.g += data->array[CoordToPos(data->width, c)].g;
            new_value.b += data->array[CoordToPos(data->width, c)].b;
        }
    }
    new_value.r /= 9;
    new_value.g /= 9;
    new_value.b /= 9;

    data->array[pos] = new_value;
}

void top_right_blur(Pixel_array *data, size_t pos)
{
    Pixel new_value = {0, 0, 0};
    coords curr = posToCoord(data->width, pos);

    for (int x = curr.x; x <= curr.x + 2; ++x)
    {
        for (int y = curr.y - 2; y <= curr.y; ++y)
        {
            coords c = {x, y};

            new_value.r += data->array[CoordToPos(data->width, c)].r;
            new_value.g += data->array[CoordToPos(data->width, c)].g;
            new_value.b += data->array[CoordToPos(data->width, c)].b;
        }
    }
    new_value.r /= 9;
    new_value.g /= 9;
    new_value.b /= 9;

    data->array[pos] = new_value;
}

void top_left_blur(Pixel_array *data, size_t pos)
{
    Pixel new_value = {0, 0, 0};
    coords curr = posToCoord(data->width, pos);

    for (int x = curr.x; x <= curr.x + 2; ++x)
    {
        for (int y = curr.y; y <= curr.y + 2; ++y)
        {
            coords c = {x, y};

            new_value.r += data->array[CoordToPos(data->width, c)].r;
            new_value.g += data->array[CoordToPos(data->width, c)].g;
            new_value.b += data->array[CoordToPos(data->width, c)].b;
        }
    }
    new_value.r /= 9;
    new_value.g /= 9;
    new_value.b /= 9;

    data->array[pos] = new_value;
}

void bottom_left_blur(Pixel_array *data, size_t pos)
{
    Pixel new_value = {0, 0, 0};
    coords curr = posToCoord(data->width, pos);

    for (int x = curr.x - 2; x <= curr.x; ++x)
    {
        for (int y = curr.y; y <= curr.y + 2; ++y)
        {
            coords c = {x, y};

            new_value.r += data->array[CoordToPos(data->width, c)].r;
            new_value.g += data->array[CoordToPos(data->width, c)].g;
            new_value.b += data->array[CoordToPos(data->width, c)].b;
        }
    }
    new_value.r /= 9;
    new_value.g /= 9;
    new_value.b /= 9;

    data->array[pos] = new_value;
}

void bottom_right_blur(Pixel_array *data, size_t pos)
{
    Pixel new_value = {0, 0, 0};
    coords curr = posToCoord(data->width, pos);

    for (int x = curr.x - 2; x <= curr.x; ++x)
    {
        for (int y = curr.y - 2; y <= curr.y; ++y)
        {
            coords c = {x, y};

            new_value.r += data->array[CoordToPos(data->width, c)].r;
            new_value.g += data->array[CoordToPos(data->width, c)].g;
            new_value.b += data->array[CoordToPos(data->width, c)].b;
        }
    }
    new_value.r /= 9;
    new_value.g /= 9;
    new_value.b /= 9;

    data->array[pos] = new_value;
}

void blur(Pixel_array *data)
{
    size_t width = data->width;
    for (int i = 0; i < data->sz; ++i)
    {
        if (i % width == 0)
        {
            if (i / width == 0)
            {
                top_left_blur(data, i);
                continue;
            }
            else if (i / width == width - 1)
            {
                bottom_left_blur(data, i);
                continue;
            }
            else
            {
                left_blur(data, i);
                continue;
            }
        }
        else if (i % width == width - 1)
        {
            if (i / width == 0)
            {
                top_right_blur(data, i);
                continue;
            }
            else if (i / width == width - 1)
            {
                bottom_right_blur(data, i);
                continue;
            }
            else
            {
                right_blur(data, i);
                continue;
            }
        }
        else if (i / width == 0)
        {
            top_blur(data, i);
            continue;
        }
        else if (i / width == width - 1)
        {
            bottom_blur(data, i);
            continue;
        }
        printf("%d of %lu pixels done.\n", i + 1, data->sz);
    }
}