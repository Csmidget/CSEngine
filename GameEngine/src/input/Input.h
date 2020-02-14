#ifndef GAME_ENGINE_INPUT_H
#define GAME_ENGINE_INPUT_H

#include "KeyCode_SDL.h"

namespace GameEngine {

	//!Class that manages user input. Stores information on keyboard,mouse and controller input.
	class Input {

		friend class Application;
		friend std::shared_ptr<Input> CreateInput();

	protected:
		virtual void ProcessEvents() = 0;

	public:

		//!The number of controllers currently active
		virtual int NumControllers() const = 0;// { return controllers.size(); }

		//!Checks if the provided keyboard KeyCode is currently beind held
		/*!
		\param _keyCode The KeyCode to check
		*/
		virtual bool KeyHeld(int _keyCode) const = 0;

		//!Checks if the provided keyboard KeyCode was pressed this frame
		/*!
		\param _keyCode The KeyCode to check
		*/
		virtual bool KeyDown(int _keyCode) const = 0;

		//!Checks if the provided keyboard KeyCode was released this frame
		/*!
		\param _keyCode The KeyCode to check
		*/
		virtual bool KeyUp(int _keyCode) const = 0;

		//!Checks if the provided Mouse button MouseCode is currently beind held
		/*!
		\param _mouseCode The MouseCode to check
		*/
		virtual bool MouseButtonHeld(int _mouseCode) const = 0;

		//!Checks if the provided Mouse button MouseCode was pressed this frame
		/*!
		\param _mouseCode The MouseCode to check
		*/
		virtual bool MouseButtonUp(int _mouseCode) const = 0;

		//!Checks if the provided Mouse button MouseCode was released this frame
		/*!
		\param _mouseCode The MouseCode to check
		*/
		virtual bool MouseButtonDown(int _mouseCode) const = 0;

		//!Sets the parameter values equal to the current mousePosX and mousePosY
		/*!
		\param _x The parameter to replace with mousePosX
		\param _y The parameter to replace with mousePosY
		*/
		virtual void GetMousePos(int *_x, int *_y) const = 0;

		//!Checks if the ControllerCode on entered device is held
		/*!
		\param _deviceNumber The Controller id to check
		\param _controllerCode The controller button to check
		*/
		virtual bool ContButtonHeld(int _deviceNumber, int _controllerCode) const = 0;

		//!Checks if the ControllerCode on entered device was released this frame
		/*!
		\param _deviceNumber The Controller id to check
		\param _controllerCode The controller button to check
		*/
		virtual bool ContButtonUp(int _deviceNumber, int _controllerCode) const = 0;

		//!Checks if the ControllerCode on entered device was released last frame
		/*!
		\param _deviceNumber The Controller id to check
		\param _controllerCode The controller button to check
		*/
		virtual bool ContButtonDown(int _deviceNumber, int _controllerCode) const = 0;

		//!Returns the value of one of the axes on a controllers analogue sticks.
		/*!
		\param _deviceNumber The Controller id to check
		\param _analogueNumber The analogue stick to check (0,1);
		\param _axisNumber The axis to check (X=0,Y=1);
		*/
		virtual float GetContAnalogueAxis(int _deviceNumber, int _analogueNumber, int _axisNumber) const = 0;
	};

	std::shared_ptr<Input> CreateInput();

}//namespace GameEngine

#endif
