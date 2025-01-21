#include <cstdio>
#include <cmath>
#include "vec3.h"
#include "color.h"
#include "ray.h"

#define PROGRESS_FINISHED "###################"
#define PROGRESS_REMAIN   "                   "
#define PROGRESS_BAR_SIZE 20

color ray_color(const ray &r) {
    vec3 u_dir = unit_vector(r.direction());
    double a = 0.5 * (1 + u_dir.y());
    return (1-a) * color(1, 1, 1) + a * color(0.5, 0.7, 1.0);
}

int main() {

    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    int image_height = int(image_width / aspect_ratio);
    image_height = 1.0 > image_height ? 1.0 : image_height;

    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * (double(image_width) / image_height);
    point3 camera_center = point3(0, 0, 0);

    vec3 viewport_u = vec3(viewport_width, 0, 0);
    vec3 viewport_v = vec3(0, -viewport_height, 0);

    vec3 pixel_delta_u = viewport_u / image_width;
    vec3 pixel_delta_v = viewport_v / image_height;

    vec3 viewport_upper_left = camera_center - vec3(0, 0, focal_length) - (viewport_u / 2 + viewport_v / 2);
    point3 pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    printf("P3\n%d %d\n255\n", image_width, image_height);

    for (int i = 0; i < image_height; i++) {
        int progress = int(double(i) / (image_height-1) * PROGRESS_BAR_SIZE);
        fprintf(stderr, "\r[%.*s%.*s]", progress, PROGRESS_FINISHED, PROGRESS_BAR_SIZE-progress, PROGRESS_REMAIN);
        for (int j = 0; j < image_width; j++) {
            point3 pixel_center = pixel00_loc + i * pixel_delta_v + j * pixel_delta_u;
            point3 ray_dir = pixel_center - camera_center;
            ray r(camera_center, ray_dir);

            color pixel_color = ray_color(r);
            write_color(stdout, pixel_color);
        }
    }
    fprintf(stderr, "\r[%.*s] \n", PROGRESS_BAR_SIZE, PROGRESS_FINISHED);
}