#ifndef PROJECT_RANDOMSAMPLER_H
#define PROJECT_RANDOMSAMPLER_H

#include <vector>
#include "defaultStructs.h"


/**
 * @class RandomSampler
 * static class responsible for random number generation and advance number sapling (eg. Jittering)
 */

using namespace std;

class RandomSampler {

public:
    static void initSeed();
    static float getProbability();
    static float getFloatInRange(float min, float max);
    static vector<Vector2D> jitter2D(int n);
    static vector<Vector2D> getPointsInUnitDisk(int n);
    static Vector2D getRandomPointInUnitDisk();

};


#endif //PROJECT_RANDOMSAMPLER_H
