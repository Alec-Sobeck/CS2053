
#include "keys.h"

/*

import java.util.List;

import mapping.MappingUtility;
import math.Vector3;

import org.lwjgl.input.Keyboard;
import org.lwjgl.input.Mouse;

import render.DrawableModel;
import render.ModTerRenderer;
import render.Render;
import utils.ObjParser;
import world.Map;
import world.Model;



void handleKeyboardInput(Entity &player, Map &map)
{
	static bool DEBUG_LOCK_FOV_OUT = false;
	static bool DEBUG_LOCK_FOV_IN = false;
	static bool DEBUG_LOCK_8 = false;
	static bool DEBUG_LOCK_9 = false;
	static bool DEBUG_LOCK_7 = false;
	static bool DEBUG_LOCK_0 = false;
	static bool isRBracketDown = false;
	static bool isLBracketDown = false;
	static bool is1Down = false;
	static bool is2Down = false;
	static bool shouldTether = true;
	static bool isTabDown = false;

    ///<DebugKeys>
    if(Keyboard.isKeyDown(Keyboard.KEY_F3) && !DEBUG_LOCK_FOV_OUT){
        DEBUG_LOCK_FOV_OUT = true;
        MappingUtility.getSettings().addToFieldOfViewAngle(5);
        System.out.println(MappingUtility.getSettings().getFieldOfViewAngle());
    }
    if(!Keyboard.isKeyDown(Keyboard.KEY_F3)){
        DEBUG_LOCK_FOV_OUT = false;
    }

    if(Keyboard.isKeyDown(Keyboard.KEY_F4) && !DEBUG_LOCK_FOV_IN){
        DEBUG_LOCK_FOV_IN = true;
        MappingUtility.getSettings().removeFromFieldOfViewAngle(5);
        System.out.println(MappingUtility.getSettings().getFieldOfViewAngle());
    }
    if(!Keyboard.isKeyDown(Keyboard.KEY_F4)){
        DEBUG_LOCK_FOV_IN = false;
    }



    if(Keyboard.isKeyDown(Keyboard.KEY_8) && !DEBUG_LOCK_8){
        DEBUG_LOCK_8 = true;
        ModTerRenderer.doStuffAdd2();
    }
    if(!Keyboard.isKeyDown(Keyboard.KEY_8)){
        DEBUG_LOCK_8 = false;
    }

    if(Keyboard.isKeyDown(Keyboard.KEY_7) && !DEBUG_LOCK_7){
        DEBUG_LOCK_7 = true;
        ModTerRenderer.doStuffAdd1();
    }
    if(!Keyboard.isKeyDown(Keyboard.KEY_7)){
        DEBUG_LOCK_7 = false;
    }

    if(Keyboard.isKeyDown(Keyboard.KEY_9) && !DEBUG_LOCK_9){
        DEBUG_LOCK_9 = true;
        ModTerRenderer.doStuffRemove1();
    }
    if(!Keyboard.isKeyDown(Keyboard.KEY_9)){
        DEBUG_LOCK_9 = false;
    }

    if(Keyboard.isKeyDown(Keyboard.KEY_0) && !DEBUG_LOCK_0){
        DEBUG_LOCK_0 = true;
        ModTerRenderer.doStuffRemove2();
    }
    if(!Keyboard.isKeyDown(Keyboard.KEY_0)){
        DEBUG_LOCK_0 = false;
    }

    if(Keyboard.isKeyDown(Keyboard.KEY_1) && !is1Down){
        is1Down = true;
        DrawableModel tempModel = new DrawableModel(pyro.exportModel());
        tempModel.setOrigin(new Vector3(player.getX(), player.getY(), player.getZ()));
        map.addModel(tempModel);
        if (selectedModel == null){
            selectedModel = tempModel;
        }
    }
    else if (is1Down && !Keyboard.isKeyDown(Keyboard.KEY_1))
    {
        is1Down = false;
    }

    if(Keyboard.isKeyDown(Keyboard.KEY_2) && !is2Down){
        is2Down = true;
        DrawableModel tempModel = new DrawableModel(box.exportModel());
        tempModel.setOrigin(new Vector3(player.getX(), player.getY(), player.getZ()));
        map.addModel(tempModel);
        if (selectedModel == null){
            selectedModel = tempModel;
        }
    }
    else if (is2Down && !Keyboard.isKeyDown(Keyboard.KEY_2)){
        is2Down = false;
    }
    ///</DebugKeys>
    if(Keyboard.isKeyDown(Keyboard.KEY_W)){
        player.accel(new Vector3(Math.sin(player.getRotation().getY()),
                0,
                -Math.cos(player.getRotation().getY())));
    }
    if(Keyboard.isKeyDown(Keyboard.KEY_S)){
        player.accel(new Vector3(-Math.sin(player.getRotation().getY()),
                0,
                Math.cos(player.getRotation().getY())));
    }
    if(Keyboard.isKeyDown(Keyboard.KEY_A)){
        player.accel(new Vector3(-Math.cos(player.getRotation().getY()),
                0,
                -Math.sin(player.getRotation().getY())));
    }
    if(Keyboard.isKeyDown(Keyboard.KEY_D)){
        player.accel(new Vector3(Math.cos(player.getRotation().getY()),
                0,
                Math.sin(player.getRotation().getY())));
    }
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

    if(Keyboard.isKeyDown(Keyboard.KEY_SPACE)){
        player.accel(new Vector3(0, 1, 0));
    }
    if(Keyboard.isKeyDown(Keyboard.KEY_LSHIFT)){
        player.accel(new Vector3(0, -1, 0));
    }

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

    //Model manipulations
    if(Keyboard.isKeyDown(Keyboard.KEY_EQUALS)){
        if (selectedModel != null){
            selectedModel.scaleModel(1.01f, true, true, true);
        }
    }

    if(Keyboard.isKeyDown(Keyboard.KEY_MINUS)){
        if (selectedModel != null){
            selectedModel.scaleModel(0.99f, true, true, true);
        }
    }

    if(Keyboard.isKeyDown(Keyboard.KEY_J)){
        if (selectedModel != null){
            selectedModel.rotate(new Vector3(0.0, 1.0, 0.0));
        }
    }
    if(Keyboard.isKeyDown(Keyboard.KEY_L)){
        if (selectedModel != null){
            selectedModel.rotate(new Vector3(0.0, -1.0, 0.0));
        }
    }
    if(Keyboard.isKeyDown(Keyboard.KEY_K)){
        if (selectedModel != null){
            selectedModel.rotate(new Vector3(-1.0, 0.0, 0.0));
        }
    }
    if(Keyboard.isKeyDown(Keyboard.KEY_I)){
        if (selectedModel != null){
            selectedModel.rotate(new Vector3(1.0, 0.0, 0.0));
        }
    }
    if(Keyboard.isKeyDown(Keyboard.KEY_O)){
        if (selectedModel != null){
            selectedModel.rotate(new Vector3(0.0, 0.0, -1.0));
        }
    }
    if(Keyboard.isKeyDown(Keyboard.KEY_U)){
        if (selectedModel != null){
            selectedModel.rotate(new Vector3(0.0, 0.0, 1.0));
        }
    }
    if(Keyboard.isKeyDown(Keyboard.KEY_LEFT)){
        if (selectedModel != null){
            selectedModel.translate(new Vector3(-Math.cos(player.getRotation().getY()),
                                                0,
                                                -Math.sin(player.getRotation().getY())));
        }
    }
    if(Keyboard.isKeyDown(Keyboard.KEY_RIGHT)){
        if (selectedModel != null){
            selectedModel.translate(new Vector3(Math.cos(player.getRotation().getY()),
                    0,
                    Math.sin(player.getRotation().getY())));
        }
    }
    if(Keyboard.isKeyDown(Keyboard.KEY_UP)){
        if (selectedModel != null){
            selectedModel.translate((new Vector3(Math.sin(player.getRotation().getY()),
                                                0,
                                                -Math.cos(player.getRotation().getY()))));
        }
    }
    if(Keyboard.isKeyDown(Keyboard.KEY_DOWN)){
        if (selectedModel != null){
            selectedModel.translate(new Vector3(-Math.sin(player.getRotation().getY()),
                                                0,
                                                Math.cos(player.getRotation().getY())));
        }
    }
    //End model manipulations
    if (shouldTether && selectedModel != null)
    {
        Vector3 vectorModelToPlayer =  new Vector3(player.getPosition().getX() - selectedModel.getOrigin().getX(),
                                                    player.getPosition().getY() - selectedModel.getOrigin().getY(),
                                                    player.getPosition().getZ() - selectedModel.getOrigin().getZ());
        if (vectorModelToPlayer.length() > 20){
            selectedModel.translate(new Vector3(vectorModelToPlayer.getX() * 0.05,
                                                vectorModelToPlayer.getY() * 0.05,
                                                vectorModelToPlayer.getZ() * 0.05));
        }
    }
}
*/
