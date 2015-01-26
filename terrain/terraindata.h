#ifndef TERRAIN_DATA_H
#define TERRAIN_DATA_H

#include <vector>
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "utils/colour.h"

/**
 * Contains the data required to reconstruct the terrain of a world. Currently, this is 
 * a collection of TerrainPolygon and some metadata including the total number of vertices
 * of all the polygons and the total number of elements (vertices, normals, colours, texture-coords)
 * to describe the entire terrain. 
 * @author Alec Sobeck
 * @author Matthew Robertson
 */
class TerrainData 
{
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<Colour> colours;
	std::vector<glm::vec2> textureCoords;
	std::vector<glm::vec3> faceVerts;
	std::vector<glm::vec3> faceNormals;
	std::vector<glm::vec3> faceTextures;	
	bool statsNeedRecalculated;

public:
	/**
	 * Constructs a new TerrainData object with the specified initial values.
	 */
	TerrainData(std::vector<glm::vec3> verts, std::vector<glm::vec3> normals, std::vector<Colour> colours, std::vector<glm::vec2> textureCoords,
		std::vector<glm::vec3> faceVerts, std::vector<glm::vec3> faceNormals, std::vector<glm::vec3> faceTextures)
		: vertices(verts), normals(normals), colours(colours), textureCoords(textureCoords), faceVerts(faceVerts), 
			faceNormals(faceNormals), faceTextures(faceTextures)
	{
	}
	
	TerrainData() vertices(std::vector<glm::vec3>()), normals(std::vector<glm::vec3>()), colours(std::vector<Colour>()), textureCoords(std::vector<glm::vec2>()), 
		faceVerts(std::vector<glm::vec3>()), faceNormals(std::vector<glm::vec3>()), faceTextures(std::vector<glm::vec3>())
	{
	}
	
	/**
	 * Gets the List of TerrainPolygons in this TerrainData.
	 * @return a List<TerrainPolygon> that belong to this TerrainData
	 */
	public TerrainPolygon[] getPolygons()
	{
		ArrayList<TerrainPolygon> polygons = new ArrayList<TerrainPolygon>();
		int k;
		
		for (int i = 0; i < faceVerts.size(); i++){
			double[] faceVertVals = faceVerts.get(i).getValues();
			//double[] faceNormalVals = faceNormals.get(i).getValues();
			double[] faceUVVals = faceTextures.get(i).getValues();
			
			Vector3[] polyVerts = new Vector3[faceVertVals.length];
			float[] polyColours = new float[4 * faceVertVals.length];
			float[] polyUVs = new float[2 * faceUVVals.length];
			
			k=0;
			for (int j = 0; j < faceVertVals.length; j++)
			{
				polyVerts[j] = vertices.get((int) faceVertVals[j] - 1);
				polyColours[k] = (float) colours.get((int) faceVertVals[j] - 1).getR();
				polyColours[k+1] = (float) colours.get((int) faceVertVals[j] - 1).getG();
				polyColours[k+2] = (float) colours.get((int) faceVertVals[j] - 1).getB();
				polyColours[k+3] = (float) colours.get((int) faceVertVals[j] - 1).getA();
				k+=4;
			}
			
			k = 0;
			for (int j = 0; j < faceUVVals.length; j++)
			{
				polyUVs[k] = (float) textureCoords.get((int) faceUVVals[j] - 1).getX();
				polyUVs[k+1] = (float) textureCoords.get((int) faceUVVals[j] - 1).getY();
				k+=2;
			}
			
			polygons.add(new TerrainPolygon(
					polyVerts,
					polyColours,
					polyUVs));
		}
		
		return polygons.toArray(new TerrainPolygon[polygons.size()]);
	}

	/**
	 * The total number of vertices of all the polygons in the TerrainData. It is expected that this value 
	 * should be in the interval [0, INF] 
	 * @return
	 */
	public int getTotalNumberOfVertices() 
	{
		return vertices.size();
	}
	
	public void exportToOBJ(String filePath)
	{
		try {
			FileWriter fileWriter = new FileWriter(filePath + ".obj");
			BufferedWriter writer = new BufferedWriter(fileWriter);
			
			for (Vector3 vertex : vertices)
			{
				writer.write("v " + vertex.getX() + " " + vertex.getY() + " " + vertex.getZ() + "\n");
			}
			
			/*for (Point2 texturecoord : textureCoords)
			{
				writer.write("vt " + texturecoord.getX() + " " + texturecoord.getY());
			}*/
			
			for (Vector3 normal : normals)
			{
				writer.write("vn " + normal.getX() + " " + normal.getY() + " " + normal.getZ() + "\n");
			}
			
			String faceData = "";
			double[] faceVert;
			double[] faceNormal;
			double[] faceTexture;
			
			for (int i = 0; i < faceVerts.size(); i++)
			{
				faceData = "";
				faceVert = faceVerts.get(i).getValues();
				if (faceNormals != null && faceNormals.size() >= faceVerts.size())
				{
					faceNormal = faceNormals.get(i).getValues();
				}
				else
				{
					faceNormal = null;
				}
				
				if (faceTextures != null && faceTextures.size() >= faceVerts.size())
				{
					faceTexture = faceTextures.get(i).getValues();
				}
				else
				{
					faceTexture = null;
				}
				
				for (int j = 0; j < 3; j++)
				{
					faceData += faceVert[j];
					
					if (faceTexture != null)
					{
						faceData += "/" + ((int) faceTexture[j]);
						if (faceNormal != null)
						{
							faceData += "/" + ((int) faceNormal[j]);
						}
					}
					else if (faceNormal != null)
					{
						faceData += "//" + ((int) faceNormal[j]);
					}
					faceData += " ";
				}
				
				writer.write("f " + faceData + "\n");
			}
			
			writer.close();
		}
		catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}

#endif