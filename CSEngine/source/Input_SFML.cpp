#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "CSEngine_Common.h"

#include "Application.h"
#include "Renderer.h"
#include "Renderer_SFML.h"
#include "KeyCode.h"
#include "KeyCode_SFML.h"
//#include "WindowEvent_SDL.h"
#include "Input.h"
#include "Input_SFML.h"

namespace CSEngine
{
	//==============================================================================
	int Input_SFML::UpdateDeltaTime()
	{
		int rdt = deltaClock.restart().asMilliseconds();

		return rdt;
	}//Input_SFML::UpdateDeltaTime
	//==============================================================================
	Input_SFML::Input_SFML()
	{
		//Gets a weak pointer to the renderer, casted into an SFML renderer for SFML specific functionality.
		renderer = std::dynamic_pointer_cast<Renderer_SFML>(Application::Renderer().lock());	
		deltaClock.restart();
	}//Input_SFML
	//==============================================================================
	void Input_SFML::RefreshEvents()
	{
		downKeys.clear();
		upKeys.clear();

		mouseMoved = false;
		downMouseButtons.clear();
		upMouseButtons.clear();
		mouseWheel = 0;

		//used to iterate through map as though it was a list: credit to: https://stackoverflow.com/questions/771453/copy-map-values-to-vector-in-stl
		for (size_t i = 0; i < controllers.size(); i++)
		{
			controllers.at(i)->downButtons.clear();
			controllers.at(i)->upButtons.clear();
		}

		sf::Vector2i mousePos = sf::Mouse::getPosition((renderer.lock()->mainWindow));

		mousePosX = mousePos.x;
		mousePosY = mousePos.y;

	}//Input_SFML::RefreshEvents

	//==============================================================================
	void Input_SFML::ProcessEvents()
	{

		sf::Event sfEvent;

		RefreshEvents();

		std::shared_ptr<Renderer_SFML> r = renderer.lock();

		while (r->mainWindow.pollEvent(sfEvent))
		{
			switch (sfEvent.type)
			{
			case sf::Event::Closed:
				Application::Stop();
				break;
			case sf::Event::KeyPressed:
			case sf::Event::KeyReleased:
				ProcessKeyEvent(sfEvent);
			case sf::Event::MouseButtonPressed:
			case sf::Event::MouseButtonReleased:
				ProcessMouseButtonEvent(sfEvent);
				break;
			case sf::Event::MouseWheelScrolled:
				ProcessMouseWheelEvent(sfEvent);
			case sf::Event::MouseMoved:
				ProcessMouseMotionEvent(sfEvent);
			case sf::Event::JoystickButtonPressed:
			case sf::Event::JoystickButtonReleased:
				ProcessControllerButtonEvent(sfEvent);
				break;
			case sf::Event::JoystickMoved:
				ProcessControllerAxisEvent(sfEvent);
				break;
			case sf::Event::JoystickConnected:
				AddController(sfEvent);
				break;
			case sf::Event::JoystickDisconnected:
				RemoveController(sfEvent);
				break;
			case sf::Event::Resized:
			case sf::Event::GainedFocus:
				//Application::Renderer().lock()->ProcessWindowEvent(WindowEvent_SDL(event));
				break;
			}

		}
	}//Input_SFML::ProcessEvents
	//==============================================================================
	void Input_SFML::ProcessKeyEvent(sf::Event& _event)
	{
		const uint32_t sfmlKeycode = _event.key.code;
		uint32_t keycode = sfmlKeyCodes.at(sfmlKeycode);

		if (keycode == KeyCode::ESCAPE)
		{
			Application::Stop();
		}

		bool keyFound = false;
		switch (_event.type)
		{
		case sf::Event::KeyPressed:

			for (int i = heldKeys.size() - 1; i >= 0; i--)
			{
				if (heldKeys[i] == keycode)
					keyFound = true;
			}
			if (!keyFound) {
				heldKeys.push_back(keycode);
				downKeys.push_back(keycode);
			}
			break;

		case sf::Event::KeyReleased:
			for (int i = heldKeys.size() - 1; i >= 0; i--)
			{
				if (heldKeys[i] == keycode) {
					heldKeys.erase(heldKeys.begin() + i);
					break;
				}
			}
			upKeys.push_back(keycode);
			break;
		}
	}//Input_SFML::ProcessKeyEvent
	//==============================================================================
	void Input_SFML::ProcessMouseButtonEvent(sf::Event& _event)
	{
		const uint32_t sfmlMousecode = _event.mouseButton.button;
		uint32_t keycode = sfmlMouseCodes.at(sfmlMousecode);

		bool buttonFound = false;

		switch (_event.type)
		{
		case sf::Event::MouseButtonPressed:
			for (int i = heldMouseButtons.size() - 1; i >= 0; i--) {
				if (heldMouseButtons[i] == keycode)
					buttonFound = true;
			}
			if (!buttonFound) {
				heldMouseButtons.push_back(keycode);
				downMouseButtons.push_back(keycode);
			}
			break;

		case sf::Event::MouseButtonReleased:
			for (int i = heldMouseButtons.size() - 1; i >= 0; i--) {
				if (heldMouseButtons[i] == keycode) {
					heldMouseButtons.erase(heldMouseButtons.begin() + i);
					break;
				}
			}
			upMouseButtons.push_back(keycode);
			break;
		}
	}//Input_SFML::ProcessMouseButtonEvent

