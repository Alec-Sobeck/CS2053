
#include <glbinding/gl/gl.h>
#include "render/dynamicvbo.h"

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

void DynamicVBO::create(std::shared_ptr<std::vector<TerrainPolygon>> &polys, std::shared_ptr<Texture> terrainTexture)
{
    this->texture = terrainTexture;

	int vertexCount = 0;
    for(int i = 0; i < polys->size(); i++)
    {
        vertexCount += polys->at(i).getVertexCount();
    }
    vertCount = vertexCount;
    int totalNumberOfElements = vertexCount * TerrainPolygon::TOTAL_ROW_SIZE;
    float *rawData = new float[totalNumberOfElements];
    int IBOIndexCounter = 0;

    int j = 0; //Raw Data Indexer
    for(int i = 0; i < polys->size(); i++)
    {
        TerrainPolygon *p = &polys->at(i);
        RawPolygonData f = p->getRawData();
        for(int i = 0; i < f.size; i++,j++)
        {
            rawData[j] = f.data[i];
        }
        int *val = constructRange(IBOIndexCounter, IBOIndexCounter + p->getVertexCount());
        p->setIBOIndexes(val);
        IBOIndexCounter += p->getVertexCount();
    }
    float* vertex_buffer_data = new float[totalNumberOfElements];
    for(int i = 0; i < totalNumberOfElements; i++)
    {
        vertex_buffer_data[i] = rawData[i];
    }
    vbo = vertex_buffer_data;

    unsigned int* intBuffer = new unsigned int[vertexCount];
    for(unsigned int i = 0; i < IBOIndexCounter; i++)
        intBuffer[i] = i;
    ibo = intBuffer;
    indicesCount = totalNumberOfElements / TerrainPolygon::TOTAL_ROW_SIZE;

    vertexBufferID = createVBOID();
    indexBufferID = createVBOID();

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, totalNumberOfElements * sizeof(float), vertex_buffer_data, GL_DYNAMIC_DRAW);
    std::cout << "DynamicVBO[SIZE]>" << totalNumberOfElements << std::endl;
    initialized = true;

    delete[] rawData;
}

void DynamicVBO::draw(Camera *cam)
{
    if(!initialized)
    {
        return;
    }
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glLoadIdentity();
   
    // Translate to model co-ordinates, based on the origin of the shape
    setLookAt(cam);
    if(texture)
    {
		glEnable(GL_TEXTURE_2D);
        texture->bind(); 
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
	
	glDrawArrays(GL_TRIANGLES, 0, vertCount);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void DynamicVBO::remove(std::vector<int> iboIndexes)
{
    if(!initialized)
    {
        return;
    }
    //ASSUMPTION: 1 iboIndexes element : 1 vertex
    int verts = iboIndexes.size();

    for(int i = 0; i < indicesCount; i++)
    {
        std::cout << i << "> " << ibo[i] << std::endl;
    }

    //Figure out what values are actually stored in the ibo at the specified indexes
	std::vector<int> valuesAtIndexes(iboIndexes.size());
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

	std::vector<float> valuesAtVBOEnd(iboIndexes.size() * TerrainPolygon::TOTAL_ROW_SIZE);
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
    //Should this offset be zero? minimum changed index?
    glBufferSubData(GL_ARRAY_BUFFER, 0/*(vertCount) * VAL_PER_VERT * 4*/, iboIndexes.size(), vbo);

    //At this point the values at the end of the vbo have been shifted to wherever the things were before
    //So we have to update the ibo values.

    // Update the indexes in the IBO, first bind the IBO
    glBindBuffer(GL_ARRAY_BUFFER, indexBufferID);
	std::vector<int> valuesAtIboEnd(iboIndexes.size());
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
    //Should the offset be 0? perhaps the index where I shifted stuff to?
    glBufferSubData(GL_ARRAY_BUFFER, 0/*(indicesCount) * 4*/, iboIndexes.size(), ibo);
    // And of course unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Update vertex counts
    vertCount -= verts;
    indicesCount -= verts;
}

void DynamicVBO::add(TerrainPolygon &poly)
{
    if(!initialized)
    {
        return;
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
    RawPolygonData data = poly.getRawData();
    for(int k = 0, i = vertCount * TerrainPolygon::TOTAL_ROW_SIZE;
        i < (vertCount + verts) * TerrainPolygon::TOTAL_ROW_SIZE;
        i++, k++)
    {
        vbo[i] = data.data[k];
    }
    delete[] data.data;

    glBufferSubData(GL_ARRAY_BUFFER,
            0,
            (vertCount + verts) * TerrainPolygon::TOTAL_ROW_SIZE,
            vbo);

    // Update the indexes in the IBO, second bind the IBO
    glBindBuffer(GL_ARRAY_BUFFER, indexBufferID);
    for(int i = indicesCount, k = 0; i < indicesCount + verts; i++, k++)
    {
        ibo[i] = indexes[k];
    }
    glBufferSubData(GL_ARRAY_BUFFER,
            0,
            indicesCount + verts,
            ibo);

    // And of course unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Update vertex counts
    vertCount += verts;
    indicesCount += verts;
}

DynamicVBO::~DynamicVBO()
{
    GLuint *ptr1 = new GLuint[1];
    ptr1[0] = vertexBufferID;
    GLuint *ptr2 = new GLuint[1];
    ptr2[0] = indexBufferID;
    glDeleteBuffers(1, ptr1);
    glDeleteBuffers(1, ptr2);
}
