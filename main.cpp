#include <iostream>
#include <fstream>
#include "vec3.h"

using namespace std;
int main() {
    vec3 v1 = vec3(1,2,3);
    vec3 v2 = vec3(4,5,6);
    cout << dot(v1, v2) << endl;
    return 0;
}