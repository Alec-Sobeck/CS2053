
#include <cmath>
#include <list>
#include <memory>
#include <stdlib.h>
#include <iostream>
#include <soil/SOIL.h>
#include <glbinding/gl/gl.h>
#include <fmod/fmod_studio.hpp>
#include <fmod/fmod.hpp>
#include <fmod/fmod_errors.h>
#include "gameloop.h"
#include "utils/textureloader.h"
#include "entity/entity.h"
#include "terrain/terraindata.h"
#include "render/terrainrenderer.h"
#include "world/map.h"
#include "graphics/rendersettingshelper.h"
#include "utils/timehelper.h"
#include "terrain/midpointterrain.h"
#include "terrain/flatterrain.h"
#include "graphics/gluhelper.h"
#include "render/render.h"
#include "terrain/grass.h"
#include "graphics/gluhelper.h"
#include "utils/objparser.h"
#include "render/glfont.h"
#include "render/ui.h"
#include "entity/projectile.h"
#include "render/sphere.h"
#include "graphics/tree.h"
#include "math/gamemath.h"
#include "utils/fileutils.h"
#include "utils/random.h"
#include "entity/enemy.h"
#include "entity/player.h"

///***********************************************************************
///***********************************************************************
/// Start internal API declaration
///***********************************************************************
///***********************************************************************
///
/// Initialization functions
///
void initializeEngine();
///
/// Input functions
///
void processKeyboardInput();
void processMouseInput();
///
/// Game update/rendering functions
///
void gameUpdateTick();

///
/// Define the KeyManager class. Because GLUT is a C library, unfortunately we have to write this is a fairly C-like style.
///
/// Special Usage Note: KeyManager class has some problems with the isShiftDown, isControlDown, and isAltDown fields not updating. The state of these keys cannot be queried until another
/// key event happens [this is an OS restriction - there might be a workaround?]. Their state only updates when another key is pressed or released.
///
void keyManagerKeyPressed(unsigned char key, int x, int y);
void keyManagerKeyUp (unsigned char key, int x, int y);
void keyManagerKeySpecial(int key, int x, int y);
void keyManagerKeySpecialUp(int key, int x, int y);
void updateModifierState();
///
/// Define the MouseManager class. Similarly to KeyManager this is in a fairly C-like style because GLUT is a C library.
///

void mouseManagerHandleMouseClick(int button, int state, int x, int y);
void mouseManagerHandleMouseMovementWhileClicked(int x,int y);
void mouseManagerHandleMouseMovementWhileNotClicked(int x, int y);
///
/// Define the GameLoop class.
///

class GameLoop
{
public:
    const int GAME_TICKS_PER_SECOND = 60;
    bool gameIsRunning;
    Player player;
    std::shared_ptr<TerrainData> terrain;
    Map map;
    long startTime;
    std::shared_ptr<TerrainRenderer> terrainRenderer;
    KeyManager keyManager;
    MouseManager mouseManager;
    Grass *grass; 
    std::shared_ptr<Model> treeModel;
	std::shared_ptr<Model> gunModel;
	std::shared_ptr<Model> zombieModel;
	std::shared_ptr<GLFont> fontRenderer;
	unsigned long long previousFrameTime;
	float deltaTime;
	std::shared_ptr<Texture> ammoTexture;
	std::shared_ptr<Texture> medkitTexture;
	std::shared_ptr<Texture> gunTexture;
	std::vector<std::shared_ptr<Projectile>> projectiles;
	FMOD::Studio::System* system = NULL;
	FMOD::Sound *music;
	FMOD::Channel* musicChannel;
	FMOD::Studio::EventInstance* eventInstance;
	FMOD::Studio::EventInstance* bgmInstance;
	FMOD::Studio::EventInstance* hurtInstance;
	std::list<Tree> trees;
	bool hasStartedBGM = false;
	std::vector<std::shared_ptr<Enemy>> enemies;
	std::shared_ptr<Texture> skyboxTexture;
	AABB worldBounds;

    GameLoop();
	~GameLoop();
    void buildSampleTerrain();
	void update();
	void collisionCheck();
	float getDeltaTime();
	///
    /// Draws a basic text string.
    /// \param val - the string of text to draw
    /// \param x - the x coordinate of the text
    /// \param y - the y coordinate of the text
    /// \param z - the z coordinate of the text. Leave 0 when rendering in 2D.
    /// \param colour - the colour the text will be rendered.
    ///
    bool drawString(std::string val, float x, float y, float z, Colour colour);
};

///***********************************************************************
///***********************************************************************
/// End internal API declaration
///***********************************************************************
///***********************************************************************

///***********************************************************************
///***********************************************************************
/// GameLoop "global" object for shared state between these functions.
///***********************************************************************
///***********************************************************************
GameLoop gameLoopObject;

