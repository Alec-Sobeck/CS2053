
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
    Entity player;
    std::shared_ptr<TerrainData> terrain;
    Map map;
    long startTime;
    std::shared_ptr<TerrainRenderer> terrainRenderer;
    KeyManager keyManager;
    MouseManager mouseManager;
    Grass *grass; 
    std::shared_ptr<Model> treeModel;
	std::shared_ptr<GLFont> fontRenderer;
	unsigned long long previousFrameTime;
	float deltaTime;
	std::shared_ptr<Texture> ammoTexture;
	std::shared_ptr<Texture> medkitTexture;
	std::vector<Projectile> projectiles;
	FMOD::System* system = NULL;
	FMOD::Sound *music;
	FMOD::Channel* musicChannel;
	FMOD::Studio::EventInstance* eventInstance;
	FMOD::Studio::EventInstance* bgmInstance;
	std::list<Tree> trees;
	bool hasStartedBGM = false;
	std::vector<std::shared_ptr<Enemy>> enemies;

    GameLoop();
	~GameLoop();
    void buildSampleTerrain();
	void update();
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
	//ERRCHECK(gameLoopObject.eventInstance->start());

	FMOD::Studio::EventDescription* bgmDescription = NULL;
	ERRCHECK(system->getEvent("event:/bgm-battle-01", &bgmDescription));
	gameLoopObject.bgmInstance = NULL;
	ERRCHECK(bgmDescription->createInstance(&gameLoopObject.bgmInstance));
	//ERRCHECK(gameLoopObject.bgmInstance->start());
//	gameLoopObject.bgmInstance->setVolume(0.4f);

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
GameLoop::GameLoop() : gameIsRunning(true), player(Entity()), map(Map(AABB(-200, -10, -200, 200, 10, 200))), startTime(getCurrentTimeMillis()),
	terrainRenderer(std::shared_ptr<TerrainRenderer>(nullptr)), grass(nullptr), previousFrameTime(getCurrentTimeMillis())
{
	// Important usage note: a GL Context is not bound when this constructor is called. Using any gl functions with cause a segfault or crash.
	player.setCamera(Camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)));
}

GameLoop::~GameLoop()
{
	ERRCHECK(system->release());
	if (grass)
	{
		delete grass;
	}
}

