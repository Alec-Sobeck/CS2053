


import java.util.Random;

import math.Interpolators;

import utils.Colour;

public class InterpTestNoiseTerrain extends Terrain
{
	private float[][] heightMap;
	private float maxVal;

	public InterpTestNoiseTerrain(int numVal, float maxVal, int lod, float size){
		heightMap = buildNoise(numVal);
		this.maxVal = maxVal;
		generateTerrain(lod, size);
	}

	public  float[][] buildNoise(int width){
		float[][] noise = new float[width][width];
		Random rng = new Random();

		for (int i = 0; i < noise.length; i++){
			for (int j = 0; j < noise[0].length; j++){
				noise[i][j] = (float)rng.nextFloat();
			}
		}

		return noise;
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
		//return (float) (maxVal * Interpolators.bilinearInterpolate(topLeft, topRight, bottomLeft, bottomRight, tx, ty));
		return (float)(maxVal * Interpolators.bicosineInterpolate(topLeft, topRight, bottomLeft, bottomRight, tx, ty));
	}

	@Override
		public Colour getColour(double x, double y) {
		return new Colour(getHeight(x, y) / 8, .5 - getHeight(x, y) / 8, 0, 1);
	}

}