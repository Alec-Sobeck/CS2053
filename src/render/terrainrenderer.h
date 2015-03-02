#ifndef TERRAIN_RENDERER_H
#define TERRAIN_RENDERER_H

#include <memory>
#include <glm/vec3.hpp>
#include "graphics/camera.h"
#include "graphics/terrainpolygon.h"
#include "terrain/terraindata.h"
#include "render/dynamicvbo.h"
#include "utils/flexarray.h"
#include "render/texture.h"

class TerrainRenderer
{
public:
    FlexArray<TerrainPolygon> terrainPolygons;
    DynamicVBO* vbo;
    TerrainRenderer();
    void create(std::shared_ptr<TerrainData> terrain, std::shared_ptr<Texture> terrainTexture);
	void draw(Camera *cam);
    ~TerrainRenderer();

/*
	public static void doStuffAdd1()
	{
		if(p.getIBOIndexes() == null)
		{
			vbo.add(p);
			vbo.add(p1);
		}
		else
		{
			System.out.println("DerpA1");
		}
	}

	public static void doStuffRemove1()
	{
		if(p.getIBOIndexes() != null)
		{
			vbo.remove(p.getIBOIndexes());
			p.setIBOIndexes(null);
			vbo.remove(p1.getIBOIndexes());
			p1.setIBOIndexes(null);
		}
		else
		{
			System.out.println("DerpR1");
		}
	}

	public static void doStuffAdd2()
	{
		if(p2.getIBOIndexes() == null)
		{
			vbo.add(p2);
			vbo.add(p3);
		}
		else
		{
			System.out.println("DerpA2");
		}
	}

	public static void doStuffRemove2()
	{
		if(p2.getIBOIndexes() != null)
		{
			vbo.remove(p2.getIBOIndexes());
			p2.setIBOIndexes(null);
			vbo.remove(p3.getIBOIndexes());
			p3.setIBOIndexes(null);
		}
		else
		{
			System.out.println("DerpR2");
		}
	}
*/
};






#endif
