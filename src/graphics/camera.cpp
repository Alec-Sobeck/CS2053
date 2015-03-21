
#include <cmath>
#include "camera.h"
#include "math/gamemath.h"

Camera::Camera() : position(glm::vec3(0, 0, 0)), rotation(glm::vec3(0, 0, 0)), maxAngle(85.0f), minZoom(0.5f), maxZoom(1.5f), currentZoom(1.0f)
{

}

Camera::Camera(glm::vec3 pos, glm::vec3 rot) : position(pos), rotation(rot), maxAngle(85.0f), minZoom(0.5f), maxZoom(1.5f), currentZoom(1.0f)
{
}

glm::vec3 Camera::getPosition()
{
    return position;
}

glm::vec3 Camera::getRotation()
{
    return rotation;
}

void Camera::setPosition(glm::vec3 newPos)
{
    this->position = newPos;
}

void Camera::setRotation(glm::vec3 newRot)
{
    this->rotation = newRot;
    reduceRotation();
}

void Camera::rotate(glm::vec3 rotation)
{
    setRotation(glm::vec3(rotation.x + this->rotation.x, rotation.y + this->rotation.y, rotation.z + this->rotation.z));
}

void Camera::reduceRotation()
{
    if(rotation.x > toRad(maxAngle))
    {
        rotation = glm::vec3(toRad(85), rotation.y, rotation.z);
    }
    else if (rotation.x < -toRad(maxAngle))
    {
        rotation = glm::vec3(-toRad(85), rotation.y, rotation.z);
    }

    rotation = glm::vec3(fmod(rotation.x, 2 * PI),
                         fmod(rotation.y, 2 * PI),
                         fmod(rotation.z, 2 * PI));
}

float Camera::getX()
{
    return position.x;
}

float Camera::getY()
{
    return position.y;
}

float Camera::getZ()
{
    return position.z;
}

float Camera::getCurrentZoom()
{
    return currentZoom;
}

void Camera::setCurrentZoom(float currentZoom)
{
    currentZoom = currentZoom;
    if(currentZoom < minZoom)
        currentZoom = minZoom;
    if(currentZoom > maxZoom)
        currentZoom = maxZoom;
}

void Camera::addToCurrentZoom(float value)
{
    currentZoom += value;
    if(currentZoom < minZoom)
        currentZoom = minZoom;
    if(currentZoom > maxZoom)
        currentZoom = maxZoom;
}

void Camera::removeFromCurrentZoom(float value)
{
    currentZoom -= value;
    if(currentZoom < minZoom)
        currentZoom = minZoom;
    if(currentZoom > maxZoom)
        currentZoom = maxZoom;
}

float Camera::getMaxZoom()
{
	return maxZoom;
}

float Camera::getMinZoom()
{
	return minZoom;
}
#include<iostream>
void Camera::move(glm::vec3 val)
{
	position.x = position.x + val.x;
	position.y = position.y + val.y;
	position.z = position.z + val.z;
}