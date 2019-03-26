#include <cstdlib>
#include <ctime>
#include "RandomSampler.h"

void RandomSampler::initSeed() {
    srand(time(0));
}

float RandomSampler::getProbability() {
    return 0;
}

float RandomSampler::getFloatInRange(float min, float max) {
    float random = (float) rand() / (float) RAND_MAX;
    return min + (max - min) * random;
    //return min + (rand() % static_cast<int>(max - min + 1));
}

vector<Vector2D> RandomSampler::jitter2D(int n) {
    vector<Vector2D> jitterVectors;
    for (int p = 0; p < n; ++p) {
        for (int q = 0; q < n; ++q) {
            float x = ((float) p + RandomSampler::getFloatInRange(0,1.f)) / n;
            float y = ((float) q + RandomSampler::getFloatInRange(0, 1.f)) / n;
            jitterVectors.push_back(Vector2D(x,y));
        }
    }
    return jitterVectors;
}
