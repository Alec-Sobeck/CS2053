#pragma once

#include <glm/vec3.hpp>

///
/// Camera has all the information the server needs to move a player around properly based on keyboard input.
///
class Camera
{
public:
	glm::vec3 position;
	glm::vec3 rotation;
	float maxAngle;
	float minZoom;
	float maxZoom;
	float currentZoom;
	Camera();
	///
	/// Creates a new Camera with the provided position and rotation.
	/// \param pos a vec3 that is the initial position of the Camera
	/// \param rot a vec3 that is the initial rotation of the Camera
	///
	Camera(glm::vec3, glm::vec3);
	glm::vec3 getPosition();
	glm::vec3 getRotation();
	void setPosition(glm::vec3);
	void setRotation(glm::vec3);
	///
	/// Rotates the Camera by the rotation values specified in the Vector3
	/// \param rotation a vec3 that describes the additional rotation to apply to this Camera
	///
	void rotate(glm::vec3 rotation);
	void reduceRotation();
	float getX();
	float getY();
    float getZ();
	float getCurrentZoom();
	void setCurrentZoom(float);
	void addToCurrentZoom(float);
	void removeFromCurrentZoom(float);
	float getMaxZoom();
	float getMinZoom();
	void Camera::move(glm::vec3 val);
};

