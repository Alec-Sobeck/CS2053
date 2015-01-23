#ifndef AABS_H
#define AABS_H

#include "glm/vec3.hpp"
#include "polygon3.h"

/**
 * AABS - "Axis Aligned Bounding Sphere" is a sphere that is used to bound a model or object for the purposes
 * of collision test.
 * <br>
 * <u>http://www.euclideanspace.com/threed/animation/collisiondetect/index.htm?utm_source=[deliciuos]&utm_medium=twitter</u>
 * @author Alec Sobeck
 * @author Matthew Robertson
 */
class AABS
{
public:
	/**
	 * Creates a new Axis-Aligned-Bounding-Sphere with specified center and radius.
	 * @param x a float, the x coordinate of the center of the sphere
	 * @param y a float, the y coordinate of the center of the sphere
	 * @param z a float, the z coordinate of the center of the sphere
	 * @param radius a float, the radius of the circle
	 */
	AABS(float x, float y, float z, float radius);
	/**
	 * Gets the surface area of this sphere. The SA of a sphere is (4 * PI * r^2).
	 * @return a float which is the surface area of this sphere
	 */
    float surfaceArea();
	/**
	 * Gets the volume of this sphere. The volume of a sphere is (4/3 * PI * r^3).
	 * @return a float which is the volume of this sphere
	 */
    float volume();
	/**
	 * Tests this AABS against another to check for overlap.
	 * @param other
	 * @return
	 */
    bool overlaps(AABS &other);
	/**
	 * Seperating axis-based test
	 * @param triangle - Polygon to be checked
	 * @return true if the sphere collides with the triangle. Returns false if provided poly is not a triangle
	 */
    bool intersectsTriangle(Polygon3 &triangle);
private:
	/** The x coordinate of the center point of the sphere. */
	const float x;
	/** The y coordinate of the center point of the sphere. */
	const float y;
	/** The z coordinate of the center point of the sphere. */
	const float z;
	/** Radius of the sphere */
	const float radius;
};

#endif
