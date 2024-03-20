#include "tgaimage.h"
#include <stdio.h>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const char* output_path = "out/point.tga";

void point(int x, int y, TGAImage& image, TGAColor color)
{
    image.set(x, y, color);
    image.flip_vertically();
    image.write_tga_file(output_path);
}

int main()
{
    printf("begin...\n");

    TGAImage image(100, 100, TGAImage::RGB);
    point(50, 50, image, red);

    printf("ok.");
    return 0;
}