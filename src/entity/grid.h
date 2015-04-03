#ifndef ENGINE_GRID_H
#define ENGINE_GRID_H

#include <glm/vec2.hpp>

class Grid
{
public:
	float x;
	float y;
	float width;
	float height;
	int cellCountWidth;
	int cellCountHeight;
	float cellWidth;
	float cellHeight;
	bool *memory;

	Grid(float x, float y, float width, float height, int cellCountWidth, int cellCountHeight);	
	bool mark(float x, float y, float w, float h, bool val);
	bool at(float x, float y);
	bool set(float x, float y, bool val);
	bool setExactCell(int x, int y, bool val);
	bool atExactCell(int x, int y);
	void print();
	glm::vec2 revertToWorldFromGrid(glm::vec2 gridPos);
	glm::vec2 convertWorldToGrid(glm::vec2 worldPos);
};


#endif