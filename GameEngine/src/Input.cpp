#include <Input.h>
#include <iostream>
#include <Application.h>
namespace GameEngine
{

	std::vector<std::shared_ptr<Controller>> Input::controllers;
	DeviceInstanceMap Input::controllerInstances;

	std::vector<int> Input::heldKeys;
	std::vector<int> Input::downKeys;
	std::vector<int> Input::upKeys;
	std::vector<int> Input::heldMouseButtons;
	std::vector<int> Input::downMouseButtons;
	std::vector<int> Input::upMouseButtons;

	bool Input::mouseMoved;
	int  Input::mouseWheel;

	int Input::mousePosX;
	int Input::mousePosY;
	//==============================================================================
	void Input::AddController(int _deviceNumber)
	{
		if (SDL_IsGameController(_deviceNumber))
		{
			std::shared_ptr<Controller> cont = std::make_shared<Controller>();
			cont->controller = (SDL_GameControllerOpen(_deviceNumber));
			cont->name = SDL_GameControllerName(cont->controller);
			controllerInstances.insert(std::pair<int, int>(SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(cont->controller)), _deviceNumber));
			controllers.push_back(cont);
			std::cout << "JOYSTICK ADDED: " << cont->name.c_str() << std::endl;
		}
	}//Input::AddController
	//==============================================================================
	void Input::RemoveController(int _deviceNumber)
	{
		controllers.erase(controllers.begin() + controllerInstances.at(_deviceNumber));
		controllerInstances.erase(_deviceNumber);

		for (DeviceInstanceMap::const_iterator i = controllerInstances.begin(); i != controllerInstances.end(); ++i)
		{
			if (i->second >= _deviceNumber)
				controllerInstances.at(i->first)--;
		}
	}//Input::RemoveController
	//==============================================================================
	void Input::ProcessKeyEvent(SDL_KeyboardEvent &_event)
	{

		if (_event.keysym.sym == KeyCode::ESCAPE)
		{
			Application::Stop();
		}

		bool keyFound = false;
		switch (_event.type)
		{
		case SDL_KEYDOWN:

			for (int i = heldKeys.size() - 1; i >= 0; i--)
			{
				if (heldKeys[i] == _event.keysym.sym)
					keyFound = true;
			}
			if (!keyFound) {
				heldKeys.push_back(_event.keysym.sym);
				downKeys.push_back(_event.keysym.sym);
			}
			break;

		case SDL_KEYUP:
			for (int i = heldKeys.size() - 1; i >= 0; i--)
			{
				if (heldKeys[i] == _event.keysym.sym) {
					heldKeys.erase(heldKeys.begin() + i);
					break;
				}
			}
			upKeys.push_back(_event.keysym.sym);
			break;
		}
	}//Input::ProcessKeyEvent
	//==============================================================================
	void Input::ProcessMouseButtonEvent(SDL_MouseButtonEvent &_event)
	{
		bool buttonFound = false;

		switch (_event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			for (int i = heldMouseButtons.size() - 1; i >= 0; i--) {
				if (heldMouseButtons[i] == _event.button)
					buttonFound = true;
			}
			if (!buttonFound) {
				heldMouseButtons.push_back(_event.button);
				downMouseButtons.push_back(_event.button);
			}
			break;

		case SDL_MOUSEBUTTONUP:
			for (int i = heldMouseButtons.size() - 1; i >= 0; i--) {
				if (heldMouseButtons[i] == _event.button) {
					heldMouseButtons.erase(heldMouseButtons.begin() + i);
					break;
				}
			}
			upMouseButtons.push_back(_event.button);
			break;
		}
	}//Input::ProcessMouseButtonEvent

	//==============================================================================
	void Input::ProcessMouseMotionEvent(SDL_MouseMotionEvent &_event)
	{
		mouseMoved = true;
	}//Input::ProcessMouseMotionEvent
	//==============================================================================
	void Input::ProcessMouseWheelEvent(SDL_MouseWheelEvent &_event)
	{
		mouseWheel = _event.y;
	}//Input ProcessMouseWheelEvent
	//==============================================================================
	void Input::RefreshEvents()
	{
		downKeys.clear();
		upKeys.clear();

		mouseMoved = false;
		downMouseButtons.clear();
		upMouseButtons.clear();
		mouseWheel = 0;

		//used to iterate through map as though it was a list: credit to: https://stackoverflow.com/questions/771453/copy-map-values-to-vector-in-stl
		for (int i = 0; i < controllers.size(); i++)
		{
			controllers.at(i)->downButtons.clear();
			controllers.at(i)->upButtons.clear();
		}

		SDL_GetMouseState(&mousePosX, &mousePosY);
	}//Input::RefreshEvents
	 //==============================================================================
	void Input::ProcessControllerButtonEvent(SDL_ControllerButtonEvent &_event)
	{
		bool buttonFound = false;

		std::shared_ptr<Controller> c = controllers.at(controllerInstances.at(_event.which));

		switch (_event.type)
		{
		case SDL_CONTROLLERBUTTONDOWN:
			std::cout << _event.which << std::endl;

			for (int i = c->heldButtons.size() - 1; i >= 0; i--)
			{
				if (c->heldButtons.at(i) == _event.button)
					buttonFound = true;
			}
			if (!buttonFound)
			{
				c->heldButtons.push_back(_event.button);
				c->downButtons.push_back(_event.button);
			}
			break;

		case SDL_CONTROLLERBUTTONUP:
			std::cout << _event.which << std::endl;
			for (int i = c->heldButtons.size() - 1; i >= 0; i--)
			{
				if (c->heldButtons[i] == _event.button)
				{
					c->heldButtons.erase(c->heldButtons.begin() + i);
					break;
				}
			}
			c->upButtons.push_back(_event.button);
			break;
		}
	}//Input::ProcessJoyButton
	//==============================================================================
	void Input::ProcessControllerAxisEvent(SDL_ControllerAxisEvent &_event)
	{
		std::shared_ptr<Controller> c = controllers.at(controllerInstances.at(_event.which));

		//_event.
		if (_event.value > 5000 || _event.value < -5000)
		{
			c->analogueAxis[_event.axis] = (_event.value / 32768.0f);
		}
		else
			c->analogueAxis[_event.axis] = 0;

	}//Input::ProcessControllerAxis
	//==============================================================================
	bool Input::KeyHeld(int _keyCode) {
		for (int i = heldKeys.size() - 1; i >= 0; i--)
		{
			if (heldKeys[i] == _keyCode)
			{
				return true;
			}
		}
		return false;
	}//Input::KeyHeld
	//==============================================================================
	bool Input::KeyUp(int _keyCode) {
		for (int i = upKeys.size() - 1; i >= 0; i--)
		{
			if (upKeys[i] == _keyCode)
			{
				return true;
			}
		}
		return false;
	}//Input::KeyUp
	//==============================================================================
	bool Input::KeyDown(int _keyCode) {
		for (int i = downKeys.size() - 1; i >= 0; i--)
		{
			if (downKeys[i] == _keyCode)
			{
				return true;
			}
		}
		return false;
	}//Input::KeyDown
	//==============================================================================
	void Input::GetMousePos(int *_x, int *_y) {
		*_x = mousePosX;
		*_y = mousePosY;
	}//Input::GetMousePos
	//==============================================================================
	bool Input::MouseButtonHeld(int _mouseCode)
	{
		for (int i = heldMouseButtons.size() - 1; i >= 0; i--)
		{
			if (heldMouseButtons[i] == _mouseCode)
			{
				return true;
			}
		}
		return false;
	}//Input::MouseButtonHeld
	//==============================================================================
	bool Input::MouseButtonUp(int _mouseCode)
	{
		for (int i = upMouseButtons.size() - 1; i >= 0; i--)
		{
			if (upMouseButtons[i] == _mouseCode)
			{
				return true;
			}
		}
		return false;
	}//Input::MouseButtonUp
	//==============================================================================
	bool Input::MouseButtonDown(int _mouseCode)
	{
		for (int i = downMouseButtons.size() - 1; i >= 0; i--)
		{
			if (downMouseButtons[i] == _mouseCode)
			{
				return true;
			}
		}
		return false;
	}//Input::MouseButtonDown
	//==============================================================================
	bool Input::ContButtonHeld(int _deviceNumber, int _controllerCode)
	{
		if (controllers.size() <= _deviceNumber) return false;

		std::shared_ptr<Controller> c = controllers.at(_deviceNumber);

		for (int i = c->heldButtons.size() - 1; i >= 0; i--)
		{
			if (c->heldButtons[i] == _controllerCode)
			{
				return true;
			}
		}
		return false;
	}//Input::ContButtonHeld
	//==============================================================================
	bool Input::ContButtonUp(int _deviceNumber, int _controllerCode)
	{
		if (controllers.size() <= _deviceNumber) return false;

		std::shared_ptr<Controller> c = controllers.at(_deviceNumber);

		for (int i = c->upButtons.size() - 1; i >= 0; i--)
		{
			if (c->upButtons[i] == _controllerCode)
			{
				return true;
			}
		}
		return false;
	}//Input::ContButtonUp
	//==============================================================================
	bool Input::ContButtonDown(int _deviceNumber, int _controllerCode)
	{
		if (controllers.size() <= _deviceNumber) return false;

		std::shared_ptr<Controller> c = controllers.at(_deviceNumber);

		for (int i = c->downButtons.size() - 1; i >= 0; i--)
		{
			if (c->downButtons[i] == _controllerCode)
			{
				return true;
			}
		}
		return false;
	}//Input::ContButtonDown
	//==============================================================================
	float Input::GetContAnalogueAxis(int _deviceNumber, int _analogueNumber, int _axisNumber)
	{
		if (controllers.size() <= _deviceNumber)
		{
			return 0.0f;
		}

		std::shared_ptr<Controller> c = controllers.at(_deviceNumber);

		if (_analogueNumber * 2 + _axisNumber > SDL_arraysize(c->analogueAxis) || _analogueNumber * 2 + _axisNumber < 0)
		{
			return 0.0f;
		}

		return c->analogueAxis[_analogueNumber * 2 + _axisNumber];
	}


}

