#include <cstdlib>
#include <ctime>
#include "RandomSampler.h"

mt19937 RandomSampler::rng;
uniform_real_distribution<float> RandomSampler::distFloat;
uniform_int_distribution<int> RandomSampler::distInt;


void RandomSampler::initSeed() {
    rng.seed(time(nullptr));
    distFloat = uniform_real_distribution<float>(0, 1);
    distInt = uniform_int_distribution<int>(0, 1);
    //srand(time(NULL));
}

float RandomSampler::getProbability() {
    return getFloatInRange(0,1.f);
}

float RandomSampler::getFloatInRange(float min, float max) {

        return distFloat(rng) * (max - min) + min;
    //return min + (rand() % static_cast<int>(max - min + 1));
}

vector<Vector2D> RandomSampler::jitter2D(int n) {
    vector<Vector2D> jitterVectors;
    for (int p = 0; p < n; ++p) {
        for (int q = 0; q < n; ++q) {
            float x = ((float) p + RandomSampler::getFloatInRange(0,1.f)) / n;
            float y = ((float) q + RandomSampler::getFloatInRange(0,1.f)) / n;
            jitterVectors.emplace_back(x,y);
        }
    }
    return jitterVectors;
}

vector<Vector2D> RandomSampler::getPointsInUnitDisk(int n) {
    vector<Vector2D> points;
    points.reserve(n);
    for (int i = 0; i < n; ++i) {
        points.push_back(RandomSampler::getRandomPointInUnitDisk());
    }
    return points;
}

Vector2D RandomSampler::getRandomPointInUnitDisk() {
    float x = RandomSampler::getFloatInRange(-1.f,1.f);
    float y = RandomSampler::getFloatInRange(-1.f,1.f);

    if (x*x + y*y < 1)
        return {x,y};
    return RandomSampler::getRandomPointInUnitDisk();
}
