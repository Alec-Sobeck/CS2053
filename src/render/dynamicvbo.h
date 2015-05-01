#pragma once

#include <vector>
#include "graphics/camera.h"
#include "graphics/terrainpolygon.h"
#include "render/vbo.h"
#include "render/texture.h"

///
/// Creates an array of values on [a, b).
/// \param a an int, the lower inclusive bound of the array's values
/// \param b an int, the upper exclusive bound of the array's values
/// \return an int[] with values on [a, b)
///
int *constructRange(int a, int b);

///
/// DynamicVBO implements a dynamic Vertex Buffer Object. This VBO chooses what vertexes to render based
/// on an Index Buffer Object that is kept in addition to the vertex data.
///
class DynamicVBO
{
private:
    gl::GLuint vertexBufferID;
	gl::GLuint indexBufferID;
	int indicesCount;
	int vertCount;
	unsigned int* ibo;
	float* vbo;
	bool initialized;
public:
    std::shared_ptr<Texture> texture;
	///
	/// Creates a new DynamicVBO but does not invoke the create(...) method.
	/// The create(...) method must be invoked prior to drawing, adding, or
	/// removing from this DynamicVBO; otherwise exceptions will be thrown
	/// indicating the requested operations are invalid.
	///
	DynamicVBO();
	void create(std::shared_ptr<std::vector<TerrainPolygon>> &polys, std::shared_ptr<Texture> texture);
	///
	/// Draws the terrain as specified by the index buffer object associated with this terrain renderer.
	/// \param cam the Camera that will be used to properly display the terrain
	///
	void draw(Camera *cam);
	void remove(std::vector<int> iboIndexes);
	///
	/// Adds a TerrainPolygon to this Dynamic VBO.
	///
	void add(TerrainPolygon &poly);
	~DynamicVBO();
};



