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