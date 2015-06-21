#pragma once

#include "glm/vec2.hpp"

///
/// AABB2 is a 2D rectangle that is aligned to the standard axes to aid in collision detection.
/// AABB2 differs from a Rectangle2 because a Rectangle2 does not have to have sides which are axis aligned, whereas an AABB2 does require
/// sides which align to the primary axes.
/// 
class AABB2D
{
public:
	/// 
	/// Constructs a new AABB2. 
	/// \param xMin a float indicating where this AABB begins spanning the x axis
	/// \param yMin a float indicating where this AABB begins spanning the y axis
	/// \param xMax a float indicating where this AABB stops spanning the x axis
	/// \param yMax a float indicating where this AABB stops spanning the y axis
	/// 
	AABB2D(float xMin, float yMin, float xMax, float yMax);
	/// 
    /// Constructs a new AABB ("Axis Aligned Bounding Box").
    /// \param origin a Vector3 describing the origin (x,y,z position) of the AABB. The center position
    /// \param halfSizes a Vector3 describing the half-width/height/depth of the AABB
    /// 
	AABB2D(glm::vec2 origin, glm::vec2 halfSizes);
	/// 
	/// Changes the values of xMin and xMax by the specified amount.
	/// \param amount a float which indicates how much to change the xMin and xMax; if this is negative it will subtract that amount from xMin and xMax
	/// 
    void moveX(float amount);
	/// 
	/// Changes the values of yMin and yMax by the specified amount.
	/// \param amount a float which indicates how much to change the yMin and yMax; if this is negative it will subtract that amount from yMin and yMax
	/// 
    void moveY(float amount);
    void move(glm::vec2 amounts);
	/// 
	/// Centers the box on the specified position 
	/// 
	void moveTo(float x, float y);	
	float getYCenter();
	float getXCenter();
	glm::vec2 center();	
	float xMin;
	float xMax;
	float yMin;
	float yMax;
};


