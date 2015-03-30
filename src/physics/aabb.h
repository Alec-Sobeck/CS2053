#ifndef AABB_H
#define AABB_H

class AABB;
class AABS;

#include <string>
#include "glm/vec3.hpp"
#include "physics/aabs.h"

/**
 * AABB - "Axis Aligned Bounding Box" - is a rectangular prism that is aligned to the standard axes to aid
 * in collision detection.
 * <br>
 * http://www.euclideanspace.com/threed/animation/collisiondetect/index.htm?utm_source=[deliciuos]&utm_medium=twitter
 */
class AABB
{
public:
	/**
	 * Constructs a new AABB ("Axis Aligned Bounding Box"). The provided coordinates must assume that all
	 * sides of the bounding box align with either the x, y, or z axis for this bounding box to be accurate.
	 * @param xMin a float indicating where this AABB begins spanning the x axis
	 * @param yMin a float indicating where this AABB begins spanning the y axis
	 * @param zMin a float indicating where this AABB begins spanning the z axis
	 * @param xMax a float indicating where this AABB stops spanning the x axis
	 * @param yMax a float indicating where this AABB stops spanning the y axis
	 * @param zMax a float indicating where this AABB stops spanning the z axis
	 */
    AABB(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax);
   	/**
     * Constructs a new AABB ("Axis Aligned Bounding Box").
     * @param origin a Vector3 describing the origin (x,y,z position) of the AABB. The center position
     * @param halfSizes a Vector3 describing the half-width/height/depth of the AABB
     */
    AABB(glm::vec3 origin, glm::vec3 halfSizes);
    /**
	 * Checks this AABB against another AABB for overlap. If the bounding boxes are not properly aligned to the axes,
	 * this can provide weird results.
	 * @param other another AABB to check for overlap
	 * @return a boolean, true if the AABB overlap, and in all other cases false
	 */
	bool overlaps(AABB &other);
	/**
 	 * Checks this AABB against an AABS for overlap. 
	 * @return a boolean, true if the AABB and AANS overlap, and in all other cases false
	 */
	bool overlaps(AABS &other);
    /**
	 * Changes the values of xMin and xMax by the specified amount.
	 * @param amount a float which indicates how much to change the xMin and
	 * xMax; if this is negative it will subtract that amount from xMin and xMax
	 */
    void moveX(float amount);
	/**
	 * Changes the values of yMin and yMax by the specified amount.
	 * @param amount a float which indicates how much to change the yMin and
	 * yMax; if this is negative it will subtract that amount from yMin and yMax
	 */
    void moveY(float amount);
	/**
	 * Changes the values of zMin and zMax by the specified amount.
	 * @param amount a float which indicates how much to change the zMin and
	 * zMax; if this is negative it will subtract that amount from zMin and zMax
	 */
    void moveZ(float amount);
    void move(glm::vec3 amounts);
	/**
	* Formats the values in this AABB to something fairly clear and understandable.
	*/
	std::string toString();
	/*
	 * Centers the box on the specified position 
	 */
	void moveTo(float x, float y, float z)
	{
		float xHalfsize = (xMax - xMin) / 2;
		float yHalfsize = (yMax - yMin) / 2;
		float zHalfsize = (zMax - zMin) / 2;
		xMin = x - xHalfsize;
		xMax = x + xHalfsize;
		yMin = y - yHalfsize;
		yMax = y + yHalfsize;
		zMin = z - zHalfsize;
		zMax = z + zHalfsize;
	}
	float getXMin();
	float getXMax();
	float getYMin();
	float getYMax();
	float getZMin();
	float getZMax();
	float getYCenter();
	float getZCenter();
	float getXCenter();

	//Position data can be stored this way because the box is aligned along the x, y, and z axes.
	float xMin;
	float xMax;
	float yMin;
	float yMax;
	float zMin;
	float zMax;
};


#endif
