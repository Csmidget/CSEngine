#ifndef GAME_ENGINE_INPUT_SFML_H
#define GAME_ENGINE_INPUT_SFML_H

namespace CSEngine {

	class Input_SFML : public Input
	{
		//!Stores information on individual controller
		struct Controller
		{
			//!The name of this controller (Normally "xinput Controller")
			std::string name;
			//!Buttons currently being held down
			std::vector<uint32_t> heldButtons;
			//!Buttons that have just been pressed
			std::vector<uint32_t> downButtons;
			//!Buttons that have been released this frame
			std::vector<uint32_t>   upButtons;
			//!Information on controller analogue sticks Left stick:[0],[1]|Right stick:[1],[2] 
			float analogueAxis[6] = { 0,0,0,0,0,0 };
		};
		//! Used for connecting instance id to device id.
		typedef std::map<uint32_t, uint32_t> DeviceInstanceMap;

	public:
		Input_SFML();

	private:

		sf::Clock deltaClock;

		std::weak_ptr<Renderer_SFML> renderer;

		//!Map from Controller instance to deviceNumber in controller list.
		DeviceInstanceMap controllerInstances;
		//!List of active controllers
		std::vector<std::shared_ptr<Controller>> controllers;

		//!Keys currently being held down
		std::vector<uint32_t> heldKeys;
		//!Keys that have just been pressed
		std::vector<uint32_t> downKeys;
		//!Keys that have been released this frame
		std::vector<uint32_t> upKeys;

		//!Mouse buttons currently being held down
		std::vector<uint32_t> heldMouseButtons;
		//!Mouse buttons that have just been pressed
		std::vector<uint32_t> downMouseButtons;
		//!Mouse buttons that have been released this frame
		std::vector<uint32_t> upMouseButtons;

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

		void ProcessKeyEvent(sf::Event& _event);
		void ProcessMouseButtonEvent(sf::Event& _event);
		void ProcessMouseMotionEvent(sf::Event& _event);
		void ProcessMouseWheelEvent(sf::Event& _event);
		void ProcessControllerButtonEvent(sf::Event& _event);
		void ProcessControllerAxisEvent(sf::Event& _event);

		//!Adds a controller to the list of active controllers. Called if new controller is detected.
		void AddController(sf::Event& _event);
		//!Removes a controller from the list of active controllers. Called if a Controller is unplugged.
		void RemoveController(sf::Event& _event);

		int UpdateDeltaTime() override;

	public:
		int NumControllers() const override { return controllers.size(); };

		bool KeyHeld(uint32_t _keyCode) const override;

		bool KeyDown(uint32_t _keyCode) const override;

		bool KeyUp(uint32_t _keyCode) const override;

		bool MouseButtonHeld(uint32_t _mouseCode) const override;

		bool MouseButtonUp(uint32_t _mouseCode) const override;

		bool MouseButtonDown(uint32_t _mouseCode) const override;

		void GetMousePos(int* _x, int* _y) const override;

		bool ContButtonHeld(uint32_t _deviceNumber, uint32_t _controllerCode) const override;

		bool ContButtonUp(uint32_t _deviceNumber, uint32_t _controllerCode) const override;

		bool ContButtonDown(uint32_t _deviceNumber, uint32_t _controllerCode) const override;

		float GetContAnalogueAxis(uint32_t _deviceNumber, uint32_t _analogueNumber, uint32_t _axisNumber) const override;

	};
}




#endif