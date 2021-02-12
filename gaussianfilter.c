#include "helpers.h"
#include <stdio.h>
#include <pthread.h>
#include <string.h>

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

Pixel compute_blur(coords start, coords end, const Pixel_array * data)
{
    Pixel new_value = {0,0,0};
    for (int x = start.x; x <= end.x; ++x)
    {
        for (int y = start.y; y <= end.y; ++y)
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

    return new_value;
}

Pixel mid_blur(const Pixel_array *data, size_t pos)
{
    coords curr = posToCoord(data->width, pos), strt = {curr.x - 1, curr.y - 1}, end = {curr.x + 1, curr.y + 1};
    return compute_blur(strt, end, data);
}

Pixel top_blur(const Pixel_array *data, size_t pos)
{

    coords curr = posToCoord(data->width, pos), strt = {curr.x, curr.y - 1}, end = {curr.x + 2, curr.y + 1};

   
    return compute_blur(strt, end, data);
}

Pixel bottom_blur(const Pixel_array *data, size_t pos)
{
    coords curr = posToCoord(data->width, pos), strt = {curr.x - 2, curr.y - 1}, end = {curr.x, curr.y + 1};

    return compute_blur(strt, end, data);
}

Pixel left_blur(const Pixel_array *data, size_t pos)
{
    coords curr = posToCoord(data->width, pos), strt = {curr.x - 1, curr.y}, end = {curr.x + 1, curr.y + 2};

    return compute_blur(strt, end, data);
}

Pixel right_blur(const Pixel_array *data, size_t pos)
{
    coords curr = posToCoord(data->width, pos), strt = {curr.x - 1, curr.y - 2}, end = {curr.x + 1, curr.y};

    return compute_blur(strt, end, data);
}

Pixel top_right_blur(const Pixel_array *data, size_t pos)
{
    coords curr = posToCoord(data->width, pos), strt = {curr.x, curr.y - 2}, end = {curr.x + 2, curr.y};

    return compute_blur(strt, end, data);
}

Pixel top_left_blur(const Pixel_array *data, size_t pos)
{
    coords curr = posToCoord(data->width, pos), strt = {curr.x, curr.y}, end = {curr.x + 2, curr.y + 2};

    return compute_blur(strt, end, data);
}

Pixel bottom_left_blur(const Pixel_array *data, size_t pos)
{
    coords curr = posToCoord(data->width, pos), strt = {curr.x - 2, curr.y}, end = {curr.x, curr.y + 2};

    return compute_blur(strt, end, data);
}

Pixel bottom_right_blur(const Pixel_array *data, size_t pos)
{
    coords curr = posToCoord(data->width, pos), strt = {curr.x, curr.y - 1}, end = {curr.x + 2, curr.y + 1};

    return compute_blur(strt, end, data);
}
/* 
void blur(Pixel_array *data)
{
    size_t width = data->width;
    Pixel_P new_data = (Pixel_P) malloc(data->sz*sizeof(Pixel));

    for (int i = 0; i < data->sz; ++i)
    {
        printf("%d of %lu pixels done.\n", i + 1, data->sz);
        if (i % width == 0)
        {
            if (i / width == 0)
            {
                new_data[i] = top_left_blur(data, i);
                continue;
            }
            else if (i / width == width - 1)
            {
                new_data[i] = bottom_left_blur(data, i);
                continue;
            }
            else
            {
                new_data[i] = left_blur(data, i);
                continue;
            }
        }
        else if (i % width == width - 1)
        {
            if (i / width == 0)
            {
                new_data[i] = top_right_blur(data, i);
                continue;
            }
            else if (i / width == width - 1)
            {
                new_data[i] = bottom_right_blur(data, i);
                continue;
            }
            else
            {
                new_data[i] = right_blur(data, i);
                continue;
            }
        }
        else if (i / width == 0)
        {
            new_data[i] = top_blur(data, i);
            continue;
        }
        else if (i / width == width - 1)
        {
            new_data[i] = bottom_blur(data, i);
            continue;
        }
    }
    //free(data->array);
    data->array = new_data;
} */

Pixel do_blur(const Pixel_array * data, size_t pos)
{
    size_t width = data->width;
    if (pos % width == 0)
    {
        if (pos / width == 0)
            return top_left_blur(data, pos);
        else if ( pos / width == width - 1)
            return bottom_left_blur(data, pos);
        else
            return left_blur(data, pos);
    }
    else if (pos % width == width - 1)
    {
        if (pos / width == 0)
            return top_right_blur(data, pos);
        else if (pos / width == width - 1)  
            return bottom_right_blur(data,pos);
        else
            return right_blur(data, pos);
    }
    else if (pos / width == 0)
        return top_blur(data, pos);
    else if (pos / width == width - 1)
        return bottom_blur(data, pos);
    else
        return mid_blur(data, pos);
}

typedef struct thread_data
{
    const Pixel_array * data;
    Pixel_P *part;
    size_t start;
    size_t end;
} thread_data;

void * blur_par_sup(void * arg)
{
    static int gen_id = 1;
    int thread_id = gen_id++;
    const Pixel_array * data = ((thread_data *) arg)->data;
    Pixel_P *part = ((thread_data *) arg)->part;
    size_t strt = ((thread_data *) arg)->start, end = ((thread_data *) arg)->end;

    *part = (Pixel_P) malloc((end - strt) * sizeof(Pixel));

    for (int i = strt; i < end; ++i)
    {
        (*part)[i - strt] = do_blur(data, i);
    }
    printf("\nthread no. %d is done\n", thread_id);

    return NULL ;
}

void blur_parallel(Pixel_array *data)
{
    // divide data into n segments
    unsigned noSegments = 8;
    size_t sz_segment = data->sz / noSegments;
    Pixel_P * parts = (Pixel_P * ) malloc(noSegments * sizeof(Pixel_P));

    // create a thread for each segment which blurs it individually
    pthread_t * threads = (pthread_t *) malloc(noSegments * sizeof(pthread_t));
    thread_data **t_data = (thread_data **) malloc(noSegments * sizeof(thread_data *));

    for (int i = 0; i < noSegments; ++i)
    {
        t_data[i] = (thread_data *) malloc(sizeof(thread_data));
        t_data[i]->data = data;
        t_data[i]->part = &parts[i];
        t_data[i]->start = i * sz_segment;
        t_data[i]->end = (i + 1) * sz_segment;
        if ( i == noSegments - 1)
        {
            t_data[i]->end = data->sz;
            pthread_create(threads + i, NULL, blur_par_sup,(void *) &t_data[i]);
        }   
        else
            pthread_create(threads + i, NULL, blur_par_sup,(void *) &t_data[i]);
    }

    for (int i = 0; i < noSegments; ++i)
    {
        pthread_join(threads[i], NULL);
    }
    // combine all the data the end
    // replace the data
    for (int i = 0; i < data->sz; ++i)
    {
        data->array[i] = parts[i / sz_segment][i % sz_segment];
    }

 /*    // clean
    for (int i = 0; i < noSegments; ++i)
    {
        free(t_data[i]);
        free(parts[i]);
    }
    free(parts);
    free(threads);
    free(t_data); */
} 
