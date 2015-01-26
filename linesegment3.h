#ifndef LINESEGMENT3_H
#define LINESEGMENT3_H

#include "glm/vec3.hpp"
#include "linesegment.h"

class LineSegment3 : public LineSegment
{
public:
	LineSegment3(glm::vec3 point1, glm::vec3 point2);
};

#endif