///***********************************************************************
///***********************************************************************
/// Define initialization functions
///***********************************************************************
///***********************************************************************

///
/// this is an error handling function for FMOD errors
/// 
void ERRCHECK(FMOD_RESULT result)        
{
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s", result, FMOD_ErrorString(result));
		exit(-1);
	}
}

void initializeEngine()
{
    using namespace gl;    
    initializeViewport();
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    //Create font
	GLuint textureName;
	gl::glGenTextures(1, &textureName);
	gameLoopObject.fontRenderer = std::shared_ptr<GLFont>(new GLFont());
	try
	{
		gameLoopObject.fontRenderer->Create(getTexture(buildPath("res/font.png")));
		gameLoopObject.ammoTexture = getTexture(buildPath("res/ammo_icon.png"));
		gameLoopObject.medkitTexture = getTexture(buildPath("res/medkit.png"));
	}
	catch(GLFontError::InvalidFile)
	{
		std::cout << "Cannot load font" << std::endl;
		exit(1);
	}    

	// Init the sound engine (FMOD)
	FMOD::Studio::System* system = NULL;
	ERRCHECK(FMOD::Studio::System::create(&system));
	gameLoopObject.system = system;

	// The example Studio project is authored for 5.1 sound, so set up the system output mode to match
	FMOD::System* lowLevelSystem = NULL;
	ERRCHECK(system->getLowLevelSystem(&lowLevelSystem));
	ERRCHECK(lowLevelSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0));
	ERRCHECK(system->initialize(32, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, NULL));

	FMOD::Studio::Bank* masterBank = NULL;
	ERRCHECK(system->loadBankFile(buildPath("res/audio/Master Bank.bank").c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank));
	FMOD::Studio::Bank* stringsBank = NULL;
	ERRCHECK(system->loadBankFile(buildPath("res/audio/Master Bank.strings.bank").c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank));
	masterBank->loadSampleData();
	stringsBank->loadSampleData();

	bool done = false;
	while (!done)
	{		
		FMOD_STUDIO_LOADING_STATE val1;
		FMOD_STUDIO_LOADING_STATE val2;
		masterBank->getLoadingState(&val1);
		stringsBank->getLoadingState(&val2);
		if (val1 == FMOD_STUDIO_LOADING_STATE_LOADED && val2 == FMOD_STUDIO_LOADING_STATE_LOADED)
		{
			done = true;
		}
	}


	FMOD::Studio::EventDescription* eventDescription = NULL;
	ERRCHECK(system->getEvent("event:/pistol-01", &eventDescription));
	gameLoopObject.eventInstance = NULL;
	ERRCHECK(eventDescription->createInstance(&gameLoopObject.eventInstance));	
	
	FMOD::Studio::EventDescription* bgmDescription = NULL;
	ERRCHECK(system->getEvent("event:/bgm-battle-01", &bgmDescription));
	gameLoopObject.bgmInstance = NULL;
	ERRCHECK(bgmDescription->createInstance(&gameLoopObject.bgmInstance));

	FMOD::Studio::EventDescription* hurtDescription = NULL;
	ERRCHECK(system->getEvent("event:/hurt1", &hurtDescription));
	gameLoopObject.hurtInstance = NULL;
	ERRCHECK(hurtDescription->createInstance(&gameLoopObject.hurtInstance));

	// Position the listener at the origin
	FMOD_3D_ATTRIBUTES attributes = { { 0 } };
	attributes.forward.z = 1.0f;
	attributes.up.y = 1.0f;
	ERRCHECK(system->setListenerAttributes(&attributes));

	// Position the event 2 units in front of the listener
	attributes.position.z = 2.0f;
	ERRCHECK(gameLoopObject.eventInstance->set3DAttributes(&attributes));

	// Build the terrain
	gameLoopObject.buildSampleTerrain();
}

///***********************************************************************
///***********************************************************************
/// Define the GameLoop class methods.
///***********************************************************************
///***********************************************************************
GameLoop::GameLoop() : gameIsRunning(true), player(Player(Camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)))), map(Map(AABB(-200, -10, -200, 200, 10, 200))), startTime(getCurrentTimeMillis()),
terrainRenderer(std::shared_ptr<TerrainRenderer>(nullptr)), grass(nullptr), previousFrameTime(getCurrentTimeMillis()), worldBounds(AABB(0, 0, 0, 0, 0, 0))
{
	// Important usage note: a GL Context is not bound when this constructor is called. Using any gl functions with cause a segfault or crash.
	player.setCamera(Camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)));
	player.boundingBox = AABB(0.0f, 0.0f, 0.0f, 1.0f, 2.0f, 1.0f);
}

