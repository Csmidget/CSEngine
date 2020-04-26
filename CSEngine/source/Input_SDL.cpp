#include "SDL/SDL.h"

#include "CSEngine_Common.h"

#include "Application.h"
#include "Renderer.h"
#include "KeyCode.h"
#include "KeyCode_SDL.h"
#include "WindowEvent_SDL.h"
#include "Input.h"
#include "Input_SDL.h"

namespace CSEngine
{
	//==============================================================================
	int Input_SDL::UpdateDeltaTime()
	{
		currentTicks = SDL_GetTicks();
		int rdt = (currentTicks - lastTicks);
		float rdts = (float)rdt / 1000.0f;
		lastTicks = currentTicks;

		if (rdt < (1.0f / 60.0f))
		{
			SDL_Delay((unsigned int)(1000 / 60 - rdts));
		}

		return rdt;
	}//Input_SDL::UpdateDeltaTime
	//==============================================================================
	void Input_SDL::RefreshEvents()
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

		SDL_GetMouseState(&mousePosX, &mousePosY);
	}//Input_SDL::RefreshEvents

	//==============================================================================
	void Input_SDL::ProcessEvents()
	{

		SDL_Event event = { 0 };

		RefreshEvents();

		while (SDL_PollEvent(&event))
		{

			switch (event.type)
			{
			case SDL_QUIT:
				Application::Stop();
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				ProcessKeyEvent(event.key);
				break;
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEBUTTONDOWN:
				ProcessMouseButtonEvent(event.button);
				break;
			case SDL_MOUSEWHEEL:
				ProcessMouseWheelEvent(event.wheel);
				break;
			case SDL_MOUSEMOTION:
				ProcessMouseMotionEvent(event.motion);
				break;
			case SDL_CONTROLLERBUTTONUP:
			case SDL_CONTROLLERBUTTONDOWN:
				ProcessControllerButtonEvent(event.cbutton);
				break;
			case SDL_CONTROLLERAXISMOTION:
				ProcessControllerAxisEvent(event.caxis);
				break;
			case SDL_CONTROLLERDEVICEADDED:
				AddController(event.cdevice.which);
				break;
			case SDL_CONTROLLERDEVICEREMOVED:
				RemoveController(event.cdevice.which);
				break;
			case SDL_WINDOWEVENT:
				Application::Renderer().lock()->ProcessWindowEvent(WindowEvent_SDL(event));
				break;
			}
		}
	}//Input_SDL::ProcessEvents
	//==============================================================================
	void Input_SDL::ProcessKeyEvent(SDL_KeyboardEvent &_event)
	{
		const Uint32 sdlKeycode = _event.keysym.sym;
		Uint32 keycode = sdlKeyCodes.at(sdlKeycode);

		if (keycode == KeyCode::ESCAPE)
		{
			Application::Stop();
		}

		bool keyFound = false;
		switch (_event.type)
		{
		case SDL_KEYDOWN:

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

		case SDL_KEYUP:
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
	}//Input_SDL::ProcessKeyEvent
	//==============================================================================
	void Input_SDL::ProcessMouseButtonEvent(SDL_MouseButtonEvent &_event)
	{
		const Uint32 sdlMousecode = _event.button;
		Uint32 mouseCode = sdlMouseCodes.at(sdlMousecode);

		bool buttonFound = false;

		switch (_event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			for (int i = heldMouseButtons.size() - 1; i >= 0; i--) {
				if (heldMouseButtons[i] == mouseCode)
					buttonFound = true;
			}
			if (!buttonFound) {
				heldMouseButtons.push_back(mouseCode);
				downMouseButtons.push_back(mouseCode);
			}
			break;

		case SDL_MOUSEBUTTONUP:
			for (int i = heldMouseButtons.size() - 1; i >= 0; i--) {
				if (heldMouseButtons[i] == mouseCode) {
					heldMouseButtons.erase(heldMouseButtons.begin() + i);
					break;
				}
			}
			upMouseButtons.push_back(mouseCode);
			break;
		}
	}//Input_SDL::ProcessMouseButtonEvent

	//==============================================================================
	void Input_SDL::ProcessMouseMotionEvent(SDL_MouseMotionEvent &_event)
	{
		mouseMoved = true;
	}//Input_SDL::ProcessMouseMotionEvent
	//==============================================================================
	void Input_SDL::ProcessMouseWheelEvent(SDL_MouseWheelEvent &_event)
	{
		mouseWheel = _event.y;
	}//Input_SDL ProcessMouseWheelEvent
	//==============================================================================
	void Input_SDL::ProcessControllerButtonEvent(SDL_ControllerButtonEvent &_event)
	{
		const Uint32 sdlContCode = _event.button;
		Uint32 contCode = sdlMouseCodes.at(sdlContCode);

		bool buttonFound = false;

		std::shared_ptr<Controller> c = controllers.at(controllerInstances.at(_event.which));
		Debug::Log(_event.which);
		switch (_event.type)
		{
		case SDL_CONTROLLERBUTTONDOWN:
			for (int i = c->heldButtons.size() - 1; i >= 0; i--)
			{
				if (c->heldButtons.at(i) == contCode)
					buttonFound = true;
			}
			if (!buttonFound)
			{
				c->heldButtons.push_back(contCode);
				c->downButtons.push_back(contCode);
			}
			break;

		case SDL_CONTROLLERBUTTONUP:
			for (int i = c->heldButtons.size() - 1; i >= 0; i--)
			{
				if (c->heldButtons[i] == contCode)
				{
					c->heldButtons.erase(c->heldButtons.begin() + i);
					break;
				}
			}
			c->upButtons.push_back(contCode);
			break;
		}
	}//Input_SDL::ProcessJoyButton
	//==============================================================================
	void Input_SDL::ProcessControllerAxisEvent(SDL_ControllerAxisEvent &_event)
	{
		std::shared_ptr<Controller> c = controllers.at(controllerInstances.at(_event.which));

		//_event.
		if (_event.value > 5000 || _event.value < -5000)
		{
			c->analogueAxis[_event.axis] = (_event.value / 32768.0f);
		}
		else
			c->analogueAxis[_event.axis] = 0;

	}//Input_SDL::ProcessControllerAxis
	//==============================================================================

	void Input_SDL::AddController(Uint32 _deviceNumber)
	{
		if (SDL_IsGameController(_deviceNumber))
		{
			std::shared_ptr<Controller> cont = std::make_shared<Controller>();
			cont->controller = (SDL_GameControllerOpen(_deviceNumber));
			cont->name = SDL_GameControllerName(cont->controller);
			controllerInstances.insert(std::pair<int, int>(SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(cont->controller)), _deviceNumber));
			controllers.push_back(cont);
			Debug::Log("JOYSTICK ADDED: ", cont->name.c_str());
		}
	}//Input_SDL::AddController
	//==============================================================================
	void Input_SDL::RemoveController(Uint32 _deviceNumber)
	{
		controllers.erase(controllers.begin() + controllerInstances.at(_deviceNumber));
		controllerInstances.erase(_deviceNumber);

		for (DeviceInstanceMap::const_iterator i = controllerInstances.begin(); i != controllerInstances.end(); ++i)
		{
			if (i->second >= _deviceNumber)
				controllerInstances.at(i->first)--;
		}
	}//Input_SDL::RemoveController
	//==============================================================================

	bool Input_SDL::KeyHeld(Uint32 _keyCode) const
	{
		for (int i = heldKeys.size() - 1; i >= 0; i--)
		{
			if (heldKeys[i] == _keyCode)
			{
				return true;
			}
		}
		return false;
	}//Input_SDL::KeyHeld
	//==============================================================================
	bool Input_SDL::KeyUp(Uint32 _keyCode) const
	{
		for (int i = upKeys.size() - 1; i >= 0; i--)
		{
			if (upKeys[i] == _keyCode)
			{
				return true;
			}
		}
		return false;
	}//Input_SDL::KeyUp
	//==============================================================================
	bool Input_SDL::KeyDown(Uint32 _keyCode) const
	{
		for (int i = downKeys.size() - 1; i >= 0; i--)
		{
			if (downKeys[i] == _keyCode)
			{
				return true;
			}
		}
		return false;
	}//Input_SDL::KeyDown
	//==============================================================================
	void Input_SDL::GetMousePos(int *_x, int *_y) const
	{
		*_x = mousePosX;
		*_y = mousePosY;
	}//Input_SDL::GetMousePos
	//==============================================================================
	bool Input_SDL::MouseButtonHeld(Uint32 _mouseCode) const
	{
		for (int i = heldMouseButtons.size() - 1; i >= 0; i--)
		{
			if (heldMouseButtons[i] == _mouseCode)
			{
				return true;
			}
		}
		return false;
	}//Input_SDL::MouseButtonHeld
	//==============================================================================
	bool Input_SDL::MouseButtonUp(Uint32 _mouseCode) const
	{
		for (int i = upMouseButtons.size() - 1; i >= 0; i--)
		{
			if (upMouseButtons[i] == _mouseCode)
			{
				return true;
			}
		}
		return false;
	}//Input_SDL::MouseButtonUp
	//==============================================================================
	bool Input_SDL::MouseButtonDown(Uint32 _mouseCode) const
	{
		for (int i = downMouseButtons.size() - 1; i >= 0; i--)
		{
			if (downMouseButtons[i] == _mouseCode)
			{
				return true;
			}
		}
		return false;
	}//Input_SDL::MouseButtonDown
	//==============================================================================
	bool Input_SDL::ContButtonHeld(Uint32 _deviceNumber, Uint32 _controllerCode) const
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
	}//Input_SDL::ContButtonHeld
	//==============================================================================
	bool Input_SDL::ContButtonUp(Uint32 _deviceNumber, Uint32 _controllerCode) const
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
	}//Input_SDL::ContButtonUp
	//==============================================================================
	bool Input_SDL::ContButtonDown(Uint32 _deviceNumber, Uint32 _controllerCode) const
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
	}//Input_SDL::ContButtonDown
	//==============================================================================
	float Input_SDL::GetContAnalogueAxis(Uint32 _deviceNumber, Uint32 _analogueNumber, Uint32 _axisNumber) const
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
	}//Input_SDL::GetContAnalogueAxis

}