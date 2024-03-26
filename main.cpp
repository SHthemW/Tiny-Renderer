#include <stdio.h>
#include <tuple>
#include "model.h"
#include "graph_drawer.h"

const char* output_path = "out/output.tga";

int gwidth  = 500;
int gheight = 500;
int scale_ratio = 250;



static void draw_african_head_line(Model model, TGAImage& image)
{
    if (scale_ratio > gwidth / 2 || scale_ratio > gheight / 2)
        printf("warning: too large scale_ratio: %d", scale_ratio);

    for (int facei = 0; facei < model.nfaces(); facei++)
    {
        std::vector<int> face = model.face(facei);

        for (int veci = 0; veci < 3; veci++) // vec3f has three element (x, y, z)
        {
            Vec3f v0 = model.vert(face[veci]);
            Vec3f v1 = model.vert(face[(veci + 1) % 3]);

            // map coordinates
            int x0 = (v0.x + 1.) * scale_ratio;
            int y0 = (v0.y + 1.) * scale_ratio;
            int x1 = (v1.x + 1.) * scale_ratio;
            int y1 = (v1.y + 1.) * scale_ratio;

            line(x0, y0, x1, y1, image, white);
        }
    }
}


int main(int argc, char** argv)
{
    Model model("resources/african_head.obj");
    TGAImage image(gwidth, gheight, TGAImage::RGB);

    draw_african_head_line(model, image);

    image.flip_vertically();
    image.write_tga_file(output_path);

    return 0;
}