
#include <vector>
#include "gamemath.h"
#include "separatingaxistest.h"

namespace separatingaxistest
{
///
/// Implements some cases of the Separating Axis Test. There are functions for the following so far:
///
/// 1. intersects(Hexagon2, Triangle2)
/// 2. intersects(Rectangle2, Circle2)
/// 3. intersects(Rectangle2, Rectangle2)
/// 
/// This is a rough port of the following:
/// http://gamedevelopment.tutsplus.com/tutorials/collision-detection-using-the-separating-axis-theorem--gamedev-169
/// \author Alec Sobeck
/// \author Matthew Robertson
///

///
/// Tests to see if a Rectangle2 intersects with another Rectangle2.
/// \param box1 a Rectangle2 which is one of the shapes for the intersection test
/// \param box2 a Rectangle2 which is one of the shapes for the intersection test
/// \return a bool - true if the rectangles intersect, otherwise false
///
bool intersects(const Rectangle2 &box1, const Rectangle2 &box2)
{
	//prepare the normals
	std::vector<glm::vec2> normals_box1 = getNormals(box1.points);
	std::vector<glm::vec2> normals_box2 = getNormals(box2.points);
	std::vector<glm::vec2> vecs_box1 = prepareVector(box1.points);
	std::vector<glm::vec2> vecs_box2 = prepareVector(box2.points);

	//results of P, Q
	std::vector<double> result_P1 = getMinMax(vecs_box1, normals_box1.at(1));
	std::vector<double> result_P2 = getMinMax(vecs_box2, normals_box1.at(1));
	std::vector<double> result_Q1 = getMinMax(vecs_box1, normals_box1.at(0));
	std::vector<double> result_Q2 = getMinMax(vecs_box2, normals_box1.at(0));

	//results of R, S
	std::vector<double> result_R1 = getMinMax(vecs_box1, normals_box2.at(1));
	std::vector<double> result_R2 = getMinMax(vecs_box2, normals_box2.at(1));
	std::vector<double> result_S1 = getMinMax(vecs_box1, normals_box2.at(0));
	std::vector<double> result_S2 = getMinMax(vecs_box2, normals_box2.at(0));

	bool separate_p = result_P1[1] < result_P2[0] || result_P2[1] < result_P1[0];
	bool separate_Q = result_Q1[1] < result_Q2[0] || result_Q2[1] < result_Q1[0];
	bool separate_R = result_R1[1] < result_R2[0] || result_R2[1] < result_R1[0];
	bool separate_S = result_S1[1] < result_S2[0] || result_S2[1] < result_S1[0];

	bool isSeparated = separate_p || separate_Q || separate_R || separate_S;
	return !isSeparated;
}

///
/// Tests to see if a Hexagon2 intersects with a Triangle2.
/// \param hex a Hexagon2 which is one of the shapes for the intersection test
/// \param tri a Triangle2 which is one of the shapes for the intersection test
/// \return a bool; true if the polygons intersect, otherwise false
///
bool intersects(const Hexagon2 &hex, const Triangle2 &tri)
{
	//prepare the normals
	std::vector<glm::vec2> normals_hex = getNormals(hex.points);
	std::vector<glm::vec2> normals_tri = getNormals(tri.points);

	std::vector<glm::vec2> vecs_hex = prepareVector(hex.points);
	std::vector<glm::vec2> vecs_tri = prepareVector(tri.points);
	bool isSeparated = false;

	//use hexagon's normals to evaluate
	for (int i = 0; i < normals_hex.size(); i++)
	{
		std::vector<double> result_box1 = getMinMax(vecs_hex, normals_hex.at(i));
		std::vector<double> result_box2 = getMinMax(vecs_tri, normals_hex.at(i));

		isSeparated = result_box1[1] < result_box2[0] || result_box2[1] < result_box1[0];
		if (isSeparated)
			break;
	}
	//use triangle's normals to evaluate
	if (!isSeparated)
	{
		for (int j = 1; j < normals_tri.size(); j++)
		{
			std::vector<double> result_P1 = getMinMax(vecs_hex, normals_tri.at(j));
			std::vector<double> result_P2 = getMinMax(vecs_tri, normals_tri.at(j));

			isSeparated = result_P1[1] < result_P2[0] || result_P2[1] < result_P1[0];
			if (isSeparated) break;
		}
	}

	return !isSeparated;
}

/**
* Tests to see if a Rectangle2 intersects with another Circle2.
* @param box a Rectangle2 which is one of the shapes for the intersection test
* @param circle a Circle2 which is one of the shapes for the intersection test
* @return a boolean; true if the polygons intersect, otherwise false
*/
bool intersects(const Rectangle2 &box, const Circle2 &circle)
{
	//prepare the vectors
	glm::vec2 c = circle.center;
	glm::vec2 v;
	glm::vec2 current_box_corner;
	glm::vec2 center_box = box.getCenter();

	float max = -pow(1.0f, 30.0f);
	glm::vec2 box2circle(c.x - center_box.x, c.y - center_box.y);
	glm::vec2 box2circle_normalised = glm::normalize(box2circle);

	//get the maximum
	for (int i = 0; i < 4 /*vertexCount of rectangle*/; i++)
	{
		current_box_corner = box.points[i];
		v = glm::vec2(
			current_box_corner.x - center_box.x,
			current_box_corner.y - center_box.y
			);
		float current_proj = glm::dot(v, box2circle_normalised);
		if (max < current_proj)
			max = current_proj;
	}

	if (box2circle.length() - max - circle.radius > 0 && box2circle.length() > 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

std::vector<glm::vec2> prepareVector(const Polygon2 &current_box)
{
	std::vector<glm::vec2> vecs_box;
	
	for (int i = 0; i < current_box.points.size(); i++)
	{
		glm::vec2 corner_box = current_box.points[i];
		vecs_box.push_back(corner_box);
	}
	return vecs_box;
}

std::vector<double> getMinMax(std::vector<glm::vec2> vecs_box, glm::vec2 axis)
{
	double min_proj_box = glm::dot(vecs_box.at(1), axis);
	double min_dot_box = 1;
	double max_proj_box = glm::dot(vecs_box.at(1), axis);
	double max_dot_box = 1;

	for (int j = 2; j < vecs_box.size(); j++)
	{
		double curr_proj = glm::dot(vecs_box.at(j), axis);
		//select the maximum projection on axis to corresponding box corners
		if (min_proj_box > curr_proj) 
		{
			min_proj_box = curr_proj;
			min_dot_box = j;
		}
		//select the minimum projection on axis to corresponding box corners
		if (curr_proj> max_proj_box) 
		{
			max_proj_box = curr_proj;
			max_dot_box = j;
		}
	}
	return std::vector<double>{
		min_proj_box,
			max_proj_box,
			min_dot_box,
			max_dot_box
	};
}



}