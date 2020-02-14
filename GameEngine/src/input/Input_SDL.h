#ifndef GAME_ENGINE_INPUT_SDL_H
#define GAME_ENGINE_INPUT_SDL_H

namespace GameEngine {

	class Input_SDL : public Input 
	{
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


	private:

		//!Map from Controller instance to deviceNumber in controller list.
		DeviceInstanceMap controllerInstances;
		//!List of active controllers
		std::vector<std::shared_ptr<Controller>> controllers;

		//!Keys currently being held down
		std::vector<int> heldKeys;
		//!Keys that have just been pressed
		std::vector<int> downKeys;
		//!Keys that have been released this frame
		std::vector<int> upKeys;

		//!Mouse buttons currently being held down
		std::vector<int> heldMouseButtons;
		//!Mouse buttons that have just been pressed
		std::vector<int> downMouseButtons;
		//!Mouse buttons that have been released this frame
		std::vector<int> upMouseButtons;

		//!The X position of the mouse within the window (Left = 0)
		int mousePosX;
		//!The Y position of the mouse within the window (Top = 0)
		int mousePosY;
		//!The mouse wheel change this frame. 1 = scroll up| -1 = scroll down
		int mouseWheel;
		//!True if the mouse has moved since the last frame
		bool mouseMoved;

		void ProcessEvents() override;
		//!Runs at the start of every frame to refresh vectors etc ready for new information.
		void RefreshEvents();

		void ProcessKeyEvent(SDL_KeyboardEvent &_event);
		void ProcessMouseButtonEvent(SDL_MouseButtonEvent &_event);
		void ProcessMouseMotionEvent(SDL_MouseMotionEvent &_event);
		void ProcessMouseWheelEvent(SDL_MouseWheelEvent &_event);
		void ProcessControllerButtonEvent(SDL_ControllerButtonEvent &_event);
		void ProcessControllerAxisEvent(SDL_ControllerAxisEvent &_event);

		//!Adds a controller to the list of active controllers. Called if new controller is detected.
		void AddController(int _deviceNumber);
		//!Removes a controller from the list of active controllers. Called if a Controller is unplugged.
		void RemoveController(int _deviceNumber);

	public:
		int NumControllers() const override { return controllers.size(); } ;

		bool KeyHeld(int _keyCode) const override;

		bool KeyDown(int _keyCode) const override;

		bool KeyUp(int _keyCode) const override;

		bool MouseButtonHeld(int _mouseCode) const override;

		bool MouseButtonUp(int _mouseCode) const override;

		bool MouseButtonDown(int _mouseCode) const override;

		void GetMousePos(int *_x, int *_y) const override;

		bool ContButtonHeld(int _deviceNumber, int _controllerCode) const override;

		bool ContButtonUp(int _deviceNumber, int _controllerCode) const override;

		bool ContButtonDown(int _deviceNumber, int _controllerCode) const override;

		float GetContAnalogueAxis(int _deviceNumber, int _analogueNumber, int _axisNumber) const override;

	};
}




#endif