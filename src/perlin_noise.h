#ifndef __PERLIN_NOISE_H
#define __PERLIN_NOISE_H

#include <cstdlib>
#include <cmath>

// This is based of the tutorial by OneLoneCoder
// Link to video tutorial: www.youtube.com/watch?v=6-0UaeJBumA
class PerlinNoise {
private:
    // 2D noise variables
    float * m_noise_seed_2D = nullptr;
    float * m_perlin_noise_2D = nullptr;
    int m_output_width;
    int m_output_height;

    // 1D noise variables
    float * m_noise_seed_1D = nullptr;
    float * m_perlin_noise_1D = nullptr;
    int m_output_size;

    // Meta data
    float m_max_perlin_value = 0.0f;
    float m_min_perlin_value = 1.0f;

public:
    PerlinNoise(int width, int height, int octaves); // 2D constructor
    PerlinNoise(int size_1D, int octaves); // 1D constructor
    ~PerlinNoise();

    // 2D noise functions
    void generateSeedNoise2D();
    void generatePerlinNoise2D(int nOctaves);
    float * getPerlinNoise2D();
    float * getNoiseSeed2D();

    // 1D noise funcitons
    void generateSeedNoise1D();
    void generatePerlinNoise1D(int nOctaves);
    float * getPerlinNoise1D();
    float * getNoiseSeed1D();

    // Meta data functions
    float getMaxPerlinValue();
    float getMinPerlinValue();

};

#endif