	//==============================================================================
	void Input_SFML::ProcessMouseMotionEvent(sf::Event& _event)
	{
		mouseMoved = true;
	}//Input_SFML::ProcessMouseMotionEvent
	//==============================================================================
	void Input_SFML::ProcessMouseWheelEvent(sf::Event& _event)
	{
		mouseWheel = _event.mouseWheel.delta;
	}//Input_SFML::ProcessMouseWheelEvent
	//==============================================================================
	void Input_SFML::ProcessControllerButtonEvent(sf::Event& _event)
	{
		//NYI: NOT YET IMPLEMENTED

		//bool buttonFound = false;
		//
		//std::shared_ptr<Controller> c = controllers.at(controllerInstances.at(_event.which));
		//
		//switch (_event.type)
		//{
		//case SDL_CONTROLLERBUTTONDOWN:
		//	Debug::Log(_event.which);
		//
		//	for (int i = c->heldButtons.size() - 1; i >= 0; i--)
		//	{
		//		if (c->heldButtons.at(i) == _event.button)
		//			buttonFound = true;
		//	}
		//	if (!buttonFound)
		//	{
		//		c->heldButtons.push_back(_event.button);
		//		c->downButtons.push_back(_event.button);
		//	}
		//	break;
		//
		//case SDL_CONTROLLERBUTTONUP:
		//	Debug::Log(_event.which);
		//	for (int i = c->heldButtons.size() - 1; i >= 0; i--)
		//	{
		//		if (c->heldButtons[i] == _event.button)
		//		{
		//			c->heldButtons.erase(c->heldButtons.begin() + i);
		//			break;
		//		}
		//	}
		//	c->upButtons.push_back(_event.button);
		//	break;
		//}
	}//Input_SFML::ProcessJoyButton
	//==============================================================================
	void Input_SFML::ProcessControllerAxisEvent(sf::Event& _event)
	{
		//NYI: NOT YET IMPLEMENTED

		//std::shared_ptr<Controller> c = controllers.at(controllerInstances.at(_event.which));
		//
		////_event.
		//if (_event.value > 5000 || _event.value < -5000)
		//{
		//	c->analogueAxis[_event.axis] = (_event.value / 32768.0f);
		//}
		//else
		//	c->analogueAxis[_event.axis] = 0;
		//
	}//Input_SFML::ProcessControllerAxis
	//==============================================================================

