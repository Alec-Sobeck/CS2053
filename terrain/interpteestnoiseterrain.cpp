
#include <cmath>
#include "interpteestnoiseterrain.h"
#include "utils/random.h"
#include "interpolators.h"


InterpTestNoiseTerrain::InterpTestNoiseTerrain(int numVal, float maxVal, int lod, float size) : heightMap(buildNoise(numVal)), maxVal(maxVal)
{
    generateTerrain(lod, size);
}

FlexArray<FlexArray<float>> InterpTestNoiseTerrain::buildNoise(int width)
{
    FlexArray<FlexArray<float>> noise = make2DFlex<float>(width, width);
    for (int i = 0; i < noise.size(); i++)
    {
        for (int j = 0; j < noise[0].size(); j++)
        {
            noise[i][j] = getRandomFloat();
        }
    }
    return noise;
}

float InterpTestNoiseTerrain::getHeight(double x, double y)
{
    double nx = abs((x + width / 2) / width * (heightMap.size() - 1));
    double ny = abs((y + width / 2) / width * (heightMap.size() - 1));
    nx = fmin(nx, heightMap.size() - 1);
    ny = fmin(ny, heightMap.size() - 1);
    nx = fmax(nx, 0);
    ny = fmax(ny, 0);

    float topLeft = heightMap[static_cast<int>(floor(nx))][static_cast<int>(floor(ny))];
    float topRight = heightMap[static_cast<int>(ceil(nx))][static_cast<int>(floor(ny))];
    float bottomLeft = heightMap[static_cast<int>(floor(nx))][static_cast<int>(ceil(ny))];
    float bottomRight = heightMap[static_cast<int>(ceil(nx))][static_cast<int>(ceil(ny))];

    float tx = static_cast<float>(nx - floor(nx));
    float ty = static_cast<float>(ny - floor(ny));
    //return (float) (maxVal * Interpolators.bilinearInterpolate(topLeft, topRight, bottomLeft, bottomRight, tx, ty));
    return static_cast<float>(maxVal * bicosineInterpolate(topLeft, topRight, bottomLeft, bottomRight, tx, ty));
}

Colour InterpTestNoiseTerrain::getColour(double x, double y)
{
    return Colour(getHeight(x, y) / 8, .5 - getHeight(x, y) / 8, 0, 1);
}
