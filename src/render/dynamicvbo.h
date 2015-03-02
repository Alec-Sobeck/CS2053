#ifndef ENG_DYNAMIC_VBO_H
#define ENG_DYNAMIC_VBO_H

#include "graphics/gluhelper.h"
#include "graphics/camera.h"
#include "graphics/terrainpolygon.h"
#include "render/vbo.h"
#include "utils/flexarray.h"
#include "render/texture.h"

/**
 * Creates an array of values on [a, b).
 * @param a an int, the lower inclusive bound of the array's values
 * @param b an int, the upper exclusive bound of the array's values
 * @return an int[] with values on [a, b)
 */
int *constructRange(int a, int b);

/**
 * DynamicVBO implements a dynamic Vertex Buffer Object. This VBO chooses what vertexes to render based
 * on an Index Buffer Object that is kept in addition to the vertex data.
 * @author Alec Sobeck
 * @author Matthew Robertson
 */
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
	/**
	 * Creates a new DynamicVBO but does not invoke the create(...) method.
	 * The create(...) method must be invoked prior to drawing, adding, or
	 * removing from this DynamicVBO; otherwise exceptions will be thrown
	 * indicating the requested operations are invalid.
	 */
	DynamicVBO();
	/**
	 * Initializes the VBO and IBO, and assigns indexes to each of the TerrainPolygons as the indexes
	 * appear in the VBO. This method must be invoked otherwise the draw method will cause the
	 * dynamic vbo to throw an exception.
	 * <br><br>
	 * <b><u>Note:</u>Re-adding a TerrainPolygon to the same VBO without removing it or adding a TerrainPolygon to
	 * two or more VBOs at the same time will cause the IBO indexes to be overwritten. This makes it
	 * functionally impossible to remove the TerrainPolygon from any VBOs but the last, a
	 * pseudo memory leak</b>
	 */
	void create(std::shared_ptr<FlexArray<TerrainPolygon>> &polys, std::shared_ptr<Texture> texture);
	/**
	 * Draws the terrain as specified by the index buffer object associated with this terrain renderer.
	 * @param cam the Camera that will be used to properly display the terrain
	 * @throws IllegalStateException - the create(...) method has not been called so there is no data
	 * in the buffer to draw
	 */
	void draw(Camera *cam);
	/**
     * <i> Javadoc comment pending finalized functionality. </i><br>
	 * Iteration 1: the number of vertices to remove is not strictly enforced
	 * likewise, it's assumed the vbo:ibo mapping is one to one, that is each
	 * of the ibo indexes maps one-to-one to a set of vertex data in the vbo
	 *
	 * @param iboIndexes an int[], where each element of the array is a value
	 * that will be removed from the vbo. The vertex removed for each element e, will
	 * be the one at ibo.get(e), however, this data will also be purged from the vbo
	 * when the index is removed from the ibo.
	 * @throws IllegalStateException - the create(...) method has not been called so there is no data
	 * in the buffer to draw
	 */
	void remove(FlexArray<int> iboIndexes);
	/**
	 * Adds a TerrainPolygon to this Dynamic VBO.
	 * <br><br>
	 * <b><u>Note:</u>Re-adding a TerrainPolygon to the same VBO without removing it or adding a TerrainPolygon to
	 * two or more VBOs at the same time will cause the IBO indexes to be overwritten. This makes it
	 * functionally impossible to remove the TerrainPolygon from any VBOs but the last, a
	 * pseudo memory leak</b>
	 * @param poly
	 * @throws IllegalStateException - the create(...) method has not been called so there is no data
	 * in the buffer to draw
	 */
	void add(TerrainPolygon &poly);
	/**
	 * Frees the allocated resources.
	 */
	~DynamicVBO();
};



#endif
