
#include <glbinding/gl/gl.h>
#include "tree.h"

Tree::Tree(std::shared_ptr<Model> treeModel, float x, float y, float z) 
	: treeModel(treeModel), x(x), y(y), z(z)
{
}

void Tree::draw(Camera *camera)
{
	using namespace gl;

	glTranslatef(x, y, z);
	treeModel->draw(camera);
	glPopMatrix();
}






