
#include <iostream>
#include "grid.h"


Grid::Grid(float x, float y, float width, float height, int cellCountWidth, int cellCountHeight)
	: cellWidth(width / cellCountWidth), cellHeight(cellHeight = height / cellCountHeight),
	x(x), y(y), width(width), height(height), cellCountHeight(cellCountHeight), cellCountWidth(cellCountWidth),
	memory(new bool[cellCountHeight * cellCountWidth])
{
	for (int i = 0; i < cellCountWidth; i++)
	{
		for (int j = 0; j < cellCountHeight; j++)
		{
			setExactCell(i, j, false);
		}
	}
}

glm::vec2 Grid::convertWorldToGrid(glm::vec2 worldPos)
{
	return glm::vec2(static_cast<int>((worldPos.x - this->x) / cellWidth), static_cast<int>((worldPos.y - this->y) / cellHeight));
}
 
glm::vec2 Grid::revertToWorldFromGrid(glm::vec2 gridPos)
{
	return glm::vec2((cellWidth * gridPos.x) + this->x, (cellHeight * gridPos.y) + this->y);
}

bool Grid::mark(float x, float y, float w, float h, bool val)
{
	bool fullySuccessful = true;
	int xStart = (x - this->x) / cellWidth;
	int yStart = (y - this->y) / cellHeight;
	int xEnd = ((x + w) - this->x) / cellWidth;
	int yEnd = ((y + h) - this->y) / cellHeight;

	if (xStart < 0)
	{
		fullySuccessful = false;
		xStart = 0;
	}
	if (yStart < 0)
	{
		fullySuccessful = false;
		yStart = 0;
	}
	if (xStart >= cellCountWidth)
	{
		fullySuccessful = false;
		xStart = cellCountWidth - 1;
	}
	if (yStart >= cellCountHeight)
	{
		yStart = cellCountHeight - 1;
		fullySuccessful = false;
	}
	if (xEnd < 0)
	{
		xEnd = 0;
		fullySuccessful = false;
	}
	if (yEnd < 0)
	{
		yEnd = 0;
		fullySuccessful = false;
	}
	if (xEnd >= cellCountWidth)
	{
		xEnd = cellCountWidth - 1;
		fullySuccessful = false;
	}
	if (yEnd >= cellCountHeight)
	{
		yEnd = cellCountHeight - 1;
		fullySuccessful = false;
	}

	for (int i = xStart; i <= xEnd; i++)
	{
		for (int j = yStart; j <= yEnd; j++)
		{
			setExactCell(i, j, val);
		}
	}
	return fullySuccessful;
}

bool Grid::at(float x, float y)
{
	int xPos = (x - this->x) / cellWidth;
	int yPos = (y - this->y) / cellHeight;
	if (xPos < 0 || yPos < 0 || xPos >= cellCountWidth || yPos >= cellCountHeight)
		return false;
	return memory[yPos * cellCountWidth + xPos];
}

bool Grid::atExactCell(int x, int y)
{
	if (x < 0 || y < 0 || x >= cellCountWidth || y >= cellCountHeight)
		return false;
	return memory[y * cellCountWidth + x];
}

bool Grid::setExactCell(int _x, int _y, bool val)
{
	if (_x < 0 || _y < 0 || _x >= cellCountWidth || _y >= cellCountHeight)
		return false;
	memory[_y * cellCountWidth + _x] = val;
	return true;
}

bool Grid::set(float x, float y, bool val)
{
	int xPos = (x - this->x) / cellWidth;
	int yPos = (y - this->y) / cellHeight;
	if (xPos < 0 || yPos < 0 || xPos >= cellCountWidth || yPos >= cellCountHeight)
		return false;
	memory[yPos * cellCountWidth + xPos] = val;
	return true;
}

void Grid::print()
{
	for (int i = 0; i < cellCountHeight; i++)
	{
		std::cout << '|';
		for (int j = 0; j < cellCountWidth; j++)
		{
			bool val = atExactCell(j, i);
			if (val)
			{
				std::cout << 'X';
			}
			else
			{
				std::cout << ' ';
			}
		}
		std::cout << '|' << std::endl;
	}
}