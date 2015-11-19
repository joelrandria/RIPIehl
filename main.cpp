#include <iostream>
#include "Mat4.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    Vec2d d(0.4f,0.7f);
    Vec2f f(1.2f,1.7f);
    Vec2i i(2,2);
    f+=i;
    f=f;

    Vec3d d2(1.8f,f);

    Mat4 m1(true);
    Mat4 m2(11,22,3,19,5,6,7,8,9,10,11,12,13,14,15);
    Color4f color(f,d);
    std :: cout<< m2.inverted() << std :: endl;
    return 0;
}