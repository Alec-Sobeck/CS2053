#pragma once

#include <string>
#include <memory>
#include "graphics/model.h"
#include "graphics/glstate.h"

class Tree
{
public:
	std::shared_ptr<Model> treeModel;
	float x;
	float y;
	float z;
	Tree(std::shared_ptr<Model> treeModel, float x, float y, float z);
	void draw(GLState &glState, Camera *camera);
};

