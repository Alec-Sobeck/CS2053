
#include <cmath>
#include <memory>
#include <stdlib.h>
#include <iostream>
#include <soil/SOIL.h>
#include <glbinding/gl/gl.h>
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
class KeyManager
{
public:
    static const int VALID_NUMBER_OF_CHARS = 1000000;
    static const int VALID_NUMBER_OF_SPECIALS = 1000;
    static const unsigned char RELEASED = 1;
    static const unsigned char PRESSED = 2;
    static const int KEY_F1 = 3;
    static const int KEY_F2 = 4;
    static const int KEY_F3 = 5;
    static const int KEY_F4 = 6;
    static const int KEY_F5 = 7;
    static const int KEY_F6 = 8;
    static const int KEY_F7 = 9;
    static const int KEY_F8 = 10;
    static const int KEY_F9 = 11;
    static const int KEY_F10 = 12;
    static const int KEY_F11 = 13;
    static const int KEY_F12 = 14;
    static const int KEY_LEFT = 15;
    static const int KEY_RIGHT = 16;
    static const int KEY_UP = 17;
    static const int KEY_DOWN = 18;
    static const int KEY_PAGE_UP = 19;
    static const int KEY_PAGE_DOWN = 20;
    static const int KEY_PAGE_HOME = 21;
    static const int KEY_PAGE_END = 22;
    static const int KEY_PAGE_INSERT = 23;

    unsigned char keystates[VALID_NUMBER_OF_CHARS];
    unsigned char specialKeystates[VALID_NUMBER_OF_SPECIALS];
    bool isShiftDown;
    bool isControlDown;
    bool isAltDown;
    unsigned char getKeyState(unsigned char key);
    unsigned char isKeyDown(unsigned char key);
    unsigned char getSpecialState(int key);
    KeyManager();
    void update();
    void updateModifierState();
};

void keyManagerKeyPressed(unsigned char key, int x, int y);
void keyManagerKeyUp (unsigned char key, int x, int y);
void keyManagerKeySpecial(int key, int x, int y);
void keyManagerKeySpecialUp(int key, int x, int y);
void updateModifierState();
///
/// Define the MouseManager class. Similarly to KeyManager this is in a fairly C-like style because GLUT is a C library.
///

class MouseManager
{
public:
    static const int MOUSE_RELEASED = 0;
    static const int MOUSE_PRESSED = 1;
    int leftMouseButtonState;
    int middleMouseButtonState;
    int rightMouseButtonState;
    int x;
    int y;
    bool grabbed;
    glm::vec3 relativeGrabDirection;
    MouseManager();
    void setGrabbed(bool);
    glm::vec3 getRelativeGrabDirection();
};

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
    Grass *grass; // TODO => [LEAK]this is never deleted
    std::shared_ptr<Model> treeModel;
	std::shared_ptr<GLFont> fontRenderer;
	unsigned long long previousFrameTime;
	float deltaTime;

    GameLoop();
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
void initializeEngine()
{
    using namespace gl;
     ///// TODO -- initializeTextures()
    initializeViewport();
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


    //Create font
	GLuint textureName;
	glGenTextures(1, &textureName);
	gameLoopObject.fontRenderer = std::shared_ptr<GLFont>(new GLFont());
	try
	{
#ifdef _WIN32
		gameLoopObject.fontRenderer->Create(getTexture("D:/Dropbox/University/GameDev/GameEngineCPP/res/font.png"));
#else
	gameLoopObject.fontRenderer->Create("/home/alec/Dropbox/University/GameDev/GameEngineCPP/res/glfont.glf", textureName);
#endif
	}
	catch(GLFontError::InvalidFile)
	{
		std::cout << "Cannot load font" << std::endl;
		exit(1);
	}
    gameLoopObject.buildSampleTerrain();
}

///***********************************************************************
///***********************************************************************
/// Define the GameLoop class methods.
///***********************************************************************
///***********************************************************************