GameLoop::~GameLoop()
{
	if (system)
	{
		ERRCHECK(system->release());
	}
	if (grass)
	{
		delete grass;
	}
}

void GameLoop::buildSampleTerrain()
{
    glm::vec3 v(getWindowWidth(), getWindowHeight(), 1.0);
    std::shared_ptr<Terrain> terrain(new FlatTerrain(200));
	worldBounds = AABB(-100, 0, -100, 60, 50, 60);

	gameLoopObject.skyboxTexture = getTexture(buildPath("res/skybox_texture.jpg"));


	auto tex = getTexture(buildPath("res/terrain.png"));
	auto grassTexture = getTexture(buildPath("res/grass_1.png"));
	auto terrainExp = terrain->exportToTerrainData();
    this->terrainRenderer = std::shared_ptr<TerrainRenderer>(new TerrainRenderer());
    this->terrainRenderer->create(terrainExp, tex);
	this->grass = new Grass(getRandomInt(1000) + 300, glm::vec3(0, 0, 0), glm::vec3(2.0f, 0, 2.0f), 50, grassTexture);
	
	// Load the tree model
	ObjParser parser(
		buildPath("res/models/pine_tree1/"), buildPath("res/models/pine_tree1/Tree.obj"),
		"Branches0018_1_S.png", false );
	gameLoopObject.treeModel = parser.exportModel();
	auto treeTexture = getTexture(buildPath("res/models/pine_tree1/BarkDecidious0107_M.jpg"));
	auto branchTexture = getTexture(buildPath("res/models/pine_tree1/Branches0018_1_S.png"));
	std::map<std::string, std::shared_ptr<Texture>> textures;
    textures["tree"] = treeTexture;
    textures["leaves"] = branchTexture;
    gameLoopObject.treeModel->createVBOs(textures);

	// Load the gun model
	parser = ObjParser(
		buildPath("res/models/gun/"), buildPath("res/models/gun/M9.obj"),
		"", true);
	gameLoopObject.gunModel = parser.exportModel();
	auto Handgun_D = getTexture(buildPath("res/models/gun/Tex_0009_1.jpg"));
	gameLoopObject.gunTexture = Handgun_D;
	textures = std::map<std::string, std::shared_ptr<Texture>>();
	textures["Tex_0009_1"] = Handgun_D;
	gameLoopObject.gunModel->createVBOs(textures);
	for (std::shared_ptr<VBO> vbo : gameLoopObject.gunModel->vbos)
	{
		vbo->associatedTexture = Handgun_D;
	}
	gameLoopObject.gunModel->generateAABB();

	for (int i = 0; i < 10; i++)
	{
		int x = getRandomInt(100) - 50;
		int y = 0;
		int z = getRandomInt(100) - 50;

		int retryCounter = 0;
		while (retryCounter < 10)
		{
			bool success = true;
			for (Tree &tree : gameLoopObject.trees)
			{
				float distanceSquared = square(tree.x - x) + square(tree.y - y);
				if (distanceSquared < 25)
				{
					success = false;
					break;
				}
			}
			retryCounter++;
			if (success)
			{
				gameLoopObject.trees.push_back(Tree(treeModel, x, y, z));
				retryCounter += 1000;
			}
		}		
	}

	// Load the zombie
	parser = ObjParser(buildPath("res/models/zombie/"), buildPath("res/models/zombie/Lambent_Male.obj"), "", true);
	gameLoopObject.zombieModel = parser.exportModel();
	auto _D = getTexture(buildPath("res/models/zombie/Lambent_Male_D.png"));
	auto _E = getTexture(buildPath("res/models/zombie/Lambent_Male_E.tga"));
	auto _N = getTexture(buildPath("res/models/zombie/Lambent_Male_N.tga"));
	auto _S = getTexture(buildPath("res/models/zombie/Lambent_Male_S.tga"));
	textures = std::map<std::string, std::shared_ptr<Texture>>();
	textures["Lambent_Male_D.tga"] = _D;
	textures["Lambent_Male_E.tga"] = _E;
	textures["Lambent_Male_N.tga"] = _N;
	textures["Lambent_Male_S.tga"] = _S;
	gameLoopObject.zombieModel->createVBOs(textures);
	for (std::shared_ptr<VBO> vbo : gameLoopObject.zombieModel->vbos)
	{
		vbo->associatedTexture = _D;
	}
	gameLoopObject.zombieModel->generateAABB(); 


}

bool GameLoop::drawString(std::string val, float x, float y, float z, Colour colour)
{
    using namespace gl;
    try
    {
        glEnable(GL_TEXTURE_2D);
        gl::glColor4f(colour.r, colour.g, colour.b, colour.a);
        glDisable(GL_BLEND);
        glAlphaFunc(GL_GREATER, 0.1f);
        glEnable(GL_ALPHA_TEST);
		std::stringstream ss;
		ss << "score:" << player.score;
        fontRenderer->TextOut(ss.str(), 20, 20, 0);
        return true;
    }
    catch(GLFontError::InvalidFont)
    {
        return false;
    }
    return false;
}