	void Input_SFML::AddController(sf::Event& _event)
	{
		//NYI: NOT YET IMPLEMENTED

		//if (SDL_IsGameController(_deviceNumber))
		//{
		//	std::shared_ptr<Controller> cont = std::make_shared<Controller>();
		//	cont->controller = (SDL_GameControllerOpen(_deviceNumber));
		//	cont->name = SDL_GameControllerName(cont->controller);
		//	controllerInstances.insert(std::pair<int, int>(SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(cont->controller)), _deviceNumber));
		//	controllers.push_back(cont);
		//	Debug::Log("JOYSTICK ADDED: ", cont->name.c_str());
		//}
	}//Input_SFML::AddController
	//==============================================================================
	void Input_SFML::RemoveController(sf::Event& _event)
	{
		//NYI:: NOT YET IMPLEMENTED
		//controllers.erase(controllers.begin() + controllerInstances.at(_deviceNumber));
		//controllerInstances.erase(_deviceNumber);
		//
		//for (DeviceInstanceMap::const_iterator i = controllerInstances.begin(); i != controllerInstances.end(); ++i)
		//{
		//	if (i->second >= _deviceNumber)
		//		controllerInstances.at(i->first)--;
		//}
	}//Input_SFML::RemoveController
	//==============================================================================

	bool Input_SFML::KeyHeld(uint32_t _keyCode) const
	{
		for (int i = heldKeys.size() - 1; i >= 0; i--)
		{
			if (heldKeys[i] == _keyCode)
			{
				return true;
			}
		}
		return false;
	}//Input_SFML::KeyHeld
	//==============================================================================
	bool Input_SFML::KeyUp(uint32_t _keyCode) const
	{
		for (int i = upKeys.size() - 1; i >= 0; i--)
		{
			if (upKeys[i] == _keyCode)
			{
				return true;
			}
		}
		return false;
	}//Input_SFML::KeyUp
	//==============================================================================
	bool Input_SFML::KeyDown(uint32_t _keyCode) const
	{
		for (int i = downKeys.size() - 1; i >= 0; i--)
		{
			if (downKeys[i] == _keyCode)
			{
				return true;
			}
		}
		return false;
	}//Input_SFML::KeyDown
	//==============================================================================
	void Input_SFML::GetMousePos(int* _x, int* _y) const
	{
		*_x = mousePosX;
		*_y = mousePosY;
	}//Input_SFML::GetMousePos
	//==============================================================================
	bool Input_SFML::MouseButtonHeld(uint32_t _mouseCode) const
	{
		for (int i = heldMouseButtons.size() - 1; i >= 0; i--)
		{
			if (heldMouseButtons[i] == _mouseCode)
			{
				return true;
			}
		}
		return false;
	}//Input_SFML::MouseButtonHeld
	//==============================================================================
	bool Input_SFML::MouseButtonUp(uint32_t _mouseCode) const
	{
		for (int i = upMouseButtons.size() - 1; i >= 0; i--)
		{
			if (upMouseButtons[i] == _mouseCode)
			{
				return true;
			}
		}
		return false;
	}//Input_SFML::MouseButtonUp
	//==============================================================================
	bool Input_SFML::MouseButtonDown(uint32_t _mouseCode) const
	{
		for (int i = downMouseButtons.size() - 1; i >= 0; i--)
		{
			if (downMouseButtons[i] == _mouseCode)
			{
				return true;
			}
		}
		return false;
	}//Input_SFML::MouseButtonDown
	//==============================================================================
	bool Input_SFML::ContButtonHeld(uint32_t _deviceNumber, uint32_t _controllerCode) const
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
	}//Input_SFML::ContButtonHeld
	//==============================================================================
	bool Input_SFML::ContButtonUp(uint32_t _deviceNumber, uint32_t _controllerCode) const
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
	}//Input_SFML::ContButtonUp
	//==============================================================================
	bool Input_SFML::ContButtonDown(uint32_t _deviceNumber, uint32_t _controllerCode) const
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
	}//Input_SFML::ContButtonDown
	//==============================================================================
	float Input_SFML::GetContAnalogueAxis(uint32_t _deviceNumber, uint32_t _analogueNumber, uint32_t _axisNumber) const
	{
		//NYI: NOT YET IMPLEMENTED
		//if (controllers.size() <= _deviceNumber)
		//{
		//	return 0.0f;
		//}
		//
		//std::shared_ptr<Controller> c = controllers.at(_deviceNumber);
		//
		//if (_analogueNumber * 2 + _axisNumber > SDL_arraysize(c->analogueAxis) || _analogueNumber * 2 + _axisNumber < 0)
		//{
		//	return 0.0f;
		//}
		//
		//return c->analogueAxis[_analogueNumber * 2 + _axisNumber];
		return 0;
	}//Input_SFML::GetContAnalogueAxis

}