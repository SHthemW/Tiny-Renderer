#include "tgaimage.h"
#include <stdio.h>
#include <tuple>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const char* output_path = "out/output.tga";

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

int main()
{
    printf("begin...\n");
    TGAImage image(100, 100, TGAImage::RGB);

    line(13, 20, 80, 40, image, white);
    line(20, 13, 40, 80, image, red);
    line(80, 40, 13, 20, image, red);

    image.flip_vertically();
    image.write_tga_file(output_path);
    printf("ok.");
    return 0;
}