float GameLoop::getDeltaTime()
{
	return deltaTime;
}

void GameLoop::update()
{
	unsigned long long currentTime = getCurrentTimeMillis();
	unsigned long long deltaTimeMillis = currentTime - previousFrameTime;
	this->deltaTime = static_cast<float>(deltaTimeMillis) / 1000.0f;
	previousFrameTime = currentTime;
	if (!hasStartedBGM)
	{
		hasStartedBGM = true;
		ERRCHECK(gameLoopObject.bgmInstance->start());
	}
	else
	{
		FMOD_STUDIO_PLAYBACK_STATE bgmState;
		gameLoopObject.bgmInstance->getPlaybackState(&bgmState);
		if (bgmState == FMOD_STUDIO_PLAYBACK_STOPPED)
		{
			ERRCHECK(gameLoopObject.bgmInstance->start());
		}
	}

	// Check collisions
	collisionCheck();
}

void GameLoop::collisionCheck()
{
	// Player - monster collision
	for (int i = 0; i < enemies.size(); i++)
	{
		std::shared_ptr<Enemy> enemy = enemies[i];
		if (enemy->getAABB().overlaps(player.getAABB()))
		{
			if (!player.isInvincible())
			{
				player.hurtPlayer(20);
				gameLoopObject.hurtInstance->start();
			}
		}
	}	

	// Player's bullet vs enemy collision test. 
	for (int j = 0; j < projectiles.size(); j++)
	{
		std::vector<std::shared_ptr<Enemy>> hits;
		for (int i = 0; i < enemies.size(); i++)
		{
			// Capsule variables
			LineSegment3 seg = projectiles[j]->getMovement();
			float radius = projectiles[j]->size;
			Capsule3D capsule(seg.point1, seg.point2, radius);
			// Check for overlap with a lazy overlap test that misses some [in this case trivial] cases.	
			if (enemies[i]->boundingBox.cheapOverlaps(capsule))
			{
				hits.push_back(enemies[i]);
			}
		}
		if (hits.size() == 1)
		{
			hits[0]->hurt(20);
			projectiles.erase(projectiles.begin() + j);
			j--;
			continue;
		}
		else if (hits.size() > 1&&false)
		{
			int closest = 0;
			float closestLength = 10000;
			glm::vec3 head = player.boundingBox.center();
			for (int i = 0; i < hits.size(); i++)
			{
				glm::vec3 tail = enemies[i]->boundingBox.center();
				glm::vec3 result = head - tail;
				float length = glm::length(result);
				if (length < closestLength)
				{
					closest = i;
				}
			}
			hits[closest]->hurt(20);

			projectiles.erase(projectiles.begin() + j);
			j--;
			continue;
		}
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->isDead())
		{
			player.score += 1;
			player.ammoCount += 5;
			enemies.erase(enemies.begin() + i);
			i--;
			continue;
		}
	}

}

///***********************************************************************
///***********************************************************************
/// Define Gameloop/render functions.
///***********************************************************************
///***********************************************************************

