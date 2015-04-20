#ifndef TERRAIN_POLYGON_H
#define TERRAIN_POLYGON_H

#include <vector>
#include "glm/vec3.hpp"
#include "math/polygon3.h"
#include "physics/aabb.h"

struct RawPolygonData
{
public:
    float *data;
    int size;
    RawPolygonData(float *data, int size) : data(data), size(size)
    {
    }
};

///
/// TerrainPolygon associates a Polygon3 with its AABB, constructing said AABB when passed a Polygon3 in the constructor 
///
class TerrainPolygon : public Polygon3
{
public:
	///
	/// An int which is the number of floats associated to one vertex; const because they currently have a fixed number of elements
	/// per vertex. 3 position, 3 normal, 4 colour, 2 texture.
	///
	static const int TOTAL_ROW_SIZE = 3/*Vert*/ + 4/*Colour*/ + 2/*Texture-Coord*/ + 3/*Normal*/;
	AABB polygonBounds;
	int* IBOIndexes;
	std::vector<float> colour;
	std::vector<float> textureCoords;
	TerrainPolygon();
	///
	/// Constructs a new TerrainPolygon and constructs the AABB that is associated with it.
	/// \param associatedPolygon a Polygon3 that will be used to construct an AABB
	///
	TerrainPolygon(std::vector<glm::vec3> vertices, std::vector<float> colour, std::vector<float> textureCoords);
	///
	/// Gets the float[] that completely describes this TerrainPolygon's vertex, normal, colour and texture coordinate data.
	/// \return a float[] that completely describes this TerrainPolygon for rendering purposes.
	/// Each vertex will be associated with the following data, in this order:
	/// { x, y, z, nx, ny, nz, r, g, b, a, u, v }, although all of the vertex data is combined
	/// into one single array. {@link #elementsPerVertex()} gives the total number of floats
	/// associated to one vertex, in this case 12 floats, while {@link #getVertexCount()}
	/// gives the total number of vertices of this polygon - using these two values makes
	/// it possible to step through this array of combined data to look at each vertex
	/// individually if required.
	///
	RawPolygonData getRawData();
	AABB getAABB();
	virtual void onAABBCollision(AABB &a);
	///
	/// Gets the indexes of this TerrainPolygon in the terrain IBO. This will be null if
	/// no such indexes have been assigned.
	/// \return an int[] which describes the indexes of this poly in the terrain IBO, or null if no
	/// such indexes have been assigned.
	///
	int* getIBOIndexes();
	///
	/// Sets the indexes of this terrain poly based on where the indexes appear in the IBO of the terrain data.
	/// \param iBOIndexes an int[] describing where the vertices of this poly appear in the terrain IBO
	///
	void setIBOIndexes(int *iBOIndexes);
	std::vector<float> getTextureCoords();
	std::vector<float> getColour();
    ~TerrainPolygon();
private:
	///
	/// Approximates the bounds of the Polygon3 associated to this TerrainPolygon.
	/// This bounding box will still work even if one of the lengths of the sides is exactly equal to zero.
	///
	AABB generateBounds();
};

inline bool operator<(const TerrainPolygon &first, const TerrainPolygon &other)
{
    return false;
}

#endif
