#include <cstdio>
#include <cmath>
#include "vec3.h"
#include "color.h"
#include "ray.h"

#define PROGRESS_FINISHED "###################"
#define PROGRESS_REMAIN   "                   "
#define PROGRESS_BAR_SIZE 20

int main() {
    int image_width = 512;
    int image_height = 512;

    printf("P3\n%d %d\n255\n", image_width, image_height);

    for (int i = 0; i < image_height; i++) {
        int progress = int(double(i) / (image_height-1) * PROGRESS_BAR_SIZE);
        fprintf(stderr, "\r[%.*s%.*s]", progress, PROGRESS_FINISHED, PROGRESS_BAR_SIZE-progress, PROGRESS_REMAIN);
        for (int j = 0; j < image_width; j++) {
            color c(double(i) / (image_height-1), double(j) / (image_width-1), 0.0);
            write_color(stdout, c);
        }
    }
    fprintf(stderr, "\r[%.*s] \n", PROGRESS_BAR_SIZE, PROGRESS_FINISHED);
}