///
/// Important usage note: a GL Context is not bound when this constructor is called. Using any gl functions with cause a segfault or crash.
///
GameLoop::GameLoop() : gameIsRunning(true), player(Entity()), map(Map(AABB(-200, -10, -200, 200, 10, 200))), startTime(getCurrentTimeMillis()),
	terrainRenderer(std::shared_ptr<TerrainRenderer>(nullptr)), grass(nullptr), previousFrameTime(getCurrentTimeMillis())
{
    player.setCamera(Camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)));
}

void GameLoop::buildSampleTerrain()
{
//shader = ShaderFactory.createShader(null, "shaders/animated1.frag");
    glm::vec3 v(getWindowWidth(), getWindowHeight(), 1.0);
//	shader.glUniform3v("iResolution", v);
//  shader.glUniform1f("iGlobalTime", 0.0f);
//  terrain = new TrigTerrain(10, 100);


    //std::shared_ptr<Terrain> terrain(new MidPointTerrain(3, 0.6f, 50, 200));

    std::shared_ptr<Terrain> terrain(new FlatTerrain(200));


    //terrain = new InterpTestNoiseTerrain(10, 10, 50, 400);
    //map.setTerrain(terrain->exportToTerrainData());
//  Set<TerrainPolygon> polys = map.getTerrainOctree().getRange(new AABB(-10, -10, -10, 10, 10, 10));
//  monkeyModel3.scaleModel(1.0f, true, true, true);
//  map.setTerrain(monkey.exportTerrain());
//  map.addModel(new DrawableModel(teapot.exportData()));
//  RenderSettingsHelper.initialize3DSettings();
//  map.addModel(new DrawableModel(ModelDataBuilder.getDerpyDefaultData()));
//  defaultMap.addTerrain(new TerrainPolygon());
//  defaultMap.buildTerrainRenderer();
    //createTerrainRenderer(terrain->exportToTerrainData());
#ifdef _WIN32
	auto tex = getTexture("D:/Dropbox/University/GameDev/GameEngineCPP/res/terrain.png");
	auto grassTexture = getTexture("D:/Dropbox/University/GameDev/GameEngineCPP/res/grass_1.png");
#else
	auto grassTexture = getTexture("/home/alec/Dropbox/University/GameDev/GameEngineCPP/res/grass_1.png");
	auto tex = getTexture("/home/alec/Dropbox/University/GameDev/GameEngineCPP/res/terrain.png");
#endif
	auto terrainExp = terrain->exportToTerrainData();
    this->terrainRenderer = std::shared_ptr<TerrainRenderer>(new TerrainRenderer());
    this->terrainRenderer->create(terrainExp, tex);

    gameLoopObject.grass = new Grass(50, glm::vec3(0,0,0), 50, grassTexture);

    /// Load tree model(s)
/*
    ObjParser parser("/home/alec/Dropbox/University/GameDev/GameEngineCPP/res/models/oak_tree1/Tree_V9_Final.obj", "bark_tree.jpg");
    ModelData data = parser.exportModel();
    auto treeTexture = getTexture(data.associatedTextureName);
    gameLoopObject.treeVBO = std::shared_ptr<VBO>(new VBO(data, treeTexture));

*/




    /// Pine tree?
#ifdef _WIN32
	ObjParser parser(
		"D:/Dropbox/University/GameDev/GameEngineCPP/res/models/pine_tree1/", "D:/Dropbox/University/GameDev/GameEngineCPP/res/models/pine_tree1/Tree.obj",
		"Branches0018_1_S.png", false );
	gameLoopObject.treeModel = parser.exportModel();
	auto treeTexture = getTexture("D:/Dropbox/University/GameDev/GameEngineCPP/res/models/pine_tree1/BarkDecidious0107_M.jpg");
	auto branchTexture = getTexture("D:/Dropbox/University/GameDev/GameEngineCPP/res/models/pine_tree1/Branches0018_1_S.png");
#else
	ObjParser parser(
		"/home/alec/Dropbox/University/GameDev/GameEngineCPP/res/models/pine_tree1/", "/home/alec/Dropbox/University/GameDev/GameEngineCPP/res/models/pine_tree1/Tree.obj",
		"Branches0018_1_S.png", false);
	gameLoopObject.treeModel = parser.exportModel();
	auto treeTexture = getTexture("/home/alec/Dropbox/University/GameDev/GameEngineCPP/res/models/pine_tree1/BarkDecidious0107_M.jpg");
	auto branchTexture = getTexture("/home/alec/Dropbox/University/GameDev/GameEngineCPP/res/models/pine_tree1/Branches0018_1_S.png");
#endif
    std::map<std::string, std::shared_ptr<Texture>> textures;
    textures["tree"] = treeTexture;
    textures["leaves"] = branchTexture;
    gameLoopObject.treeModel->createVBOs(textures);
/*
    ObjParser parser(
        "/home/alec/Dropbox/University/GameDev/GameEngineCPP/res/models/generic_tree1/Broad_Leaf_Straight_Trunk.obj", "Broad_Leaf_1.bmp"
    );
    gameLoopObject.treeModel = parser.exportModel();
    auto treeTexture = getTexture("/home/alec/Dropbox/University/GameDev/GameEngineCPP/res/models/generic_tree1/Broad_Leaf_1.bmp");
    std::map<std::string, std::shared_ptr<Texture>> textures;
    textures["tree"] = treeTexture;
    gameLoopObject.treeModel->overrideTexture = treeTexture;
    gameLoopObject.treeModel->createVBOs(textures);
*/
/*
    ObjParser parser(
        "/home/alec/Dropbox/University/GameDev/GameEngineCPP/res/models/generic_tree2/", "/home/alec/Dropbox/University/GameDev/GameEngineCPP/res/models/generic_tree2/Tree.obj", "Bottom_Trunk.bmp"
    );
    gameLoopObject.treeModel = parser.exportModel();
    auto leafTexture = getTexture("/home/alec/Dropbox/University/GameDev/GameEngineCPP/res/models/generic_tree2/Branches0018_1_S.png");
    auto treeTexture = getTexture("/home/alec/Dropbox/University/GameDev/GameEngineCPP/res/models/generic_tree2/BarkDecidious0107_M.jpg");
    std::map<std::string, std::shared_ptr<Texture>> textures;
    textures["tree"] = treeTexture;
    textures["leaves"] = leafTexture;
    gameLoopObject.treeModel->createVBOs(textures);
*/

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
}

