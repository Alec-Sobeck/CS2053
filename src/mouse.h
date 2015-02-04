#ifndef GAME_MOUSE_H
#define GAME_MOUSE_H

/*
package hardware;

import math.Vector3;
import opengl.RenderSettingsHelper;

import org.lwjgl.input.Mouse;

import world.Camera;

public class MouseHelper
{

	public static void mouseWheel(Camera cam)
	{
		if(Mouse.hasWheel())
		{
			int wheelMovement = Mouse.getDWheel();
			if (wheelMovement > 0) //If mouse scrolled up
			{
				cam.removeFromCurrentZoom(0.01);
//				System.out.println("Current Zoom: " + cam.getCurrentZoom());
			}
			else if(wheelMovement < 0) //If mouse scrolled down
			{
				cam.addToCurrentZoom(0.01);
//				System.out.println("Current Zoom: " + cam.getCurrentZoom());
			}
		}
	}

	public static void update(Camera cam)
	{
		mouseWheel(cam);
		int dx = RenderSettingsHelper.getWidth() / 2 - Mouse.getX();
		int dy = RenderSettingsHelper.getHeight() / 2 - Mouse.getY();
		if (Mouse.isGrabbed()) {
			if (dx < -2) {
				cam.rotate(new Vector3(0, 0.05, 0));
			} else if (dx > 2) {
				cam.rotate(new Vector3(0, -0.05, 0));
			}
			if (dy < -2) {
				cam.rotate(new Vector3(-0.05, 0, 0));
			} else if (dy > 2) {
				cam.rotate(new Vector3(0.05, 0, 0));
			}
			Mouse.setCursorPosition(RenderSettingsHelper.getWidth() / 2,
					RenderSettingsHelper.getHeight() / 2);
		}

	}

	public static int getXPos() {
		return Mouse.getX();
	}

	public static int getYPos() {
		return Mouse.getY();
	}
}

*/
#endif
