
#include <cmath>
#include <stdexcept>
#include "model.h"
#include "math/gamemath.h"

int getNextModelID()
{
    static int modelID = 0;
    return modelID++;
}

AABB Model::getAABB()
{
    return AABB(0,0,0,0,0,0);
}

void Model::onAABBCollision(AABB &boundsCollidedWith)
{

}

/**
 * Constructs a new Model with the specified ModelData object.
 * @param data a ModelData object that can be used to construct this Model
 */
Model::Model(std::vector<std::shared_ptr<MeshData>> data) : modelID(getNextModelID()), origin(glm::vec3(0, 0, 0)), rotationOnAxes(glm::vec3(0, 0, 0)),
        data(data), aabb(rotateAABB(AABB(0, 0, 0, 10, 10, 10))), scale(glm::vec3(1.0f, 1.0f, 1.0f))
{
}

Model::~Model()
{

}

AABB Model::rotateAABB(AABB aabb)
{
    if(1==1)
    {
//        return data.getAABB();
        return AABB(0.0f, 0.0f, 0.0f, 10.0f, 10.0f, 10.0f);
    }
    //TODO rotate the AABB
//		this doesnt work at all - vertices are botched srsly badly
    if(1==1)
        throw std::runtime_error("Any value given by this method is wrong. will fix");
    /*
    Vector3[] vertices = {
            new Vector3(aabb.getXMin(), aabb.getYMin(), aabb.getZMin()),
            new Vector3(aabb.getXMin(), aabb.getYMin(), aabb.getZMin()),
            new Vector3(aabb.getXMin(), aabb.getYMax(), aabb.getZMin()),
            new Vector3(aabb.getXMin(), aabb.getYMin(), aabb.getZMin()),
            new Vector3(aabb.getXMax(), aabb.getYMin(), aabb.getZMin()),
            new Vector3(aabb.getXMax(), aabb.getYMin(), aabb.getZMin()),
            new Vector3(aabb.getXMax(), aabb.getYMin(), aabb.getZMin()),
            new Vector3(aabb.getXMax(), aabb.getYMin(), aabb.getZMin())
    };



    return null;
    */
    return AABB(0,0,0,0,0,0);
}

/**
 * Tests this Model's AABB against another AABB for overlap
 * @param other another AABB to check for intersection
 * @return a boolean, true if the AABB overlap, otherwise false
 */
bool Model::intersections(AABB &other)
{
    return aabb.overlaps(other);
}

/**
 * Gets the Point3 that describes the relative origin of this Model. That is to say the translation applied
 * before drawing the Model.
 * @return a Point3 that describes the relative origin of the Model
 */
glm::vec3 Model::getOrigin()
{
    return origin;
}

/**
 * Sets the origin of this Model, which is the amount it is translated before being drawn.
 * @param origin a Point3 describing the new relative origin of this Model
 */
void Model::setOrigin(glm::vec3 origin)
{
    this->origin = origin;
}

/**
 * Sets the model scale to the scale that is input
 * @param scale
 */
void Model::scaleModel(glm::vec3 scale)
{
    this->scale = scale;
}

/**
 * Multiplies the appropriate axes of scale by amount
 * @param amount the amount to scale by
 * @param scaleX if the X axis is affected
 * @param scaleY if the Y axis is affected
 * @param scaleZ if the Z axis is affected
 */
void Model::scaleModel(float amount, bool scaleX, bool scaleY, bool scaleZ)
{
    if (scaleX)
        scale = glm::vec3(scale.x * amount, scale.y, scale.z);
    if (scaleY)
        scale = glm::vec3(scale.x, scale.y * amount, scale.z);
    if (scaleZ)
        scale = glm::vec3(scale.x, scale.y, scale.z * amount);
}

/**
 * Translates the model's origin The provided amount
 * @param amount a Vector3 describing the direction and amount of movement
 */
void Model::translate(glm::vec3 amount)
{
    origin = origin + amount;
}

/**
 * Gets the Vector3 that describes the rotation of this Model
 * @return a Vector3 that describes the rotation of this Model
 */
glm::vec3 Model::getRotationOnAxes()
{
    return rotationOnAxes;
}

/**
 * Rotates the Model by the rotation values specified in the Vector3
 * @param rotation a Vector3 that describes the additional rotation to apply to this Camera
 */
void Model::rotate(glm::vec3 rotation)
{
    setRotationOnAxes(glm::vec3(rotation.x + rotationOnAxes.x,
                                rotation.y + rotationOnAxes.y,
                                rotation.z + rotationOnAxes.z));
}

void Model::reduceRotation()
{
    setRotationOnAxes(glm::vec3(fmod(rotationOnAxes.x, (2 * PI)),
                                fmod(rotationOnAxes.y, (2 * PI)),
                                fmod(rotationOnAxes.z, (2 * PI))));
}

void Model::setRotationOnAxes(glm::vec3 rotationOnAxes)
{
    this->rotationOnAxes = rotationOnAxes;
    this->aabb = rotateAABB(AABB(0,0,0,10,10,10));
}

int Model::getID()
{
    return modelID;
}

void Model::createVBOs(std::map<std::string, std::shared_ptr<Texture>> textureMap)
{
    for(unsigned int i = 0; i < data.size(); i++)
    {
        std::cout << ">" << data[i]->associatedTextureName << "<"<< std::endl;
        if(overrideTexture)
        {
            vbos.push_back(std::shared_ptr<VBO>(new VBO(data[i], overrideTexture)));
        }
        else
        {
            vbos.push_back(std::shared_ptr<VBO>(new VBO(data[i], textureMap[data[i]->associatedTextureName])));
        }
    }
}

void Model::draw(Camera *camera)
{
    for(unsigned int i = 0; i < vbos.size(); i++)
    {
        vbos[i]->draw(camera);
    }
}



