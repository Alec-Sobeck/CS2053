#ifndef TERRAIN_POLYGON_H
#define TERRAIN_POLYGON_H

#include "glm/vec3.hpp"
#include "utils/flexarray.h"
#include "math/polygon3.h"
#include "math/ioctreeelement.h"
#include "physics/aabb.h"

/**
 * TerrainPolygon associates a Polygon3 with its AABB, constructing said AABB when passed
 * a Polygon3 in the constructor {@link #TerrainPolygon(Polygon3)}.
 * @author Alec Sobeck
 * @author Matthew Robertson
 */
class TerrainPolygon : public Polygon3, public IOctreeElement
{
public:
	/**
	 * An int which is the number of floats associated to one vertex; const because they currently have a fixed number of elements
	 * per vertex. 3 position, 3 normal, 4 colour, 2 texture.
	 */
	const int TOTAL_ROW_SIZE = 3/*Vert*/ + 4/*Colour*/ + 2/*Texture-Coord*/ + 3/*Normal*/;
	AABB polygonBounds;
	FlexArray<int> IBOIndexes;
	FlexArray<float> colour;
	FlexArray<float> textureCoords;
	/**
	 * Constructs a new TerrainPolygon and constructs the AABB that is associated with it.
	 * @param associatedPolygon a Polygon3 that will be used to construct an AABB
	 */
	TerrainPolygon(std::vector<glm::vec3> vertices, FlexArray<float> colour, FlexArray<float> textureCoords);
	/**
	 * Gets the float[] that completely describes this TerrainPolygon's vertex, normal, colour
	 * and texture coordinate data.
	 * @return a float[] that completely describes this TerrainPolygon for rendering purposes.
	 * Each vertex will be associated with the following data, in this order:
	 * { x, y, z, nx, ny, nz, r, g, b, a, u, v }, although all of the vertex data is combined
	 * into one single array. {@link #elementsPerVertex()} gives the total number of floats
	 * associated to one vertex, in this case 12 floats, while {@link #getVertexCount()}
	 * gives the total number of vertices of this polygon - using these two values makes
	 * it possible to step through this array of combined data to look at each vertex
	 * individually if required.
	 */
	FlexArray<float> getRawData();
	AABB getAABB();
	//TODO make this method do something?
	virtual void onAABBCollision(AABB &a);
	/**
	 * Gets the indexes of this TerrainPolygon in the terrain IBO. This will be null if
	 * no such indexes have been assigned.
	 * @return an int[] which describes the indexes of this poly in the terrain IBO, or null if no
	 * such indexes have been assigned.
	 */
	FlexArray<int> getIBOIndexes();
	/**
	 * Sets the indexes of this terrain poly based on where the indexes appear in the IBO of the terrain data.
	 * @param iBOIndexes an int[] describing where the vertices of this poly appear in the terrain IBO
	 */
	void setIBOIndexes(FlexArray<int> &iBOIndexes);
	FlexArray<float> getTextureCoords();
	FlexArray<float> getColour();
private:
	/**
	 * Approximates the bounds of the Polygon3 associated to this TerrainPolygon.
	 * This bounding box will still work even if one of the lengths of the sides
	 * is exactly equal to zero.
	 * @return
	 */
	AABB generateBounds();
};


#endif
