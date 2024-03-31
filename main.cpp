#include <stdio.h>
#include <cstdlib>
#include "model.h"
#include "graph_drawer.h"
#include "shape.h"

constexpr int gwidth  = 500;
constexpr int gheight = 500;
constexpr int scale_ratio = 250;

Vec3f global_light_direction(0, 0, -1);

static void draw_triangle(Triangle2D todraw, Triangle3D referance, int** zbuffer, TGAImage& image, TGAColor color, bool fill, bool edge, bool debug)
{
    if (!edge && !fill)
        printf("warning: triangle has neither edge nor solid fill. you may cannot see anything on output.");

    if (edge)
    {
        line(todraw.get_point1(), todraw.get_point2(), image, color);
        line(todraw.get_point2(), todraw.get_point3(), image, color);
        line(todraw.get_point3(), todraw.get_point1(), image, color);
    }

    if (fill)
        fillif(
            [=, &image](Vec2i coord) -> bool
            { 
                if (!todraw.inside(coord))
                    return false;

                // apply zbuffer
                Vec3f p(coord.x, coord.y, 0);
                Vec3f bc_screen = referance.barycentric(p);

                p.z = referance.get_point1().z * bc_screen.x
                    + referance.get_point2().z * bc_screen.y
                    + referance.get_point3().z * bc_screen.z;

                if (zbuffer[(int)p.x][(int)p.y] >= p.z)
                    return false;

                zbuffer[(int)p.x][(int)p.y] = p.z;
                return true; 
            }, 
            image, todraw.bounding_box(), color);

    if (debug)
        printf("\ntriangle (%d, %d), (%d, %d), (%d, %d) is drawed.",
            todraw.get_point1().x, todraw.get_point1().y, 
            todraw.get_point2().x, todraw.get_point2().y, 
            todraw.get_point3().x, todraw.get_point3().y);
}

static void draw_model(Model model, TGAImage& image, TGAColor linecolor, int** zbuffer, bool fill, bool edge, bool debug)
{
    if (scale_ratio > gwidth / 2 || scale_ratio > gheight / 2)
        printf("warning: too large scale_ratio: %d", scale_ratio);

    const int face_num = model.nfaces();

    for (int facei = 0; facei < face_num; facei++)
    {
        std::vector<int> face = model.face(facei);

        // current vertex batch
        // update at each face loop
        Vec3f world_vertexs[3];
        Vec2i screen_vertexs[3];

        for (int veci = 0; veci < 3; veci++) // vec3f has three element (x, y, z)
        {
            Vec3f world_curr = model.vert(face[veci]);
            Vec3f world_next = model.vert(face[(veci + 1) % 3]);

            // map world coord to screen
            Vec2i screen_curr = Vec2i((world_curr.x + 1.) * scale_ratio, (world_curr.y + 1.) * scale_ratio);
            Vec2i screen_next = Vec2i((world_next.x + 1.) * scale_ratio, (world_next.y + 1.) * scale_ratio);

            world_vertexs[veci] = world_curr;
            screen_vertexs[veci] = screen_curr;
        }

        // generate triangle
        Triangle3D face_triangle_3d(world_vertexs);
        Triangle2D face_triangle_screen(screen_vertexs);

        TGAColor face_color = render_color(
            face_triangle_3d.normal(),
            global_light_direction);

        if (face_color != clear)
            draw_triangle(face_triangle_screen, face_triangle_3d, zbuffer, image, face_color, fill, edge, debug);

        if (debug)
            printf("\ndrawing model triangle: [%d / %d]", facei, face_num);
    }
}

static void output(TGAImage& image, const std::string filename)
{
    image.flip_vertically();
    image.write_tga_file(("out/" + filename).c_str());
}

int main(int argc, char** argv)
{
    TGAImage model_scene(gwidth, gheight, TGAImage::RGB);
    TGAImage depth_scene(gwidth, gheight, TGAImage::RGB);

    Model model("resources/african_head.obj");

    // heap alloc zbuffer
    int** zbuffer = new int* [gwidth]; 
    for (int i = 0; i < gwidth; i++) 
        zbuffer[i] = new int[gheight];

    // init by negtive infinity
    for (int x = 0; x < gwidth; x++)
        for (int y = 0; y < gheight; y++)
            zbuffer[x][y] = std::numeric_limits<int>::min();

    // draw
    draw_model(model, model_scene, white, zbuffer, true, true, false);

    output(model_scene, "output.tga");
    output(depth_scene, "depth.tga");

    delete[] zbuffer;

    return 0;
}