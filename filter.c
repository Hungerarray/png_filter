#include <stdio.h>
#include "lodepng.h"
#include "helpers.h"

void blur(Pixel_array *data);

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf ("\nusuage ./filter [imgname] [newname]\n");
        return 1;
    }

    IMG image;
    unsigned err = decodeImg(argv[1], &image);

    if (err)
    {
        printf("error %u: %s\n", err, lodepng_error_text(err));
        return 1;
    }
    
    Pixel_array data;
    GetRGB(&image, &data);
    blur(&data);
    SetRGB(&data, &image);

    err = encodeImg(argv[2], &image);

    if (err)   
    {
        printf ("error %d: %s\n", err, lodepng_error_text(err));
        return 1;
    }
    return 0;
}
