
#include <glbinding/gl/gl.h>
#include "tree.h"

Tree::Tree(std::shared_ptr<Model> treeModel, float x, float y, float z) 
	: treeModel(treeModel), x(x), y(y), z(z)
{
}

void Tree::draw(GLState &glState, Camera *camera)
{
	glState.loadIdentity();
	glState.translate(x, y, z);
	glState.default3DShader->glUniformMatrix4("modelMatrix", gl::GL_FALSE, glState.model);
	treeModel->draw(camera);
}






