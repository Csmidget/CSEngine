#ifndef GAME_ENGINE_INPUT_H
#define GAME_ENGINE_INPUT_H

#include <vector>
#include <map>
#include <memory>
#include "SDL\SDL.h"
#include "input/KeyCode.h"
#include "glm\glm.hpp"

namespace GameEngine {

	//!Stores information on individual controller
	struct Controller
	{
		//!Pointer to SDL controller.
		SDL_GameController* controller;
		//!The name of this controller (Normally "xinput Controller")
		std::string name;
		//!Buttons currently being held down
		std::vector<int> heldButtons;
		//!Buttons that have just been pressed
		std::vector<int> downButtons;
		//!Buttons that have been released this frame
		std::vector<int>   upButtons;
		//!Information on controller analogue sticks Left stick:[0],[1]|Right stick:[1],[2] 
		float analogueAxis[6] = { 0,0,0,0,0,0 };
	};
	//! Used for connecting instance id to device id.
	typedef std::map<int, int> DeviceInstanceMap;

	//!Class that manages user input. Stores information on keyboard,mouse and controller input.
	class Input {

		friend class Application;

	private:
		//!Map from Controller instance to deviceNumber in controller list.
		static DeviceInstanceMap controllerInstances;
		//!List of active controllers
		static std::vector<std::shared_ptr<Controller>> controllers;

		//!Keys currently being held down
		static std::vector<int> heldKeys;
		//!Keys that have just been pressed
		static std::vector<int> downKeys;
		//!Keys that have been released this frame
		static std::vector<int> upKeys;

		//!Mouse buttons currently being held down
		static std::vector<int> heldMouseButtons;
		//!Mouse buttons that have just been pressed
		static std::vector<int> downMouseButtons;
		//!Mouse buttons that have been released this frame
		static std::vector<int> upMouseButtons;

		//!The X position of the mouse within the window (Left = 0)
		static int mousePosX;
		//!The Y position of the mouse within the window (Top = 0)
		static int mousePosY;
		//!The mouse wheel change this frame. 1 = scroll up| -1 = scroll down
		static int mouseWheel;
		//!True if the mouse has moved since the last frame
		static bool mouseMoved;

		static void ProcessKeyEvent(SDL_KeyboardEvent         &_event);
		static void ProcessMouseButtonEvent(SDL_MouseButtonEvent      &_event);
		static void ProcessMouseMotionEvent(SDL_MouseMotionEvent      &_event);
		static void ProcessMouseWheelEvent(SDL_MouseWheelEvent       &_event);
		static void ProcessControllerButtonEvent(SDL_ControllerButtonEvent &_event);
		static void ProcessControllerAxisEvent(SDL_ControllerAxisEvent   &_event);

		//!Adds a controller to the list of active controllers. Called if new controller is detected.
		static void AddController(int _deviceNumber);
		//!Removes a controller from the list of active controllers. Called if a Controller is unplugged.
		static void RemoveController(int _deviceNumber);

		//!Runs at the start of every frame to refresh vectors etc ready for new information.
		static void RefreshEvents();

	public:

		//!The number of controllers currently active
		static int NumControllers() { return controllers.size(); }

		//!Checks if the provided keyboard KeyCode is currently beind held
		/*!
		\param _keyCode The KeyCode to check
		*/
		static bool KeyHeld(int _keyCode);

		//!Checks if the provided keyboard KeyCode was pressed this frame
		/*!
		\param _keyCode The KeyCode to check
		*/
		static bool KeyDown(int _keyCode);

		//!Checks if the provided keyboard KeyCode was released this frame
		/*!
		\param _keyCode The KeyCode to check
		*/
		static bool KeyUp(int _keyCode);

		//!Checks if the provided Mouse button MouseCode is currently beind held
		/*!
		\param _mouseCode The MouseCode to check
		*/
		static bool MouseButtonHeld(int _mouseCode);

		//!Checks if the provided Mouse button MouseCode was pressed this frame
		/*!
		\param _mouseCode The MouseCode to check
		*/
		static bool MouseButtonUp(int _mouseCode);

		//!Checks if the provided Mouse button MouseCode was released this frame
		/*!
		\param _mouseCode The MouseCode to check
		*/
		static bool MouseButtonDown(int _mouseCode);

		//!Sets the parameter values equal to the current mousePosX and mousePosY
		/*!
		\param _x The parameter to replace with mousePosX
		\param _y The parameter to replace with mousePosY
		*/
		static void GetMousePos(int *_x, int *_y);

		//!Checks if the ControllerCode on entered device is held
		/*!
		\param _deviceNumber The Controller id to check
		\param _controllerCode The controller button to check
		*/
		static bool ContButtonHeld(int _deviceNumber, int _controllerCode);

		//!Checks if the ControllerCode on entered device was released this frame
		/*!
		\param _deviceNumber The Controller id to check
		\param _controllerCode The controller button to check
		*/
		static bool ContButtonUp(int _deviceNumber, int _controllerCode);

		//!Checks if the ControllerCode on entered device was released last frame
		/*!
		\param _deviceNumber The Controller id to check
		\param _controllerCode The controller button to check
		*/
		static bool ContButtonDown(int _deviceNumber, int _controllerCode);

		//!Returns the value of one of the axes on a controllers analogue sticks.
		/*!
		\param _deviceNumber The Controller id to check
		\param _analogueNumber The analogue stick to check (0,1);
		\param _axisNumber The axis to check (X=0,Y=1);
		*/
		static float GetContAnalogueAxis(int _deviceNumber, int _analogueNumber, int _axisNumber);
	};

}//namespace GameEngine

#endif
