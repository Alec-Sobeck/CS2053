#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <map>
#include <glm/vec3.hpp>
#include "math/ioctreeelement.h"
#include "physics/aabb.h"
#include "world/meshdata.h"
#include "graphics/camera.h"
#include "render/vbo.h"
#include "render/texture.h"

int getNextModelID();

/**
 * Describes a basic 3d model.
 * @author Matt Robertson
 * @author Alec Sobeck
 */
class Model : public IOctreeElement
{
private:
    int modelID;

protected:
	glm::vec3 origin;
	glm::vec3 rotationOnAxes;
	AABB aabb;
	glm::vec3 scale;
public:
	std::vector<std::shared_ptr<MeshData>> data;
	std::vector<std::shared_ptr<VBO>> vbos;
	std::shared_ptr<Texture> overrideTexture;
	void onAABBCollision(AABB &boundsCollidedWith) override;

	AABB getAABB() override;
	AABB generateAABB();
	~Model();
	/**
	 * Constructs a new Model with the specified ModelData object.
	 * @param data a ModelData object that can be used to construct this Model
	 */
	Model(std::vector<std::shared_ptr<MeshData>> data);
	/**
	 * Tests this Model's AABB against another AABB for overlap
	 * @param other another AABB to check for intersection
	 * @return a boolean, true if the AABB overlap, otherwise false
	 */
	bool intersections(AABB &other);
	/**
	 * Gets the Point3 that describes the relative origin of this Model. That is to say the translation applied
	 * before drawing the Model.
	 * @return a Point3 that describes the relative origin of the Model
	 */
	glm::vec3 getOrigin();
	/**
	 * Sets the origin of this Model, which is the amount it is translated before being drawn.
	 * @param origin a Point3 describing the new relative origin of this Model
	 */
	void setOrigin(glm::vec3 origin);
    /**
	 * Sets the model scale to the scale that is input
	 * @param scale
	 */
	void scaleModel(glm::vec3 scale);
	/**
	 * Multiplies the appropriate axes of scale by amount
	 * @param amount the amount to scale by
	 * @param scaleX if the X axis is affected
	 * @param scaleY if the Y axis is affected
	 * @param scaleZ if the Z axis is affected
	 */
	void scaleModel(float amount, bool scaleX, bool scaleY, bool scaleZ);
	/**
	 * Translates the model's origin The provided amount
	 * @param amount a Vector3 describing the direction and amount of movement
	 */
	void translate(glm::vec3 amount);
    /**
	 * Gets the Vector3 that describes the rotation of this Model
	 * @return a Vector3 that describes the rotation of this Model
	 */
	glm::vec3 getRotationOnAxes();
	/**
	 * Rotates the Model by the rotation values specified in the Vector3
	 * @param rotation a Vector3 that describes the additional rotation to apply to this Camera
	 */
	void rotate(glm::vec3 rotation);
	/**
	 * Ensures the rotation falls between 0 and 2PI on each axis
	 */
	void reduceRotation();
	/**
	 * Sets the Vector3 that controls rotation for this Model to a new Vector3.
	 * This will recalculate the AABB for this Model.
	 * @param rotationOnAxes a Vector3 that describes the rotation of this Model
	 */
	void setRotationOnAxes(glm::vec3 rotationOnAxes);
    /**
	 * Gets the ModelData associated with this Model. This may not be very useful after the Model has been initialized.
	 * @return a ModelData object which describes this Model
	 */
	int getID();
    void createVBOs(std::map<std::string, std::shared_ptr<Texture>> textureMap);
    void draw(Camera *camera);
};

inline bool operator<(const Model &first, const Model &other)
{
    return false;
}


#endif