void gameUpdateTick()
{
    using namespace gl;
	gameLoopObject.system->update();
	float deltaTime = gameLoopObject.getDeltaTime();

	gameLoopObject.update();
    processKeyboardInput();
    processMouseInput();

    //Draw here
    startRenderCycle();
    gl::glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    Camera *cam = gameLoopObject.player.getCamera();
    startRenderCycle();
    start3DRenderCycle();
	
	AABB box = gameLoopObject.treeModel->getAABB();
	renderAxes(cam);
	drawSkybox(gameLoopObject.skyboxTexture, cam);
	gameLoopObject.player.update(gameLoopObject.worldBounds, deltaTime);
    gameLoopObject.terrainRenderer->draw(cam);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glDisable(GL_TEXTURE_2D);
	for (int i = 0; i < gameLoopObject.projectiles.size(); )
	{
		std::shared_ptr<Projectile> p = gameLoopObject.projectiles.at(i);
		p->onGameTick(deltaTime);
			
		if (p->getY() < -p->size)
		{
			gameLoopObject.projectiles.erase(gameLoopObject.projectiles.begin() + i);
		}
		else
		{
			p->draw();
			i++;
		}
	}
	glEnable(GL_TEXTURE_2D);

	/// DRAW -- tree
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glDisable(GL_BLEND);
    glAlphaFunc(GL_GREATER, 0.1f);
    glEnable(GL_ALPHA_TEST);
	gl::glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    setLookAt(cam);
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    for(Tree &tree : gameLoopObject.trees)
    {
        tree.draw(cam);
    }
	glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	/// END DRAW -- tree
	// draw enemies
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glDisable(GL_BLEND);
	glAlphaFunc(GL_GREATER, 0.1f);
	glEnable(GL_ALPHA_TEST);
	gl::glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	setLookAt(cam);
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	for (std::shared_ptr<Enemy> enemy: gameLoopObject.enemies)
	{
		enemy->onGameTick(gameLoopObject.player, deltaTime, gameLoopObject.worldBounds);
		enemy->draw(cam);
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	// End draw enemies

	gameLoopObject.grass->update(cam);
    gameLoopObject.grass->draw(cam);
    
	// Draw the player's gun
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glDisable(GL_BLEND);
	glAlphaFunc(GL_GREATER, 0.1f);
	glEnable(GL_ALPHA_TEST);
	//glDisable(GL_CULL_FACE);
	
	glMatrixMode(GL_MODELVIEW);
	gl::glPushMatrix();
	gl::glLoadIdentity();
	// Translate to model co-ordinates, based on the origin of the shape
	
	setLookAt(cam);
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glm::vec3 lookAt = glm::normalize(glm::vec3(
		+ sin(cam->rotation.y),
		- sin(cam->rotation.x),
		- cos(cam->rotation.y)
	));
	glm::vec3 offset = lookAt;
	gl::glTranslatef(cam->position.x + offset.x, cam->position.y + offset.y - 0.2f, cam->position.z + offset.z);
	glm::vec3 forward(
		cam->position.x + sin(cam->rotation.y),
		cam->position.y - sin(cam->rotation.x),
		cam->position.z - cos(cam->rotation.y)
		);
	glm::vec3 up(0, cos(cam->rotation.x), 0);
	glm::vec3 left = glm::cross(up, forward);
	//glRotatef(toDeg(cam->rotation.x + cam->rotation.z), left.x, left.y, left.z);
	gl::glRotatef(toDeg(-cam->rotation.y), 0, 1, 0);
	glEnable(GL_TEXTURE_2D);
	gameLoopObject.gunModel->draw(cam);
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	gl::glPopMatrix();


	// End gun draw
	end3DRenderCycle();

    start2DRenderCycle();
    gameLoopObject.drawString("hello world", 50, 50, 0, RED);
	drawUI(gameLoopObject.player, gameLoopObject.mouseManager, gameLoopObject.fontRenderer, gameLoopObject.ammoTexture, gameLoopObject.medkitTexture);
    end2DRenderCycle();
    endRenderCycle();

}

///***********************************************************************
///***********************************************************************
/// Define Core Input Functions
///***********************************************************************
///***********************************************************************
#include <GL/freeglut.h>
#include "graphics/windowhelper.h"
void processKeyboardInput()
{
	float deltaTime = gameLoopObject.getDeltaTime();
    // to check for a key modifier use:
    //       int glutGetModifiers(void);
    // The return value for this function is either one of three predefined constants or any bitwise OR combination of them. The constants are:
    //       GLUT_ACTIVE_SHIFT - Set if either you press the SHIFT key, or Caps Lock is on. Note that if they are both on then the constant is not set.
    //       GLUT_ACTIVE_CTRL - Set if you press the CTRL key.
    //       GLUT_ACTIVE_ALT - Set if you press the ALT key.
    Camera *camera = gameLoopObject.player.getCamera();
    KeyManager *manager = &gameLoopObject.keyManager;
    manager->update();

    if (manager->getKeyState(27) == KeyManager::PRESSED) // Escape key
	{
		exit(0);
	}

    if(manager->getKeyState('w') == KeyManager::PRESSED)
    {
		gameLoopObject.player.accel(
			glm::vec3(
				sin(gameLoopObject.player.getCamera()->rotation.y),
				0,
				-cos(gameLoopObject.player.getCamera()->rotation.y)
			) * deltaTime * 5.0f
		);
    }
    if(manager->getKeyState('s') == KeyManager::PRESSED)
    {
        gameLoopObject.player.accel(
			glm::vec3(
				-sin(gameLoopObject.player.getCamera()->rotation.y),
                0,
                cos(gameLoopObject.player.getCamera()->rotation.y)
			) * deltaTime * 5.0f
		);
    }
    if(manager->getKeyState('a') == KeyManager::PRESSED)
    {
        gameLoopObject.player.accel(
			glm::vec3(-cos(gameLoopObject.player.getCamera()->rotation.y),
                0,
                -sin(gameLoopObject.player.getCamera()->rotation.y)
			) * deltaTime * 5.0f
		);
    }
    if(manager->getKeyState('d') == KeyManager::PRESSED)
    {
        gameLoopObject.player.accel(
			glm::vec3(cos(gameLoopObject.player.getCamera()->rotation.y),
                0,
                sin(gameLoopObject.player.getCamera()->rotation.y)
			) * deltaTime * 5.0f
		);
    }

    if(manager->isKeyDown('1'))
    {
        camera->rotate(glm::vec3(0.01f, 0, 0));
    }
    if(manager->isKeyDown('2'))
    {
        camera->rotate(glm::vec3(-.01f, 0, 0));
    }
    if(manager->isKeyDown('3'))
    {
        camera->rotate(glm::vec3(0, 0.01f, 0));
    }
    if(manager->isKeyDown('4'))
    {
        camera->rotate(glm::vec3(0, -.01f, 0));
    }
    if(manager->isKeyDown('5'))
    {
        camera->rotate(glm::vec3(0, 0, 0.01f));
    }
    if(manager->isKeyDown('6'))
    {
        camera->rotate(glm::vec3(0, 0, -.01f));
    }
	
	static bool enemyLock = false;
	if (manager->isKeyDown('m') && !enemyLock)
	{
		enemyLock = true;
		std::shared_ptr<Enemy> enemy(new Enemy(gameLoopObject.zombieModel, Camera(glm::vec3(static_cast<float>(getRandomInt(30) - 15), 0, static_cast<float>(getRandomInt(30) - 15)), glm::vec3(0, 0, 0))));
		enemy->boundingBox = AABB(0, 0, 0, 1, 1, 1);
		gameLoopObject.enemies.push_back(enemy);
	}
	if (!manager->isKeyDown('m'))
	{
		enemyLock = false;
	}

	// Use a healthkit if the player has less than their maximum health. 
	static bool healLock = false;
	if (manager->isKeyDown('h') && !healLock)
	{
		if (gameLoopObject.player.health < gameLoopObject.player.maxHealth && gameLoopObject.player.healingItemCount > 0)
		{
			gameLoopObject.player.health = gameLoopObject.player.maxHealth;
			gameLoopObject.player.healingItemCount -= 1;
		}
	}
	if (!manager->isKeyDown('h'))
	{
		healLock = false;
	}

    static bool keylockTab = false;
    if(manager->getKeyState('\t') == KeyManager::PRESSED && !keylockTab)
    {
        keylockTab = true;
        gameLoopObject.mouseManager.setGrabbed(!gameLoopObject.mouseManager.grabbed);
    }
    if(manager->getKeyState('\t') == KeyManager::RELEASED)
    {
        keylockTab = false;
    }

	/*
    if(manager->getKeyState(' ') == KeyManager::PRESSED)
    {
        gameLoopObject.player.accel(glm::vec3(0, 1, 0) * deltaTime);
    }
    if(manager->getKeyState('x') == KeyManager::PRESSED)
    {
		gameLoopObject.player.accel(glm::vec3(0, -1, 0) * deltaTime);
    }
	*/
}

void processMouseInput()
{
    MouseManager *manager = &gameLoopObject.mouseManager;
    Camera *cam = gameLoopObject.player.getCamera();
	float deltaTime = gameLoopObject.getDeltaTime();

    if(manager->grabbed)
    {
        glm::vec3 *grabDir = &manager->relativeGrabDirection;
        if (grabDir->x < -2)
        {
			cam->rotate(glm::vec3(0, -1.2, 0) * deltaTime);
        }
        else if (grabDir->x > 2)
        {
            cam->rotate(glm::vec3(0, 1.2, 0) * deltaTime);
        }
        if (grabDir->y < -2)
        {
			cam->rotate(glm::vec3(-1.2, 0, 0) * deltaTime);
        }
        else if (grabDir->y > 2)
        {
			cam->rotate(glm::vec3(1.2, 0, 0) * deltaTime);
        }
    }

	// FIRE!
	static bool leftClickLock = false;
	if (manager->leftMouseButtonState == MouseManager::MOUSE_PRESSED && !leftClickLock)
	{
		leftClickLock = true;
		if (gameLoopObject.player.ammoCount > 0)
		{
			// Figure out the bullet's offset based on the lookAt vector
			glm::vec3 lookAt = glm::normalize(glm::vec3(
				sin(cam->rotation.y * -1.0f),
				0,
				cos(cam->rotation.y * -1.0f)
				)) * -1.0f;
			AABB gunbox = gameLoopObject.gunModel->getAABB();
			float yDelta = gunbox.yMax - gunbox.yMin;
			lookAt = lookAt + lookAt * yDelta;
			// Note the bullet is still a little bit off
			//lookAt.x += 0.025f;
			//lookAt.y -= 0.1f; // 0.1f is a magic number. we'll eventually have to solve for this based on where the barrel in the gun model is.
			// Create the projectile.
			Camera camera((gameLoopObject.player.getPosition() + lookAt + glm::vec3(0.025f, -0.1f, 0.0f)), glm::vec3(0, 0, 0));
			std::shared_ptr<Projectile> projectile(new Projectile(camera, .029f));

			glm::vec3 acceleration = (lookAt)* 40.0f;
			acceleration.y -= 1.8f;
			projectile->accel(acceleration);
			gameLoopObject.projectiles.push_back(projectile);

			ERRCHECK(gameLoopObject.eventInstance->start());
			gameLoopObject.player.ammoCount -= 1;
		}
	}
	if (manager->leftMouseButtonState != MouseManager::MOUSE_PRESSED)
	{
		leftClickLock = false;
	}
}

void entryCall(int argc, char **argv)
{
    // init GLUT and create window
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,640);
	glutCreateWindow("BoatQuest IV");
	// register callbacks
	glutDisplayFunc(gameUpdateTick);
	glutReshapeFunc(changeSize);
	glutIdleFunc(gameUpdateTick);

	glutKeyboardFunc(keyManagerKeyPressed);
	glutKeyboardUpFunc(keyManagerKeyUp);
	glutSpecialFunc(keyManagerKeySpecial);
	glutSpecialUpFunc(keyManagerKeySpecialUp);
//	glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);
	//glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);
	//glutKeyboardFunc(processNormalKeys);
	//glutSpecialFunc(processSpecialKeys);
    glutMouseFunc(mouseManagerHandleMouseClick);
    glutMotionFunc(mouseManagerHandleMouseMovementWhileClicked);
    glutPassiveMotionFunc(mouseManagerHandleMouseMovementWhileNotClicked);
    // load opengl functions beyond version 1.1
    glbinding::Binding::initialize(true);
    // Initialize the engine.
    initializeEngine();
	// enter GLUT event processing loop
	glutMainLoop();
}