///***********************************************************************
///***********************************************************************
/// Define Gameloop/render functions.
///***********************************************************************
///***********************************************************************
void gameUpdateTick()
{
    using namespace gl;

    //Variables for the gameloop cap (30 times / second)
    /*
    const int GAME_TICKS_PER_SECOND = 30;
    const int SKIP_TICKS = 1000 / GAME_TICKS_PER_SECOND;
    const int MAX_FRAMESKIP = 5;
    long long next_game_tick = getCurrentTimeMillis();
    int loops;
*/
    //This method may be commented out to block the terrain generation and rendering

    //Main Game Loop
   // while(gameLoopObject.gameIsRunning)
   // {
   //     loops = 0;
   //     while(getCurrentTimeMillis() > static_cast<unsigned long long>(next_game_tick) && loops < MAX_FRAMESKIP) //Update the game 30 times/second
    //    {
            //Take hardware input and chat and such; update graphics and whatnot
            //Keys.keyboard(player, map);
            //MouseHelper.update(player.getCamera());
            //ComponentHelper.getWindow().mouseAndKeyboardUpdate();
            //ComponentHelper.getWindow().mouseAndKeyboardUpdate();

            //Actual game world code here

    //        next_game_tick += SKIP_TICKS;
    //        loops++;
    //    }

        //Make sure the game loop doesn't fall very far behind and have to accelerate the
        //game for an extended period of time
    //    if(getCurrentTimeMillis() - next_game_tick > 1000)
    //    {
    //        next_game_tick = getCurrentTimeMillis();
    //    }

	gameLoopObject.update();

        processKeyboardInput();
        processMouseInput();

        //Draw here
        startRenderCycle();
        glClearDepth(1.0f);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        Camera *cam = gameLoopObject.player.getCamera();
        startRenderCycle();
        start3DRenderCycle();

        glDisable(GL_TEXTURE_2D);
        renderAxes(cam);

        gameLoopObject.player.move();
        gameLoopObject.terrainRenderer->draw(cam);


    /// DRAW -- tree


        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glDisable(GL_BLEND);
        glAlphaFunc(GL_GREATER, 0.1f);
        glEnable(GL_ALPHA_TEST);
        //glDisable(GL_CULL_FACE);
        glLoadIdentity();
        glEnable(GL_TEXTURE_2D);
        // Translate to model co-ordinates, based on the origin of the shape
        setLookAt(cam);
        glDisable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
//        glCullFace(GL_BACK);

        //glTranslatef(0.0f, 5.0f, 0.0f);
        for(int i = 0; i < 1; i++)
        {
        //    glTranslatef(5.0f, 0.0f, 0.0f);
            gameLoopObject.treeModel->draw(cam);
        }

        //glEnable(GL_CULL_FACE);
///        glDisable(GL_ALPHA_TEST);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);


    /// END DRAW -- tree
        gameLoopObject.grass->update(cam);
        gameLoopObject.grass->draw(cam);
        end3DRenderCycle();

        start2DRenderCycle();
        gameLoopObject.drawString("hello world", 50, 50, 0, RED);
        end2DRenderCycle();
        endRenderCycle();

/*
        RenderSettingsHelper.start3DRenderCycle();
        Render.renderAxes(player.getCamera());
        player.move();

        if(terrain != null)
        {
            //shader.bindShader();
            ModTerRenderer.draw(player.getCamera());
            //shader.releaseShader();

            map.draw(player.getCamera());
        }



        RenderSettingsHelper.end3DRenderCycle();
        ComponentHelper.getWindow().draw();
        RenderSettingsHelper.endRenderCycle();
*/

//        		if(Mouse.isButtonDown(0))
//        		{
//        			System.out.println(Unprojection.unproject(mappingCamera, Mouse.getX(), Mouse.getY(), mappingCamera.getZ()));
//        		}

        //End drawing now



/*
        static bool loadTexture = false;
        static std::shared_ptr<Texture> texture(nullptr);
        if(!loadTexture)
        {
            loadTexture = true;
            texture = getTexture(
                "/home/alec/Dropbox/University/GameDev/GameEngineCPP/res/img_test.png"
            );
        }

        // Clear Color and Depth Buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Reset transformations
        gl::glLoadIdentity();
        // Set the camera
        setGluLookAt(	0.0f, 0.0f, 10.0f,
                    0.0f, 0.0f,  0.0f,
                    0.0f, 1.0f,  0.0f);
        gl::glRotatef(10.0, 0.0f, 1.0f, 0.0f);

        glEnable(GL_TEXTURE_2D);
        texture->bind();

        glBegin(GL_QUADS);
          glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
          glTexCoord2f(0, 1); glVertex3f(0, 10, 0);
          glTexCoord2f(1, 1); glVertex3f(10, 10, 0);
          glTexCoord2f(1, 0); glVertex3f(10, 0, 0);
        glEnd();

        swapBuffers();

        // Clear Color and Depth Buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Reset transformations
        gl::glLoadIdentity();
        // Set the camera
        setGluLookAt(	0.0f, 0.0f, 10.0f,
                    0.0f, 0.0f,  0.0f,
                    0.0f, 1.0f,  0.0f);
        gl::glRotatef(10.0, 0.0f, 1.0f, 0.0f);

        glEnable(GL_TEXTURE_2D);
        texture->bind();

        glBegin(GL_QUADS);
          glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
          glTexCoord2f(0, 1); glVertex3f(0, 10, 0);
          glTexCoord2f(1, 1); glVertex3f(10, 10, 0);
          glTexCoord2f(1, 0); glVertex3f(10, 0, 0);
        glEnd();

        swapBuffers();
        */
   // }
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

    if(manager->grabbed)
    {
        glm::vec3 *grabDir = &manager->relativeGrabDirection;
        if (grabDir->x < -2)
        {
            cam->rotate(glm::vec3(0, -0.01, 0));
        }
        else if (grabDir->x > 2)
        {
            cam->rotate(glm::vec3(0, 0.01, 0));
        }
        if (grabDir->y < -2)
        {
            cam->rotate(glm::vec3(-0.01, 0, 0));
        }
        else if (grabDir->y > 2)
        {
            cam->rotate(glm::vec3(0.01, 0, 0));
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



