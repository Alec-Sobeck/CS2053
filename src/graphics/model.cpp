
#include <cmath>
#include <stdexcept>
#include "model.h"
#include "math/gamemath.h"

int getNextModelID()
{
    static int modelID = 0;
    return modelID++;
}

AABB Model::getAABB()
{
	return aabb;
}

AABB Model::generateAABB()
{
	if (data.size() == 0)
	{
		return AABB(0, 0, 0, 0, 0, 0);
	}
	float minX =  10000000;
	float minY =  10000000;
	float minZ =  10000000;
	float maxX = -10000000;
	float maxY = -10000000;
	float maxZ = -10000000;

	for (auto mesh : data)
	{
		auto cs = mesh->numVerts;
		for (int i = 0; i < cs; i++)
		{
			// X
			if (mesh->vertices[i * 3 + 0] > maxX)
			{
				maxX = mesh->vertices[i * 3 + 0];
			}
			if (mesh->vertices[i * 3 + 0] < minX)
			{
				minX = mesh->vertices[i * 3 + 0];
			}
			// Y
			if (mesh->vertices[i * 3 + 1] > maxY)
			{
				maxY = mesh->vertices[i * 3 + 1];
			}
			if (mesh->vertices[i * 3 + 1] < minY)
			{
				minY = mesh->vertices[i * 3 + 1];
			}
			// Z
			if (mesh->vertices[i * 3 + 2] > maxZ)
			{
				maxZ = mesh->vertices[i * 3 + 2];
			}
			if (mesh->vertices[i * 3 + 2] < minZ)
			{
				minZ = mesh->vertices[i * 3 + 2];
			}
		}
	}
	this->aabb = AABB(minX, minY, minZ, maxX, maxY, maxZ);
	return this->aabb;
}

Model::Model(std::vector<std::shared_ptr<VAOMeshData>> data) : modelID(getNextModelID()), origin(glm::vec3(0, 0, 0)), rotationOnAxes(glm::vec3(0, 0, 0)),
        data(data), aabb(generateAABB()), scale(glm::vec3(1.0f, 1.0f, 1.0f))
{
}

Model::~Model()
{
}

bool Model::intersections(AABB &other)
{
	return intersects(aabb, other);
}

glm::vec3 Model::getOrigin()
{
    return origin;
}

void Model::setOrigin(glm::vec3 origin)
{
    this->origin = origin;
}

void Model::scaleModel(glm::vec3 scale)
{
    this->scale = scale;
}

void Model::scaleModel(float amount, bool scaleX, bool scaleY, bool scaleZ)
{
    if (scaleX)
        scale = glm::vec3(scale.x * amount, scale.y, scale.z);
    if (scaleY)
        scale = glm::vec3(scale.x, scale.y * amount, scale.z);
    if (scaleZ)
        scale = glm::vec3(scale.x, scale.y, scale.z * amount);
}

void Model::translate(glm::vec3 amount)
{
    origin = origin + amount;
}

glm::vec3 Model::getRotationOnAxes()
{
    return rotationOnAxes;
}

void Model::rotate(glm::vec3 rotation)
{
    setRotationOnAxes(glm::vec3(rotation.x + rotationOnAxes.x,
                                rotation.y + rotationOnAxes.y,
                                rotation.z + rotationOnAxes.z));
}

void Model::reduceRotation()
{
    setRotationOnAxes(glm::vec3(fmod(rotationOnAxes.x, (2 * PI)),
                                fmod(rotationOnAxes.y, (2 * PI)),
                                fmod(rotationOnAxes.z, (2 * PI))));
}

void Model::setRotationOnAxes(glm::vec3 rotationOnAxes)
{
    this->rotationOnAxes = rotationOnAxes;
}

int Model::getID()
{
    return modelID;
}

void Model::createVBOs(std::shared_ptr<Shader> associatedShader, std::map<std::string, std::shared_ptr<Texture>> textureMap)
{
	this->associatedShader = associatedShader;
	for(unsigned int i = 0; i < data.size(); i++)
    {
		auto d = data[i];
		std::cout << "Texture: " << data[i]->associatedTextureName << std::endl;
		if (overrideTexture)
        {
			auto vao = std::shared_ptr<TexturedNormalColouredVAO>(new TexturedNormalColouredVAO(
				associatedShader->programID, d->numVerts, d->vertices, d->verticesSize, d->normals, d->normalsSize,
				d->colours, d->coloursSize, d->textures, d->texturesSize
			));
			vao->tex = overrideTexture;
			vaos.push_back(vao);
		}
        else
		{
			auto vao = std::shared_ptr<TexturedNormalColouredVAO>(new TexturedNormalColouredVAO(
				associatedShader->programID, 
				d->numVerts, 
				d->vertices, 
				d->verticesSize, 
				d->normals, 
				d->normalsSize,
				d->colours, 
				d->coloursSize,
				d->textures, 
				d->texturesSize
			));
			vao->tex = textureMap[data[i]->associatedTextureName];
			vaos.push_back(vao);
        }
    }
}

void Model::draw(Camera *camera)
{
    for(unsigned int i = 0; i < vaos.size(); i++)
    {
        vaos[i]->draw();
    }
}



