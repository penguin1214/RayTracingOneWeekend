#include <iostream>
#include <fstream>

using namespace std;
int main() {
    ofstream ppm;
    ppm.open("image.ppm");
    int width = 200;
    int height = 100;
    float delta_x = 255 / width;
    float delta_y = 255 / height;
    ppm << "P3\n" << width << " " << height << "\n255\n";   // ASCII, size, max value
    int r = 0; int g = 0; int b = 0;
    for (int i = 0; i < height; ++i) {
        g = 255 - delta_y * i;
        for (int j = 0; j < width; ++j) {
            r = delta_x * j;
            ppm << r << " " << g << " " << b << " ";
        }
        ppm << endl;
    }
    return 0;
}