///
/// Define the KeyManager functions and methods.
///
KeyManager::KeyManager() : isShiftDown(false), isControlDown(false), isAltDown(false)
{
}

void KeyManager::update()
{
}

void KeyManager::updateModifierState()
{
    int mod = glutGetModifiers();
    isShiftDown = false;
    isControlDown = false;
    isAltDown = false;

    if(mod == GLUT_ACTIVE_SHIFT)
    {
        isShiftDown = true;
    }
    if(mod == GLUT_ACTIVE_CTRL)
    {
        isControlDown = true;
    }
    if(mod == GLUT_ACTIVE_ALT)
    {
        isAltDown = true;
    }
    if(mod == (GLUT_ACTIVE_ALT|GLUT_ACTIVE_CTRL))
    {
        isControlDown = true;
        isAltDown = true;
    }
    if(mod == (GLUT_ACTIVE_SHIFT|GLUT_ACTIVE_CTRL))
    {
        isShiftDown = true;
        isControlDown = true;
    }
    if(mod == (GLUT_ACTIVE_SHIFT|GLUT_ACTIVE_ALT))
    {
        isShiftDown = true;
        isAltDown = true;
    }
    if(mod == (GLUT_ACTIVE_SHIFT|GLUT_ACTIVE_CTRL|GLUT_ACTIVE_ALT))
    {
        isShiftDown = true;
        isControlDown = true;
        isAltDown = true;
    }
}

