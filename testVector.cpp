#include "VectorMath.cpp"
#include "defaultStructs.h"
#include <chrono>
#include <ios>

using namespace std;


int main() {
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 512*512*100*16; ++i) {
        Vector v1(-0.5f, 0.332, 0.1);
        Vector v2(0.25f, -1.f, 0.1);
        Vector v3(-19, -0.2, -5);

        v1 = vectorAddToAllAxis(v1, 0.5f);
        v2 = vectorAdd(vectorScale(v2, 8.88f), vectorNormalize(v3));

        Vector zzzzz = vectorCrossProduct(v1, v2);

        float x = vectorDotProduct(zzzzz, v2);
        v1 = vectorScale(vectorAdd(vectorAdd(v1, v2), v3), x);
        // vectorPrint(v1);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end-start;
    cout << "1: " << diff.count() << " s" << endl;


    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 512*512*100*16; ++i) {
        Vector v1(-0.5f, 0.332, 0.1);
        Vector v2(0.25f, -1.f, 0.1);
        Vector v3(-19, -0.2, -5);


        v1.x += 0.5f;
        v1.y +=0.5f;
        v1.z +=0.5f;

        float scale1 = 1.f/(sqrt(v3.x * v3.x + v3.y * v3.y + v3.z * v3.z));

        v2.x = (v2.x * 8.88f) + (v3.x * scale1);
        v2.y = (v2.y * 8.88f) + (v3.y * scale1);
        v2.z = (v2.z * 8.88f) + (v3.z * scale1);

        Vector zzzzz;
        zzzzz.x = v1.y*v2.z-v1.z*v2.y;
        zzzzz.y = v1.z*v2.x- v1.x*v2.z;
        zzzzz.z = v1.x*v2.y-v1.y*v2.x;

        float x = zzzzz.x*v2.x + zzzzz.y*v2.y + zzzzz.z*v2.z;

        v1.x = (v1.x + v2.x + v3.x) * x;
        v1.y = (v1.y + v2.y +v3.y)*x;
        v1.z = (v1.z + v2.z +v3.z)* x;

        // v1 = Vector(v1.x + 0.5f, v1.y + 0.5f,  v1.z + 0.5f);
        // v2 = Vector((v2.x * 8.88f) + (v3.x * scale1), (v2.y * 8.88f) + (v3.y * scale1),  (v2.z * 8.88f) + (v3.z * scale1));
        // zzzzz = Vector(v1.y*v2.z-v1.z*v2.y, v1.z*v2.x- v1.x*v2.z, v1.x*v2.y-v1.y*v2.x);

        // v1 = Vector((v1.x + v2.x + v3.x) * x, (v1.y + v2.y +v3.y)*x, (v1.z + v2.z +v3.z)* x);
        // std::cout << "Vector: " << v1.x << " " << v1.y << " " << v1.z << std::endl;

    }

    end = std::chrono::high_resolution_clock::now();
    diff = end-start;
    cout << "2: " << diff.count() << " s" << endl;


}