void GameLoop::buildSampleTerrain()
{
    glm::vec3 v(getWindowWidth(), getWindowHeight(), 1.0);
    std::shared_ptr<Terrain> terrain(new FlatTerrain(200));

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
        fontRenderer->TextOut("hello world", 50, 50, 0);
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

	/*
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);

	GLfloat global_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
		
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// note, no alpha is required since it has no use in specifying a light
	// source (in this case). Keep in mind however, that its default value
	// is 1.0f anyway
	// Create light components
	GLfloat ambientLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
	GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat position[] = { 20, 20, 0, 1.0f };

	// Assign created components to GL_LIGHT0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glDisable(GL_TEXTURE_2D);
	*/
	renderAxes(cam);
    gameLoopObject.player.move();
    gameLoopObject.terrainRenderer->draw(cam);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glDisable(GL_TEXTURE_2D);
	for (int i = 0; i < gameLoopObject.projectiles.size(); )
	{
		Projectile &p = gameLoopObject.projectiles.at(i);
		p.onGameTick(deltaTime);
			
		if (p.getY() < -p.size)
		{
			gameLoopObject.projectiles.erase(gameLoopObject.projectiles.begin() + i);
		}
		else
		{
			p.draw();
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
    //glDisable(GL_CULL_FACE);
	gl::glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    // Translate to model co-ordinates, based on the origin of the shape
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

	glDisable(GL_TEXTURE_2D);
	for (std::shared_ptr<Enemy> enemy: gameLoopObject.enemies)
	{
		enemy->onGameTick(gameLoopObject.player, deltaTime);
		AABB box = enemy->getAABB();
		drawAABB(box);
	}
	glEnable(GL_TEXTURE_2D);

	gameLoopObject.grass->update(cam);
    gameLoopObject.grass->draw(cam);
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

	static bool fireLock = false;
	if (manager->isKeyDown('f') && !fireLock)
	{
		fireLock = true;
		Camera cam(gameLoopObject.player.getPosition(), glm::vec3(0, 0, 0));
		Projectile projectile(cam, 1);
		glm::vec3 acceleration = glm::vec3(
			sin(gameLoopObject.player.getCamera()->rotation.y),
			0,
			-cos(gameLoopObject.player.getCamera()->rotation.y)
			) * 25.0f;
		acceleration.y -= 9.8f;
		projectile.accel(acceleration);
		gameLoopObject.projectiles.push_back(projectile);
	}
	if (!manager->isKeyDown('f'))
	{
		fireLock = false;
	}

	static bool enemyLock = false;
	if (manager->isKeyDown('m') && !enemyLock)
	{
		enemyLock = true;
		std::shared_ptr<Enemy> enemy(new Enemy(std::shared_ptr<Model>(nullptr), Camera(glm::vec3(getRandomInt(30) - 15, 0, getRandomInt(30) - 15), glm::vec3(0, 0, 0))));
		enemy->boundingBox = AABB(0, 0, 0, 1, 1, 1);
		gameLoopObject.enemies.push_back(enemy);
	}
	if (!manager->isKeyDown('m'))
	{
		enemyLock = false;
	}


	if (manager->isKeyDown('g'))
	{
		gameLoopObject.player.health += 10.0f * deltaTime;
	}
	if (manager->isKeyDown('h'))
	{
		gameLoopObject.player.health -= 10.0f * deltaTime;		
		ERRCHECK(gameLoopObject.eventInstance->start());
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
    if(Keyboard.isKeyDown(Keyboard.KEY_PERIOD)){
        shouldTether = !shouldTether;
    }
    */

    if(manager->getKeyState(' ') == KeyManager::PRESSED)
    {
        gameLoopObject.player.accel(glm::vec3(0, 1, 0) * deltaTime);
    }
    if(manager->getKeyState('x') == KeyManager::PRESSED)
    {
		gameLoopObject.player.accel(glm::vec3(0, -1, 0) * deltaTime);
    }
    /*
    if(Keyboard.isKeyDown(Keyboard.KEY_LBRACKET) && !isLBracketDown){
        isLBracketDown = true;
        List<Model> models = map.getModels();
        if (models != null && models.size() != 0){
            if (selectedModel.getID() > 0){
                selectedModel = models.get(selectedModel.getID() - 1);
            }
            else
            {
                selectedModel = models.get(models.size() - 1);
            }
        }
    }
    else if (isLBracketDown && !Keyboard.isKeyDown(Keyboard.KEY_LBRACKET)){
        isLBracketDown = false;
    }

    if(Keyboard.isKeyDown(Keyboard.KEY_RBRACKET) && !isRBracketDown){
        isRBracketDown = true;
        List<Model> models = map.getModels();
        if (models != null && models.size() != 0){
            if (selectedModel.getID() < models.size() - 1){
                selectedModel = models.get(selectedModel.getID() + 1);
            }
            else
            {
                selectedModel = models.get(0);
            }
        }
    }
    else if (isRBracketDown && !Keyboard.isKeyDown(Keyboard.KEY_RBRACKET)){
        isRBracketDown = false;
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
			cam->rotate(glm::vec3(0, -0.6, 0) * deltaTime);
        }
        else if (grabDir->x > 2)
        {
            cam->rotate(glm::vec3(0, 0.6, 0) * deltaTime);
        }
        if (grabDir->y < -2)
        {
			cam->rotate(glm::vec3(-0.6, 0, 0) * deltaTime);
        }
        else if (grabDir->y > 2)
        {
			cam->rotate(glm::vec3(0.6, 0, 0) * deltaTime);
        }
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