void keyManagerKeyPressed(unsigned char key, int x, int y)
{
    gameLoopObject.keyManager.updateModifierState();
    if(key >= KeyManager::VALID_NUMBER_OF_CHARS || key < 0)
    {
        return;
    }
    gameLoopObject.keyManager.keystates[key] = KeyManager::PRESSED;
}

void keyManagerKeyUp(unsigned char key, int x, int y)
{
    gameLoopObject.keyManager.updateModifierState();

    if(key >= KeyManager::VALID_NUMBER_OF_CHARS || key < 0)
    {
        return;
    }
    gameLoopObject.keyManager.keystates[key] = KeyManager::RELEASED;
}

void keyManagerKeySpecial(int key, int x, int y)
{
    gameLoopObject.keyManager.updateModifierState();

    if(key >= KeyManager::VALID_NUMBER_OF_SPECIALS || key < 0)
    {
        return;
    }
    gameLoopObject.keyManager.specialKeystates[key] = KeyManager::PRESSED;
}

void keyManagerKeySpecialUp(int key, int x, int y)
{
    gameLoopObject.keyManager.updateModifierState();
    if(key >= KeyManager::VALID_NUMBER_OF_SPECIALS || key < 0)
    {
        return;
    }
    gameLoopObject.keyManager.specialKeystates[key] = KeyManager::RELEASED;
}

unsigned char KeyManager::getKeyState(unsigned char key)
{
    if(key >= KeyManager::VALID_NUMBER_OF_CHARS || key < 0)
    {
        return RELEASED;
    }
    return gameLoopObject.keyManager.keystates[key];
}

