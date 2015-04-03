#ifndef ENGINE_PATHFINDER_H
#define ENGINE_PATHFINDER_H

#include <vector>
#include <memory>
#include <list>
#include "grid.h"
#include <glm/vec2.hpp>

class PlannerNode;

class PlannerNode
{
public:
	std::shared_ptr<PlannerNode> parent;
	int cellX, cellY;
	float givenCost;
	float finalCost;
	PlannerNode(int x, int y);
	PlannerNode();
	void setParent(std::shared_ptr<PlannerNode> p);
};

class PathFinder
{
public:
	std::shared_ptr<Grid> worldGrid;
	std::vector<std::shared_ptr<PlannerNode>> openList;
	std::vector<std::shared_ptr<PlannerNode>> closeList;
	std::shared_ptr<PlannerNode> currentNode;
	glm::vec2 goalPosition;
	PathFinder(std::shared_ptr<Grid> worldGrid);
	std::shared_ptr<PlannerNode> computePath(glm::vec2 start, glm::vec2 goal);
	std::shared_ptr<PlannerNode> popLowestNode();
	void addSuccessor(int x, int y, float cost);
};



#endif