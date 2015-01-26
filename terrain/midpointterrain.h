package terrain;

import java.util.Random;

import math.Interpolators;
import utils.Colour;

public class MidPointTerrain extends Terrain
{
	float[][] heightMap;
	private float initialValue;
	private Random rng;
	private float roughness;
	private float randomizerValue = 7;
	private int sideLength;
	private float maxHeight = 0.1f;

	public MidPointTerrain(int iterations, float roughness, int lod, float size)
	{
		rng = new Random();
		this.roughness = roughness;
		int sideLength = (int)(Math.pow(2, iterations) - 1);
		heightMap = new float[sideLength][sideLength];
		width = size;
		lod = sideLength;

		heightMap[0][0] = 7f + rng.nextFloat() * randomizerValue * 2 - randomizerValue;
		heightMap[0][heightMap.length - 1] = 7f + rng.nextFloat() * randomizerValue * 2 - randomizerValue;
		heightMap[heightMap.length - 1][0] = 7f + rng.nextFloat() * randomizerValue * 2 - randomizerValue;
		heightMap[heightMap.length - 1][heightMap.length - 1] = 7f + rng.nextFloat() * randomizerValue * 2 - randomizerValue;


		buildHeightMap(randomizerValue, 0, 0, heightMap.length - 1, heightMap.length - 1);

		for (int i = 0; i < heightMap.length; i++){
			for (int j = 0; j < heightMap[0].length; j++){
				if (heightMap[i][j] > maxHeight) maxHeight = heightMap[i][j];
			}
		}
		//maybe change this?
		generateTerrain(lod, size);
	}

	public void buildHeightMap(float randomizerValue, int x1, int y1, int x2, int y2)
	{
		int xm = (x1 + x2) / 2;
		int ym = (y1 + y2) / 2;
		int numPoints = 4;
		if (xm == x1 && ym == y1) return;

		// Diamond

		heightMap[xm][ym] = (rng.nextFloat() * 2 * randomizerValue - randomizerValue) +
			((heightMap[x1][y1] + heightMap[x1][y2] +
			heightMap[x2][y1] + heightMap[x2][y2]) / 4);

		// Square
		if (x1 == 0)
		{
			heightMap[x1][ym] = (rng.nextFloat() * 2 * randomizerValue - randomizerValue) +
				(heightMap[x1][y1] + heightMap[x2][y1] + heightMap[xm][ym]) / 3;
		}
		else
		{
			heightMap[x1][ym] = (rng.nextFloat() * 2 * randomizerValue - randomizerValue) +
				(heightMap[x1][y1] + heightMap[x1][y2] + heightMap[xm][ym] + heightMap[x1 - (xm - x1)][ym]) / 4;
		}
		if (y1 == 0)
		{
			heightMap[xm][y1] = (rng.nextFloat() * 2 * randomizerValue - randomizerValue) +
				(heightMap[x1][y1] + heightMap[x2][y1] + heightMap[xm][ym]) / 3;
		}
		else
		{
			heightMap[xm][y1] = (rng.nextFloat() * 2 * randomizerValue - randomizerValue) +
				(heightMap[x1][y1] + heightMap[x2][y1] + heightMap[xm][ym] + heightMap[xm][y1 - (ym - y1)]) / 4;
		}
		if (x2 == heightMap.length - 1)
		{
			heightMap[x2][ym] = (rng.nextFloat() * 2 * randomizerValue - randomizerValue) +
				(heightMap[x2][y1] + heightMap[x2][y2] + heightMap[xm][ym]) / 3;
		}
		else
		{
			heightMap[x2][ym] = (rng.nextFloat() * 2 * randomizerValue - randomizerValue) +
				(heightMap[x2][y1] + heightMap[x2][y2] + heightMap[xm][ym] + heightMap[x2 + (xm - x1)][ym]) / 4;
		}
		if (y2 == heightMap.length - 1)
		{
			heightMap[xm][y2] = (rng.nextFloat() * 2 * randomizerValue - randomizerValue) +
				(heightMap[x1][y1] + heightMap[x2][y1] + heightMap[xm][ym]) / 3;
		}
		else
		{
			heightMap[xm][y2] = (rng.nextFloat() * 2 * randomizerValue - randomizerValue) +
				(heightMap[x1][y2] + heightMap[x2][y2] + heightMap[xm][ym] + heightMap[xm][y2 + (ym - y1)]) / 4;
		}

		randomizerValue *= Math.pow(2, -roughness);

		buildHeightMap(randomizerValue, x1, y1, xm, ym);
		buildHeightMap(randomizerValue, xm, y1, x2, ym);
		buildHeightMap(randomizerValue, x1, ym, xm, y2);
		buildHeightMap(randomizerValue, xm, ym, x2, y2);

	}


	@Override
		public float getHeight(double x, double y) {

		double nx = Math.abs((x + width / 2) / width * (heightMap.length - 1));
		double ny = Math.abs((y + width / 2) / width * (heightMap.length - 1));
		nx = Math.min(nx, heightMap.length - 1);
		ny = Math.min(ny, heightMap.length - 1);
		nx = Math.max(nx, 0);
		ny = Math.max(ny, 0);

		float topLeft = heightMap[(int)Math.floor(nx)][(int)Math.floor(ny)];
		float topRight = heightMap[(int)Math.ceil(nx)][(int)Math.floor(ny)];
		float bottomLeft = heightMap[(int)Math.floor(nx)][(int)Math.ceil(ny)];
		float bottomRight = heightMap[(int)Math.ceil(nx)][(int)Math.ceil(ny)];

		float tx = (float)(nx - Math.floor(nx));
		float ty = (float)(ny - Math.floor(ny));
		return 1.5f * (float)Interpolators.bicosineInterpolate(topLeft, topRight, bottomLeft, bottomRight, tx, ty) - 1;
	}

	@Override
		public Colour getColour(double x, double y) {
		return new Colour(getHeight(x, y) / (1.5f * maxHeight - 1), 1 - getHeight(x, y) / (1.5f * maxHeight - 1), 0, 1);
	}

}