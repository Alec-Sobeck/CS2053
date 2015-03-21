
#include <glbinding/gl/gl.h>
#include "render/dynamicvbo.h"


TerrainPolygon _p(
        FlexArray<glm::vec3>({
                glm::vec3(3.0f,  1.0f, -1.0f),
                glm::vec3(3.0f,  1.0f,  1.0f),
                glm::vec3(3.0f, -1.0f,  1.0f),
                glm::vec3(3.0f, -1.0f, -1.0f)
        }),
        FlexArray<float>({
                0.0f,1.0f,1.0f,1.0f,
                0.0f,1.0f,1.0f,1.0f,
                0.0f,1.0f,1.0f,1.0f,
                0.0f,1.0f,1.0f,1.0f
        }),
        FlexArray<float>({
                1.0f, 1.0f,
                0.0f, 1.0f,
                0.0f, 0.0f,
                1.0f, 0.0f
        })
);
TerrainPolygon _p1(
        FlexArray<glm::vec3>({
                glm::vec3(5.0f,  1.0f, -1.0f),
                glm::vec3(5.0f,  1.0f,  1.0f),
                glm::vec3(5.0f, -1.0f,  1.0f),
                glm::vec3(5.0f, -1.0f, -1.0f)
        }),
        FlexArray<float>({
                0.0f,0.0f,1.0f,1.0f,
                0.0f,1.0f,1.0f,1.0f,
                0.0f,1.0f,1.0f,1.0f,
                0.0f,1.0f,1.0f,1.0f
        }),
        FlexArray<float>({
                1.0f, 1.0f,
                0.0f, 1.0f,
                0.0f, 0.0f,
                1.0f, 0.0f
        })
);
TerrainPolygon _p2(
        FlexArray<glm::vec3>({
                glm::vec3(7.0f,  1.0f, -1.0f),
                glm::vec3(7.0f,  1.0f,  1.0f),
                glm::vec3(7.0f, -1.0f,  1.0f),
                glm::vec3(7.0f, -1.0f, -1.0f)
        }),
        FlexArray<float>({
                0.0f,1.0f,1.0f,1.0f,
                0.0f,1.0f,1.0f,1.0f,
                0.0f,1.0f,1.0f,1.0f,
                0.0f,1.0f,1.0f,1.0f
        }),
        FlexArray<float>({
                1.0f, 1.0f,
                0.0f, 1.0f,
                0.0f, 0.0f,
                1.0f, 0.0f
        })
);
TerrainPolygon _p3(
        FlexArray<glm::vec3> {
                glm::vec3(10.0f,  1.0f, -1.0f),
                glm::vec3(10.0f,  1.0f,  1.0f),
                glm::vec3(10.0f, -1.0f,  1.0f),
                glm::vec3(10.0f, -1.0f, -1.0f)
        },
        FlexArray<float>({
                0.0f,0.0f,1.0f,1.0f,
                0.0f,1.0f,1.0f,1.0f,
                0.0f,1.0f,1.0f,1.0f,
                0.0f,1.0f,1.0f,1.0f
        }),
        FlexArray<float>({
                1.0f, 1.0f,
                0.0f, 1.0f,
                0.0f, 0.0f,
                1.0f, 0.0f
        })
);

using namespace gl;

int *constructRange(int a, int b)
{
    int *vals = new int[b - a];
    for(int i = 0; i < b - a; i++)
    {
        vals[i] = a + i;
    }
    return vals;
}

