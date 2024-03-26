#include "tgaimage.h"
#include <stdio.h>
#include <tuple>
#include "model.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const char* output_path = "out/output.tga";

constexpr int gwidth  = 500;
constexpr int gheight = 500;

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

int main(int argc, char** argv)
{
    Model model("resources/african_head.obj");
    TGAImage image(gwidth, gheight, TGAImage::RGB);

    for (int facei = 0; facei < model.nfaces(); facei++)
    {
        std::vector<int> face = model.face(facei);

        for (int veci = 0; veci < 3; veci++) // vec3f has three element (x, y, z)
        {
            Vec3f v0 = model.vert(face[veci]);
            Vec3f v1 = model.vert(face[(veci + 1) % 3]);

            int x0 = (v0.x + 1.) * gwidth  / 2;
            int y0 = (v0.y + 1.) * gheight / 2;
            int x1 = (v1.x + 1.) * gwidth  / 2;
            int y1 = (v1.y + 1.) * gheight / 2;

            line(x0, y0, x1, y1, image, white);
        }
    }

    image.flip_vertically();
    image.write_tga_file(output_path);

    return 0;
}