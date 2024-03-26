#pragma once
#include "tgaimage.h"
#include <functional>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor green = TGAColor(0  , 255,   0, 255);
const TGAColor red   = TGAColor(255,   0,   0, 255);
const TGAColor random_color()
{
    return TGAColor(rand() % 255, rand() % 255, rand() % 255, 255);
}

static void line(const int x0, const int y0, const int x1, const int y1, TGAImage& image, const TGAColor color = white, const int resulotion = 10)
{
    const int diff_x = x1 - x0;
    const int diff_y = y1 - y0;
    const int length = std::sqrt((float)std::abs(diff_x) + (float)std::abs(diff_y));

    const float step = 1. / ((float)resulotion * (float)length);

    for (float t = 0.; t < 1; t += step)
    {
        float x = x0 + t * diff_x;
        float y = y0 + t * diff_y;
        image.set(x, y, color);
    }
}

static void fillif(std::function<bool(Vec2i)> condition, TGAImage& image, const TGAColor color = white)
{
    for (int x = 0; x < image.get_width(); x++)
    {
        for (int y = 0; y < image.get_height(); y++)
        {
            if (!condition(Vec2i(x, y)))
                continue;
            image.set(x, y, color);
        }
    }
}