unsigned char KeyManager::getSpecialState(int key)
{
    if(key >= KeyManager::VALID_NUMBER_OF_CHARS || key < 0)
    {
        return RELEASED;
    }
    return gameLoopObject.keyManager.specialKeystates[key];

}

unsigned char KeyManager::isKeyDown(unsigned char key)
{
    return getKeyState(key) == PRESSED;
}

///
/// Define MouseManager functions/methods
///
MouseManager::MouseManager() : leftMouseButtonState(MOUSE_RELEASED), middleMouseButtonState(MOUSE_RELEASED), rightMouseButtonState(MOUSE_RELEASED), x(0), y(0), grabbed(false)
{
}

void mouseManagerHandleMouseClick(int button, int state, int x, int y)
{
/*
The first relates to which button was pressed, or released. This argument can have one of three values:
    GLUT_LEFT_BUTTON
    GLUT_MIDDLE_BUTTON
    GLUT_RIGHT_BUTTON
The second argument relates to the state of the button when the callback was generated, i.e. pressed or released. The possible values are:
    GLUT_DOWN
    GLUT_UP
*/
    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            gameLoopObject.mouseManager.leftMouseButtonState = MouseManager::MOUSE_PRESSED;
        }
        if(state == GLUT_UP)
        {
            gameLoopObject.mouseManager.leftMouseButtonState = MouseManager::MOUSE_RELEASED;
        }
    }
    if(button == GLUT_MIDDLE_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            gameLoopObject.mouseManager.middleMouseButtonState = MouseManager::MOUSE_PRESSED;
        }
        if(state == GLUT_UP)
        {
            gameLoopObject.mouseManager.middleMouseButtonState = MouseManager::MOUSE_RELEASED;
        }
    }
    if(button == GLUT_RIGHT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            gameLoopObject.mouseManager.rightMouseButtonState = MouseManager::MOUSE_PRESSED;
        }
        if(state == GLUT_UP)
        {
            gameLoopObject.mouseManager.rightMouseButtonState = MouseManager::MOUSE_RELEASED;
        }
    }
    gameLoopObject.mouseManager.x = x;
    gameLoopObject.mouseManager.y = y;
}

// active mouse movement: active motion occurs when the mouse is moved and a button is pressed.
void mouseManagerHandleMouseMovementWhileClicked(int x, int y)
{
    // Do stuff with the mouse clicked then dragged
    static bool warped = false;
    if(warped)
    {
        warped = false;
        return;
    }
    if(gameLoopObject.mouseManager.grabbed)
    {
        warped = true;
        int width = getWindowWidth();
        int height = getWindowHeight();
        int centerX = (float)width / 2.0;
        int centerY = (float)height / 2.0;
        int deltaX = (x - centerX);
        int deltaY = (y - centerY);
        glm::vec3 dir(deltaX , deltaY , 0);
        gameLoopObject.mouseManager.relativeGrabDirection = dir;
        glutWarpPointer( glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2 );
        gameLoopObject.mouseManager.x = x;
        gameLoopObject.mouseManager.y = y;
    }
    else
    {
        gameLoopObject.mouseManager.x = x;
        gameLoopObject.mouseManager.y = y;
    }
}

// passive mouse movement: movement that occurs when the mouse is not clicked.
void mouseManagerHandleMouseMovementWhileNotClicked(int x, int y)
{
    // Do stuff while the mouse isn't clicked, but dragged
    static bool warped = false;
    if(warped)
    {
        warped = false;
        return;
    }
    if(gameLoopObject.mouseManager.grabbed)
    {
        warped = true;
        int width = getWindowWidth();
        int height = getWindowHeight();
        int centerX = (float)width / 2.0;
        int centerY = (float)height / 2.0;
        int deltaX = (x - centerX);
        int deltaY = (y - centerY);
        glm::vec3 dir(deltaX , deltaY , 0);
        gameLoopObject.mouseManager.relativeGrabDirection = dir;
        glutWarpPointer( glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2 );
        gameLoopObject.mouseManager.x = x;
        gameLoopObject.mouseManager.y = y;
    }
    else
    {
        gameLoopObject.mouseManager.x = x;
        gameLoopObject.mouseManager.y = y;
    }
}

void MouseManager::setGrabbed(bool grabbed)
{
    this->grabbed = grabbed;
    if(grabbed)
    {
        glutSetCursor(GLUT_CURSOR_NONE);
    }
    else
    {
        glutSetCursor(GLUT_CURSOR_LEFT_SIDE);
    }
}

glm::vec3 MouseManager::getRelativeGrabDirection()
{
    if(grabbed)
    {
        return this->relativeGrabDirection;
    }
    else
    {
        return glm::vec3(0, 0, 0);
    }
}



