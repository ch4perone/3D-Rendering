#include "VectorMath.cpp"
#include "defaultStructs.h"
#include <chrono>
#include <ios>

using namespace std;


int main() {
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 512*512*10; ++i) {
        Vector v1(-0.5f, 0.332, 0.1);
        Vector v2(0.25f, -1.f, 0.1);
        Vector v3(-19, -0.2, -5);

        v1 = vectorAddToAllAxis(v1, 0.5f);
        v2 = vectorAdd(vectorScale(v2, 8.88f), vectorNormalize(v3));

        Vector zzzzz = vectorCrossProduct(v1, v2);

        float x = vectorDotProduct(zzzzz, v2);
        v1 = vectorScale(vectorAdd(vectorAdd(v1, v2), v3), x);
        vectorPrint(v1);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end-start;
    cout << "1: " << diff.count() << " s" << endl;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 512*512*10; ++i) {
        Vector v1(-0.5f, 0.332, 0.1);
        Vector v2(0.25f, -1.f, 0.1);
        Vector v3(-19, -0.2, -5);



        v1 = vectorAddToAllAxis(v1, 0.5f);
        v2 = vectorAdd(vectorScale(v2, 8.88f), vectorNormalize(v3));

        Vector zzzzz = vectorCrossProduct(v1, v2);

        float x = vectorDotProduct(zzzzz, v2);
        v1 = vectorScale(vectorAdd(vectorAdd(v1, v2), v3), x);
        vectorPrint(v1);

    }

    end = std::chrono::high_resolution_clock::now();
    diff = end-start;
    cout << "2: " << diff.count() << " s" << endl;


}