DynamicVBO::DynamicVBO() : vertexBufferID(0), indexBufferID(0),
    indicesCount(0), vertCount(0), texture(std::shared_ptr<Texture>(nullptr)), initialized(false)
{
}

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
void DynamicVBO::create(std::shared_ptr<FlexArray<TerrainPolygon>> &polys, std::shared_ptr<Texture> terrainTexture)
{
    this->texture = terrainTexture;
//    polys = std::shared_ptr<FlexArray<TerrainPolygon>>(new FlexArray<TerrainPolygon>({_p, _p1, _p2, _p3}));

    int vertexCount = 0;
    for(int i = 0; i < polys->size(); i++)
    {
        vertexCount += polys->at(i).getVertexCount();
    }
    vertCount = vertexCount;
    int totalNumberOfElements = vertexCount * TerrainPolygon::TOTAL_ROW_SIZE;

    //std::cout << "!" << totalNumberOfElements << std::endl;
    float *rawData = new float[totalNumberOfElements];
    int IBOIndexCounter = 0;


    int j = 0; //Raw Data Indexer
    for(int i = 0; i < polys->size(); i++)
    {
        TerrainPolygon *p = &polys->at(i);
        RawPolygonData f = p->getRawData();

        /*
        if(p->getVertexCount() > 0)
        {
            rawData[6] = 1.0f;
            rawData[7] = 1.0f;
            rawData[8] = 1.0f;
            rawData[9] = 1.0f;
        }
*/

        for(int i = 0; i < f.size; i++,j++)
        {
            rawData[j] = f.data[i];
        }
        int *val = constructRange(IBOIndexCounter, IBOIndexCounter + p->getVertexCount());
        p->setIBOIndexes(val);
        IBOIndexCounter += p->getVertexCount();
        // THIS IS A SERIOUS MEMORY LEAK
        //delete[] f.data;
    }
    float* vertex_buffer_data = new float[totalNumberOfElements]/*rawData.length*/;
    for(int i = 0; i < totalNumberOfElements/*rawData's size*/; i++)
    {
        vertex_buffer_data[i] = rawData[i];
    }
    // vertex_buffer_data.put(rawData);
    //vertex_buffer_data.rewind();
    vbo = vertex_buffer_data;

    unsigned int* intBuffer = new unsigned int[vertexCount] /*IBOIndexCounter*/;
    for(unsigned int i = 0; i < IBOIndexCounter; i++)
        intBuffer[i] = i;
    //intBuffer.rewind();
    ibo = intBuffer;
    indicesCount = totalNumberOfElements/*rawData's size*/ / TerrainPolygon::TOTAL_ROW_SIZE;

    vertexBufferID = createVBOID();
    indexBufferID = createVBOID();

   // std::cout << "!" << glBindBuffer << ":" << vertexBufferID << std::endl;
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, totalNumberOfElements * sizeof(float)/*rawData's size*/, vertex_buffer_data, GL_DYNAMIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    std::cout << "DynamicVBO[SIZE]>" << totalNumberOfElements << std::endl;
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexCount * sizeof(unsigned int), intBuffer, GL_DYNAMIC_DRAW);
    initialized = true;

    delete[] rawData;
}

/**
 * Draws the terrain as specified by the index buffer object associated with this terrain renderer.
 * @param cam the Camera that will be used to properly display the terrain
 * @throws IllegalStateException - the create(...) method has not been called so there is no data
 * in the buffer to draw
 */
