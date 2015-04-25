
#include "polygonmath.h"


bool containsPoint(const std::vector<glm::vec2> &points, glm::vec2 point) 
{
	//@TODO test whether or not this actually works after being ported over.
	size_t i, j;
	bool c = false;
	for (i = 0, j = points.size() - 1; i < points.size(); j = i++)
	{
		if (((points[i].y > point.y) != (points[j].y > point.y)) && 
			(point.x < (points[j].x - points[i].x) * (point.y - points[i].y) / (points[j].y - points[i].y) + points[i].x))			
		{
			c = !c;
		}
	}
	return c;
}

void rotateOnVertex(std::vector<glm::vec2> &points, int vertexIndex, double angleOfRotation)
{
	rotateOnPoint(points, points[vertexIndex], angleOfRotation);
}

void rotateOnPoint(std::vector<glm::vec2> &points, glm::vec2 pointRotatedOn, double angleOfRotation)
{
	//TODO this seems to work - but needs more testing
	//TODO round off the errors that are to the effect of "n * 10^-16? 
	double s = sin(angleOfRotation);
	double c = cos(angleOfRotation);
	double xOffset = pointRotatedOn.x;
	double yOffset = pointRotatedOn.y;
	for (unsigned int i = 0; i < points.size(); i++)
	{
		//Moves the point relative to the origin
		double oldX = points[i].x - xOffset;
		double oldY = points[i].y - yOffset;
		//Rotate (this is a cheap inline of the 2D rotation matrix)
		double newX = oldX * c - oldY * s;
		double newY = oldX * s + oldY * c;
		//Move them back and add back the offset moving to the origin originally
		points[i] = glm::vec2(newX + xOffset, newY + yOffset);
	}
}

std::vector<glm::vec2> getNormals(const std::vector<glm::vec2> &points)
{
	std::vector<glm::vec2> normals;
	for (int i = 0; i < static_cast<int>(points.size()) - 1; i++)
	{
		glm::vec2 currentNormal(
			points[i + 1].x - points[i].x,
			points[i + 1].y - points[i].y
			);
		normals.push_back(currentNormal);
	}
	normals.push_back(glm::vec2(
		points[1].x - points[points.size() - 1].x,
		points[1].y - points[points.size() - 1].y
		));
	return normals;
}