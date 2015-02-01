
#include <cmath>
#include "midpointterrain.h"
#include "utils/random.h"
#include "interpolators.h"

MidPointTerrain::MidPointTerrain(int iterations, float roughness, int lod, float size) : roughness(roughness)
{
    int sideLength = static_cast<int>(pow(2, iterations) - 1);
    heightMap = make2DFlex<float>(sideLength, sideLength);
    width = size;
    lod = sideLength;

    heightMap[0][0] = 7.0f + getRandomFloat() * randomizerValue * 2 - randomizerValue;
    heightMap[0][heightMap.size() - 1] = 7.0f + getRandomFloat() * randomizerValue * 2 - randomizerValue;
    heightMap[heightMap.size() - 1][0] = 7.0f + getRandomFloat() * randomizerValue * 2 - randomizerValue;
    heightMap[heightMap.size() - 1][heightMap.size() - 1] = 7.0f + getRandomFloat() * randomizerValue * 2 - randomizerValue;
    buildHeightMap(randomizerValue, 0, 0, heightMap.size() - 1, heightMap.size() - 1);

    for (int i = 0; i < heightMap.size(); i++)
    {
        for (int j = 0; j < heightMap[0].size(); j++)
        {
            if (heightMap[i][j] > maxHeight)
            {
                maxHeight = heightMap[i][j];
            }
        }
    }
    //maybe change this?
    generateTerrain(lod, size);
}

void MidPointTerrain::buildHeightMap(float randomizerValue, int x1, int y1, int x2, int y2)
{
    int xm = (x1 + x2) / 2;
    int ym = (y1 + y2) / 2;
    if (xm == x1 && ym == y1)
    {
        return;
    }

    // Diamond
    heightMap[xm][ym] = (getRandomFloat() * 2 * randomizerValue - randomizerValue) +
        ((heightMap[x1][y1] + heightMap[x1][y2] +
        heightMap[x2][y1] + heightMap[x2][y2]) / 4);

    // Square
    if (x1 == 0)
    {
        heightMap[x1][ym] = (getRandomFloat() * 2 * randomizerValue - randomizerValue) +
            (heightMap[x1][y1] + heightMap[x2][y1] + heightMap[xm][ym]) / 3;
    }
    else
    {
        heightMap[x1][ym] = (getRandomFloat() * 2 * randomizerValue - randomizerValue) +
            (heightMap[x1][y1] + heightMap[x1][y2] + heightMap[xm][ym] + heightMap[x1 - (xm - x1)][ym]) / 4;
    }
    if (y1 == 0)
    {
        heightMap[xm][y1] = (getRandomFloat() * 2 * randomizerValue - randomizerValue) +
            (heightMap[x1][y1] + heightMap[x2][y1] + heightMap[xm][ym]) / 3;
    }
    else
    {
        heightMap[xm][y1] = (getRandomFloat() * 2 * randomizerValue - randomizerValue) +
            (heightMap[x1][y1] + heightMap[x2][y1] + heightMap[xm][ym] + heightMap[xm][y1 - (ym - y1)]) / 4;
    }
    if (x2 == heightMap.size() - 1)
    {
        heightMap[x2][ym] = (getRandomFloat() * 2 * randomizerValue - randomizerValue) +
            (heightMap[x2][y1] + heightMap[x2][y2] + heightMap[xm][ym]) / 3;
    }
    else
    {
        heightMap[x2][ym] = (getRandomFloat() * 2 * randomizerValue - randomizerValue) +
            (heightMap[x2][y1] + heightMap[x2][y2] + heightMap[xm][ym] + heightMap[x2 + (xm - x1)][ym]) / 4;
    }
    if (y2 == heightMap.size() - 1)
    {
        heightMap[xm][y2] = (getRandomFloat() * 2 * randomizerValue - randomizerValue) +
            (heightMap[x1][y1] + heightMap[x2][y1] + heightMap[xm][ym]) / 3;
    }
    else
    {
        heightMap[xm][y2] = (getRandomFloat() * 2 * randomizerValue - randomizerValue) +
            (heightMap[x1][y2] + heightMap[x2][y2] + heightMap[xm][ym] + heightMap[xm][y2 + (ym - y1)]) / 4;
    }

    randomizerValue *= pow(2, -roughness);

    buildHeightMap(randomizerValue, x1, y1, xm, ym);
    buildHeightMap(randomizerValue, xm, y1, x2, ym);
    buildHeightMap(randomizerValue, x1, ym, xm, y2);
    buildHeightMap(randomizerValue, xm, ym, x2, y2);

}

float MidPointTerrain::getHeight(double x, double y)
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
    return 1.5f * static_cast<float>(bicosineInterpolate(topLeft, topRight, bottomLeft, bottomRight, tx, ty) - 1);
}

Colour MidPointTerrain::getColour(double x, double y) {
    return Colour(getHeight(x, y) / (1.5f * maxHeight - 1), 1 - getHeight(x, y) / (1.5f * maxHeight - 1), 0, 1);
}
