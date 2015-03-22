#ifndef ENGINE_TREE_H
#define ENGINE_TREE_H

#include <string>
#include <memory>
#include "graphics/model.h"

class Tree
{
public:
	std::shared_ptr<Model> treeModel;
	float x;
	float y;
	float z;
	Tree(std::shared_ptr<Model> treeModel, float x, float y, float z);
	void draw(Camera *camera);
};

#endif
