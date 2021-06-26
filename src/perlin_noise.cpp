#include "perlin_noise.h"

PerlinNoise::PerlinNoise(int width, int height, int octaves)
    :m_output_width(width)
    ,m_output_height(height)
{
    m_noise_seed_2D = new float[width * height];
    m_perlin_noise_2D = new float[width * height];

    generateSeedNoise2D();
    generatePerlinNoise2D(octaves);
}

PerlinNoise::PerlinNoise(int size_1D, int octaves)
    :m_output_size(size_1D)
{
    m_noise_seed_1D = new float[m_output_size];
    m_perlin_noise_1D = new float[m_output_size];

    generateSeedNoise1D();
    generatePerlinNoise1D(octaves);
}

PerlinNoise::~PerlinNoise()
{
    delete m_noise_seed_2D;
    delete m_perlin_noise_2D;
    delete m_noise_seed_1D;
    delete m_perlin_noise_1D;
}


///////////////////////////////////////////////////////////////////////////////
// 2D functions
///////////////////////////////////////////////////////////////////////////////

void PerlinNoise::generateSeedNoise2D()
{
    for (int i = 0; i < m_output_width * m_output_height; i++) m_noise_seed_2D[i] = (float)rand() / (float)RAND_MAX;
}

void PerlinNoise::generatePerlinNoise2D(int octaves)
{
    //float calc_acc_scale = (std::pow(2.0f, octaves) - 1.0f) / std::pow(2.0f, octaves - 1.0f);
    for (int y = 0; y < m_output_height; y++)
    {
        for (int x = 0; x < m_output_width; x++)
        {
            float acc_noise = 0.0f; // Accumulated noise
            float scale = 1.0f;
            float acc_scale = 0.0f;
            for (int o = 0; o < octaves; o++)
            {
                int pitch = m_output_width >> o; 
                int sampleX1 = (x / pitch) * pitch; 
                int sampleY1 = (y / pitch) * pitch; 

                int sampleX2 = (sampleX1 + pitch) % m_output_width;
                int sampleY2 = (sampleY1 + pitch) % m_output_width;

                // We then need to find the linear interpolation between the two samples
                // To do this we need to find how far into a pitch are we
                float blendX = (float)(x - sampleX1) / (float)pitch; // a value between 0 and 1
                float blendY = (float)(y - sampleY1) / (float)pitch; // a value between 0 and 1

                // We want two lerps to lerp between (for the y axis)
                float sampleT = (1.0f - blendX) * m_noise_seed_2D[sampleY1 * m_output_width + sampleX1] + blendX * m_noise_seed_2D[sampleY1 * m_output_width + sampleX2]; // Linearly interpolate between sample1 and sample2
                float sampleB = (1.0f - blendX) * m_noise_seed_2D[sampleY2 * m_output_width + sampleX1] + blendX * m_noise_seed_2D[sampleY2 * m_output_width + sampleX2]; // Linearly interpolate between sample1 and sample2

                // Lerp equation between sample B and sample T
                acc_noise += (blendY * (sampleB - sampleT) + sampleT) * scale;
                acc_scale += scale;
                scale = scale / 2;
            }
            float value = acc_noise / acc_scale;
            m_perlin_noise_2D[y * m_output_width + x] = value;
            if (value < m_min_perlin_value) m_min_perlin_value = value;
            if (value > m_max_perlin_value) m_max_perlin_value = value;
        }
    }
}

float * PerlinNoise::getPerlinNoise2D()
{
    return m_perlin_noise_2D;
}

float * PerlinNoise::getNoiseSeed2D()
{
    return m_noise_seed_2D;
}



///////////////////////////////////////////////////////////////////////////////
// 1D functions
///////////////////////////////////////////////////////////////////////////////

void PerlinNoise::generateSeedNoise1D()
{
    for (int i = 0; i < m_output_size; i++) m_noise_seed_1D[i] = (float)rand() / (float)RAND_MAX;
}

void PerlinNoise::generatePerlinNoise1D(int octaves)
{
    //float calc_acc_scale = (std::pow(2.0f, octaves) - 1.0f) / std::pow(2.0f, octaves - 1.0f);
    for (int x = 0; x < m_output_size; x++)
    {
        float acc_noise = 0.0f; // Accumulated noise
        float scale = 1.0f;
        float acc_scale = 0.0f;
        for (int o = 0; o < octaves; o++)
        {
            int pitch = m_output_size >> o; // pitch is how much distance between each sample. 128 means two samples. 64 means 4 samples. 1 means 256 samples
            int sample1 = (x / pitch) * pitch; // Due to int devision, infomation is lost. So we essntialy round down to nearest pitch multiple
            int sample2 = (sample1 + pitch) % m_output_size;
            // We then need to find the linear interpolation between the two samples
            // To do this we need to find how far into a pitch are we
            float blend = (float)(x - sample1) / (float)pitch; // a value between 0 and 1
            float sample = (1.0f - blend) * m_noise_seed_1D[sample1] + blend * m_noise_seed_1D[sample2]; // Linearly interpolate between sample1 and sample2
            acc_noise += sample * scale;
            acc_scale += scale;
            scale = scale / 2;
        }
        float value = acc_noise / acc_scale;
        m_perlin_noise_1D[x] = value;
        if (value < m_min_perlin_value) m_min_perlin_value = value;
        if (value > m_max_perlin_value) m_max_perlin_value = value;

    }
}

float * PerlinNoise::getPerlinNoise1D()
{
    return m_perlin_noise_1D;
}

float * PerlinNoise::getNoiseSeed1D()
{
    return m_noise_seed_1D;
}

float PerlinNoise::getMaxPerlinValue()
{
    return m_max_perlin_value;
}

float PerlinNoise::getMinPerlinValue()
{
    return m_min_perlin_value;
}