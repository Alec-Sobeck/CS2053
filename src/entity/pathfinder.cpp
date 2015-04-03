#include <cmath>
#include "pathfinder.h"

///
/// Define PlannerNode class methods.
/// 

PlannerNode::PlannerNode(int x, int y) : cellX(x), cellY(y), parent(nullptr)
{
}

void PlannerNode::setParent(std::shared_ptr<PlannerNode> p)
{
	parent = p;
}

///
/// Define PathFinder class
///

PathFinder::PathFinder(std::shared_ptr<Grid> worldGrid) : worldGrid(worldGrid)
{ 
}

PlannerNode::PlannerNode()
{

}

std::shared_ptr<PlannerNode> PathFinder::computePath(glm::vec2 start, glm::vec2 goal)
{
	if (worldGrid->atExactCell(start.x, start.y) || worldGrid->atExactCell(start.x, start.y))
	{
		return nullptr;
	}
	goalPosition = goal;
	float maxDistance = static_cast<float>(sqrt((start.x - goal.x) * (start.x - goal.x) + (start.y - goal.y) * (start.y - goal.y)));
	int x = static_cast<int>(start.x);
	int y = static_cast<int>(start.y);
	std::shared_ptr<PlannerNode> rootNode(new PlannerNode(x, y));
	rootNode->givenCost = 0.0f;
	rootNode->finalCost = 0.0f;
	openList.push_back(rootNode);

	while (openList.size() > 0)
	{
		currentNode = popLowestNode();
		if (currentNode->cellX == goal.x && currentNode->cellY == goal.y) 
			break;
		x = currentNode->cellX;
		y = currentNode->cellY;
		int maxX = worldGrid->cellCountWidth;
		int maxY = worldGrid->cellCountHeight;

		if (x + 1 < maxX && worldGrid->atExactCell(x + 1, y) == 0)
			addSuccessor(x + 1, y, 10.0f);
		if (x + 1 < maxX && y + 1 < maxY && worldGrid->atExactCell(x + 1, y + 1) == 0)
			addSuccessor(x + 1, y + 1, 14.0f);
		if (y + 1 < maxY && worldGrid->atExactCell(x, y + 1) == 0)
			addSuccessor(x, y + 1, 10.0f);
		if (x - 1 > 0 && y + 1 < maxY && worldGrid->atExactCell(x - 1, y + 1) == 0)
			addSuccessor(x - 1, y + 1, 14.0f);
		if (x - 1 > 0 && worldGrid->atExactCell(x - 1, y) == 0)
			addSuccessor(x - 1, y, 10.0f);
		if (x - 1 > 0 && y - 1 > 0 && worldGrid->atExactCell(x - 1, y - 1) == 0)
			addSuccessor(x - 1, y - 1, 14.0f);
		if (y - 1 > 0 && worldGrid->atExactCell(x, y - 1) == 0)
			addSuccessor(x, y - 1, 10.0f);
		if (x + 1 < maxX && y - 1 > 0 && worldGrid->atExactCell(x + 1, y - 1) == 0)
			addSuccessor(x + 1, y - 1, 14.0f);
		closeList.push_back(currentNode);
	}
	return currentNode;
}

std::shared_ptr<PlannerNode> PathFinder::popLowestNode()
{
	std::shared_ptr<PlannerNode> lowestNode = openList[0];
	int index = 0;
	for (int i = 1; i < openList.size(); i++)
	{
		std::shared_ptr<PlannerNode> pn = openList[i];
		if (lowestNode->finalCost > pn->finalCost)
		{
			lowestNode = pn;
			index = i;
		}
	}
	openList.erase(openList.begin() + index);
	return lowestNode;
}

void PathFinder::addSuccessor(int x, int y, float cost)
{
	std::shared_ptr<PlannerNode> successor(new PlannerNode(x, y));
	successor->givenCost = currentNode->givenCost + cost;
	float distance = static_cast<float>(sqrt((x - goalPosition.x) * (x - goalPosition.x) + (y - goalPosition.y) * (y - goalPosition.y)));
	float hCost = distance;
	float hWeight = 1.0f;
	successor->finalCost = successor->givenCost + hCost * hWeight;
	successor->parent = currentNode;
	std::shared_ptr<PlannerNode> removalNode = nullptr;
	int index = 0;
	for (std::shared_ptr<PlannerNode> pn : openList)
	{
		if (pn->cellX == x && pn->cellY == y)
		{
			if (pn->finalCost <= successor->finalCost) 
				return;
			removalNode = pn;
			break;
		}
		index++;
	}
	if (removalNode != nullptr)
		openList.erase(openList.begin() + index);
	openList.push_back(successor);

}