void DynamicVBO::draw(Camera *cam)
{
    if(!initialized)
    {
        return;
        // TODO - throw exception on failure instead?
        //throw IllegalStateException("The VBO has not been initialized with any data.");
    }
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glLoadIdentity();
   
    //glColor3f(1.0f, 1.0f, 1.0f);
    // Translate to model co-ordinates, based on the origin of the shape
    setLookAt(cam);
    if(texture)
    {
		glEnable(GL_TEXTURE_2D);
        texture->bind(); // terrain texture?
    }
    else
    {
		glDisable(GL_TEXTURE_2D);
        std::cout << "failure to bind texture: nullptr" << std::endl;
    }
    int firstVert = 0;
    int firstNormal = 12;
    int firstColour = 24;
    int firstTextureCoord = 40;
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glVertexPointer(3, GL_FLOAT, 48, (void*)(0));
    glNormalPointer(GL_FLOAT, 48, (void*)(12));
    glColorPointer(4, GL_FLOAT, 48, (void*)(24));
    glTexCoordPointer(2, GL_FLOAT, 48, (void*)(40));

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    //std::cout << "Error1:" << glGetError() << std::endl;
  //  glDrawElements(GL_TRIANGLES, vertCount, GL_UNSIGNED_INT, 0);
    //std::cout << "Error2:" << glGetError() << std::endl;

    glDrawArrays(GL_TRIANGLES, 0, vertCount);
  //  std::cout << "Error!:" << glGetError() << std::endl;
//
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

   // std::cout << "Error3:" << glGetError() << std::endl;
}

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
void DynamicVBO::remove(FlexArray<int> iboIndexes)
{
    if(!initialized)
    {
        return;
        // TODO -- throw exception on failure?
        //throw IllegalStateException("The VBO has not been initialized with any data.");
    }
    //ibo.clear();
    //vbo.clear();
    //ibo.rewind();
    //vbo.rewind();
    //ASSUMPTION: 1 iboIndexes element : 1 vertex
    int verts = iboIndexes.size();

    for(int i = 0; i < indicesCount; i++)
    {
        std::cout << i << "> " << ibo[i] << std::endl;
    }

    //Figure out what values are actually stored in the ibo at the specified indexes
    FlexArray<int> valuesAtIndexes(iboIndexes.size());
    for(int i = 0; i < iboIndexes.size(); i++)
    {
        std::cout << i << "> " << std::endl;
        valuesAtIndexes[i] = ibo[iboIndexes[i]];
        std::cout << "valuesAtIndexes[" << i << "]=" << valuesAtIndexes[i];
    }
    //A problem that's going to occur here, I think, is that if a vertex is shared
    //then when I update the indexes and change stuff it'll break

    // Update vertices in the VBO, first bind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    //vbo.rewind();

    FlexArray<float> valuesAtVBOEnd(iboIndexes.size() * TerrainPolygon::TOTAL_ROW_SIZE);
    for(int i = verts * TerrainPolygon::TOTAL_ROW_SIZE - 1,
        j = (indicesCount * TerrainPolygon::TOTAL_ROW_SIZE) - 1; i >= 0; i--, j--)
    {
        valuesAtVBOEnd[i] = vbo[j];
        vbo[j] = 0;
    }
    int count = 0;
    for(int i = 0; i < iboIndexes.size(); i++)
    {
        for(int j = 0; j < TerrainPolygon::TOTAL_ROW_SIZE; j++)
        {
            vbo[iboIndexes[i] * TerrainPolygon::TOTAL_ROW_SIZE + j] = valuesAtVBOEnd[count++];
        }
    }
//			vbo.flip();
    //Should this offset be zero? minimum changed index?
    glBufferSubData(GL_ARRAY_BUFFER, 0/*(vertCount) * VAL_PER_VERT * 4*/, iboIndexes.size(), vbo);

    //At this point the values at the end of the vbo have been shifted to wherever the things were before
    //So we have to update the ibo values.

    // Update the indexes in the IBO, first bind the IBO
    glBindBuffer(GL_ARRAY_BUFFER, indexBufferID);
//		ibo.rewind();
    FlexArray<int> valuesAtIboEnd(iboIndexes.size());
    for(int i = verts - 1, j = indicesCount - 1; i >= 0; i--, j--)
    {
        valuesAtIboEnd[i] = ibo[j];
        ibo[j] = 0;
    }
    for(int i = 0; i < iboIndexes.size(); i++)
    {
        ibo[iboIndexes[i]] = valuesAtIboEnd[i];
    }

    int lowerBound = indicesCount - verts;
    int upperBound = indicesCount;
    //This step can probably be optimized or skipped somehow
    for(int i = 0, x = 0; i < indicesCount; i++)
    {
        x = ibo[i];
        if(x < upperBound && x >= lowerBound)
        {
            ibo[i] = iboIndexes[upperBound - x - 1];
        }
    }
//			ibo.flip();
    //Should the offset be 0? perhaps the index where I shifted stuff to?
    glBufferSubData(GL_ARRAY_BUFFER, 0/*(indicesCount) * 4*/, iboIndexes.size(), ibo);
    // And of course unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Update vertex counts
    vertCount -= verts;
    indicesCount -= verts;
}

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
void DynamicVBO::add(TerrainPolygon &poly)
{
    if(!initialized)
    {
        return;
        // TODO- throw exception on failure?
        //throw IllegalStateException("The VBO has not been initialized with any data. To add initial data, use the create(...) method instead. ");
    }

    int verts = poly.getVertexCount();
    int* indexes = constructRange(indicesCount, indicesCount + verts);
    poly.setIBOIndexes(indexes);

    //Note the offset in glBufferSubData(...)
    //First of all, it's the offset in bytes not data values.
    //Second, it's only as far into the buffer as we need to copy... basically we're appending after
    //that byte in the buffer. So, the * 12 and * 4 are hardcoded and not strictly correct. It may
    //not be the case that each vertex has exactly 12 floats (of size 4), which would break this.
    //The same follows for the IBO call below - though we can get away with a bit more because we'll likely
    //always use ints for the IBO

    // Update vertices in the VBO, first bind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    //vbo.rewind();
    RawPolygonData data = poly.getRawData();
    for(int k = 0, i = vertCount * TerrainPolygon::TOTAL_ROW_SIZE;
        i < (vertCount + verts) * TerrainPolygon::TOTAL_ROW_SIZE;
        i++, k++)
    {
        vbo[i] = data.data[k];
    }
    delete[] data.data;

    //vbo.position(vertCount * TerrainPolygon::TOTAL_ROW_SIZE);
    //vbo.limit((vertCount + verts) * TerrainPolygon::TOTAL_ROW_SIZE);
    //vbo.put(poly.getRawData());
    //vbo.flip();
    glBufferSubData(GL_ARRAY_BUFFER,
            0/*(vertCount) * 12*/,
            (vertCount + verts) * TerrainPolygon::TOTAL_ROW_SIZE,
            vbo);

    // Update the indexes in the IBO, second bind the IBO
    glBindBuffer(GL_ARRAY_BUFFER, indexBufferID);
    //ibo.rewind();
//		ibo.position(indicesCount);
//		ibo.limit(indicesCount + verts);
//		ibo.put(indexes);
    for(int i = indicesCount, k = 0; i < indicesCount + verts; i++, k++)
    {
        ibo[i] = indexes[k];
    }
    //ibo.flip();
    glBufferSubData(GL_ARRAY_BUFFER,
            0/*(indicesCount) * 4*/,
            indicesCount + verts,
            ibo);

    // And of course unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Update vertex counts
    vertCount += verts;
    indicesCount += verts;
}

/**
 * Frees the memory allocated to VRam.
 */
DynamicVBO::~DynamicVBO()
{
    GLuint *ptr1 = new GLuint[1];
    ptr1[0] = vertexBufferID;
    GLuint *ptr2 = new GLuint[1];
    ptr2[0] = indexBufferID;
    glDeleteBuffers(1, ptr1);
    glDeleteBuffers(1, ptr2);
//    delete[] ibo;
//    delete[] vbo;
}
