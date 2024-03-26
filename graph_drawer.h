#pragma once
#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

static void point(const int x, const int y, TGAImage& image, const TGAColor color)
{
    image.set(x, y, color);
}

static void line(const int x0, const int y0, const int x1, const int y1, TGAImage& image, const TGAColor color, const int resulotion = 100)
{
    const float step = 1. / (float)resulotion;

    for (float t = 0.; t < 1; t += step)
    {
        float x = x0 + t * (x1 - x0);
        float y = y0 + t * (y1 - y0);
        image.set(x, y, color);
    }
}