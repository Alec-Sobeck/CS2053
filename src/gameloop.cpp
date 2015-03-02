
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
#include "graphics/gluhelper.h"
#include "render/render.h"

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
void handleMouseClick(int button, int state, int x, int y);
void handleMouseMovementWhileClicked(int x,int y);
void handleMouseMovementWhileNotClicked(int x, int y);
void processSpecialKeys(int key, int x, int y);
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
    static const unsigned char JUST_PRESSED = 0;
    static const unsigned char RELEASED = 1;
    static const unsigned char STILL_PRESSED = 2;
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

    GameLoop();
    void buildSampleTerrain();
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
     ///// TODO -- initializeTextures()
    gameLoopObject.buildSampleTerrain();
}

///***********************************************************************
///***********************************************************************
/// Define the GameLoop class methods.
///***********************************************************************
///***********************************************************************
GameLoop::GameLoop() : gameIsRunning(true), player(Entity()), map(Map(AABB(-200, -10, -200, 200, 10, 200))), startTime(getCurrentTimeMillis()),
        terrainRenderer(std::shared_ptr<TerrainRenderer>(nullptr))
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
    std::shared_ptr<Terrain> terrain(new MidPointTerrain(3, 0.6f, 50, 200));
//  terrain = new InterpTestNoiseTerrain(10, 10, 50, 400);
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
    auto tex = getTexture("/home/alec/Dropbox/University/GameDev/GameEngineCPP/res/terrain.png");
    auto terrainExp = terrain->exportToTerrainData();
    this->terrainRenderer = std::shared_ptr<TerrainRenderer>(new TerrainRenderer());
    this->terrainRenderer->create(terrainExp, tex);

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

        processKeyboardInput();

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

        //std::cout << cam << ":" << cam->position.x << " " << cam->position.y << " " << cam->position.z << std::endl;

        end3DRenderCycle();
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
    // to check for a key modifier use:
    //       int glutGetModifiers(void);
    // The return value for this function is either one of three predefined constants or any bitwise OR combination of them. The constants are:
    //       GLUT_ACTIVE_SHIFT - Set if either you press the SHIFT key, or Caps Lock is on. Note that if they are both on then the constant is not set.
    //       GLUT_ACTIVE_CTRL - Set if you press the CTRL key.
    //       GLUT_ACTIVE_ALT - Set if you press the ALT key.
    Camera *camera = gameLoopObject.player.getCamera();
    KeyManager *manager = &gameLoopObject.keyManager;
    manager->update();

    if (manager->getKeyState(27) == KeyManager::STILL_PRESSED) // Escape key
	{
		exit(0);
	}

    if(manager->getKeyState('w') == KeyManager::STILL_PRESSED)
    {
        gameLoopObject.player.accel(glm::vec3(sin(gameLoopObject.player.getCamera()->rotation.y),
                0,
                -cos(gameLoopObject.player.getCamera()->rotation.y)));
    }
    if(manager->getKeyState('s') == KeyManager::STILL_PRESSED)
    {
        gameLoopObject.player.accel(glm::vec3(-sin(gameLoopObject.player.getCamera()->rotation.y),
                0,
                cos(gameLoopObject.player.getCamera()->rotation.y)));
    }
    if(manager->getKeyState('a') == KeyManager::STILL_PRESSED)
    {
        gameLoopObject.player.accel(glm::vec3(-cos(gameLoopObject.player.getCamera()->rotation.y),
                0,
                -sin(gameLoopObject.player.getCamera()->rotation.y)));
    }
    if(manager->getKeyState('d') == KeyManager::STILL_PRESSED)
    {
        gameLoopObject.player.accel(glm::vec3(cos(gameLoopObject.player.getCamera()->rotation.y),
                0,
                sin(gameLoopObject.player.getCamera()->rotation.y)));
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
    /*
    if(Keyboard.isKeyDown(Keyboard.KEY_TAB) && !isTabDown){
        isTabDown = true;
        if (Mouse.isGrabbed()){
            Mouse.setGrabbed(false);
        }
        else Mouse.setGrabbed(true);
    }
    else if(!Keyboard.isKeyDown(Keyboard.KEY_TAB)){
        isTabDown = false;
    }

    if(Keyboard.isKeyDown(Keyboard.KEY_PERIOD)){
        shouldTether = !shouldTether;
    }
    */

    if(manager->getKeyState(' ') == KeyManager::STILL_PRESSED)
    {
        gameLoopObject.player.accel(glm::vec3(0, 1, 0));
    }
    if(manager->getKeyState('x') == KeyManager::STILL_PRESSED)
    {
        gameLoopObject.player.accel(glm::vec3(0, -1, 0));
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

void handleMouseClick(int button, int state, int x, int y)
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
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
    }
}

// active mouse movement: active motion occurs when the mouse is moved and a button is pressed.
void handleMouseMovementWhileClicked(int x, int y)
{
    // Do stuff with the mouse clicked then dragged
}

// passive mouse movement: movement that occurs when the mouse is not clicked.
void handleMouseMovementWhileNotClicked(int x, int y)
{
    // Do stuff while the mouse isn't clicked, but dragged
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
	//glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);
	//glutKeyboardFunc(processNormalKeys);
	//glutSpecialFunc(processSpecialKeys);
    glutMouseFunc(handleMouseClick);
    glutMotionFunc(handleMouseMovementWhileClicked);
    glutPassiveMotionFunc(handleMouseMovementWhileNotClicked);
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
    if(gameLoopObject.keyManager.keystates[key] == KeyManager::RELEASED)
    {
        gameLoopObject.keyManager.keystates[key] = KeyManager::JUST_PRESSED;
    }
    if(gameLoopObject.keyManager.keystates[key] == KeyManager::JUST_PRESSED)
    {
        gameLoopObject.keyManager.keystates[key] = KeyManager::STILL_PRESSED;
    }
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

    if(gameLoopObject.keyManager.specialKeystates[key] == KeyManager::RELEASED)
    {
        gameLoopObject.keyManager.specialKeystates[key] = KeyManager::JUST_PRESSED;
    }
    if(gameLoopObject.keyManager.specialKeystates[key] == KeyManager::JUST_PRESSED)
    {
        gameLoopObject.keyManager.specialKeystates[key] = KeyManager::STILL_PRESSED;
    }
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
    return getKeyState(key) == JUST_PRESSED || getKeyState(key) == STILL_PRESSED;
}



