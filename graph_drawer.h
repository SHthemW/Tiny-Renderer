#pragma once
#include "tgaimage.h"
#include <functional>

const TGAColor black = TGAColor(  0,   0,   0, 255);
const TGAColor clear = TGAColor(  0,   0,   0,   0);
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor green = TGAColor(  0, 255,   0, 255);
const TGAColor blue  = TGAColor(  0,   0, 255, 255);
const TGAColor cyan  = TGAColor(255,   0, 255, 255);
const TGAColor red   = TGAColor(255,   0,   0, 255);

static void line(const Vec2i p0, const Vec2i p1, TGAImage& image, const TGAColor color = white, const int resulotion = 10)
{
    const int diff_x = p1.x - p0.x;
    const int diff_y = p1.y - p0.y;
    const int length = std::sqrt((float)std::abs(diff_x) + (float)std::abs(diff_y));

    const float step = 1. / ((float)resulotion * (float)length);

    for (float t = 0.; t < 1; t += step)
    {
        float x = p0.x + t * diff_x;
        float y = p0.y + t * diff_y;
        image.set(x, y, color);
    }
}

static void fillif(const std::function<bool(Vec2i)> condition, TGAImage& image, const std::pair<Vec2i, Vec2i> boundingbox, const TGAColor color = white)
{
    for (int x = boundingbox.first.x; x < boundingbox.second.x; x++)
    {
        for (int y = boundingbox.first.y; y < boundingbox.second.y; y++)
        {
            if (!condition(Vec2i(x, y)))
                continue;
            image.set(x, y, color);
        }
    }
}

static void rasterize2d(Vec2i p0, Vec2i p1, int* ybuffer, const std::size_t ybuffer_size, TGAImage& image, const TGAColor color)
{
    if (p0.x > p1.x)
        std::swap(p0, p1);

    if (p0.x < 0 || p1.x > ybuffer_size)
        throw new std::exception("error: point coordinate out of range.");

    for (int x = p0.x; x < p1.x; x++)
    {
        float t = (x - p0.x) / (float)(p1.x - p0.x);
        int   y = p0.y * (1. - t) + p1.y * t;

        if (ybuffer[x] < y)
        {
            ybuffer[x] = y;
            image.set(x, 1, color);
        }
    }
}

static void rasterize3d(const std::function<bool(Vec2i)> condition, const std::pair<Vec2i, Vec2i> boundingbox, int** zbuffer, TGAImage& image, const TGAColor color)
{
    for (int x = boundingbox.first.x; x < boundingbox.second.x; x++)
    {
        for (int y = boundingbox.first.y; y < boundingbox.second.y; y++)
        {
            if (!condition(Vec2i(x, y)))
                continue;
            
        }
    }
}

const static TGAColor random_color()
{
    return TGAColor(rand() % 255, rand() % 255, rand() % 255, 255);
}

const static TGAColor render_color(const Vec3f normal, const Vec3f light_direction)
{
    // density is 'dot product' of normal and light direction.
    float intensity = 
        (normal.x * light_direction.x + normal.y * light_direction.y + normal.z * light_direction.z)
        / 
        (normal.norm() * light_direction.norm());

    if (intensity >= -1 && intensity <= 0)
    {
        return clear;
    }
    if (intensity >   0 && intensity <= 1)
    {
        int rgb_val = (int)(255 * intensity);
        return TGAColor(rgb_val, rgb_val, rgb_val, 1);
    }
    else 
        throw new std::exception("err: invalid intensity value: %f", intensity);
}