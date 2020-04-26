#ifndef GAME_ENGINE_KEYCODE_SFML_H
#define GAME_ENGINE_KEYCODE_SFML_H

//This file provides conversions from SDL input codes to Engine input codes.

namespace CSEngine {

	//NYI: NOT YET IMPLEMTENTED
	const std::map<uint32_t, uint32_t> sfmlControllerCodes
	{
		{UINT32_MAX,ControllerCode::CONTA},
		{UINT32_MAX,ControllerCode::CONTB},
		{UINT32_MAX,ControllerCode::CONTX},
		{UINT32_MAX,ControllerCode::CONTY},
		{UINT32_MAX,ControllerCode::CONTBACK},
		{UINT32_MAX,ControllerCode::CONTSTART},
		{UINT32_MAX,ControllerCode::CONTGUIDE},
		{UINT32_MAX,ControllerCode::CONTDPADUP},
		{UINT32_MAX,ControllerCode::CONTDPADDOWN},
		{UINT32_MAX,ControllerCode::CONTDPADLEFT},
		{UINT32_MAX,ControllerCode::CONTDPADRIGHT},
		{UINT32_MAX,ControllerCode::CONTLEFTSHOULDER},
		{UINT32_MAX,ControllerCode::CONTRIGHTSHOULDER},
		{UINT32_MAX,ControllerCode::CONTA},
		{UINT32_MAX,ControllerCode::CONTA},
		{UINT32_MAX,ControllerCode::CONTA},
		{UINT32_MAX,ControllerCode::CONTA},
		{UINT32_MAX,ControllerCode::CONTA},
		{UINT32_MAX,ControllerCode::CONTA},
		{UINT32_MAX,ControllerCode::CONTA}
	};


	const std::map<uint32_t, uint32_t> sfmlMouseCodes
	{
		{sf::Mouse::Left,MouseCode::MBLEFT},
		{sf::Mouse::Middle,MouseCode::MBMID},
		{sf::Mouse::Right,MouseCode::MBRIGHT},
		{sf::Mouse::XButton1,MouseCode::MBX1},
		{sf::Mouse::XButton2,MouseCode::MBX2}
	};

	const std::map<uint32_t, uint32_t> sfmlKeyCodes
	{
		{sf::Keyboard::Num0,KeyCode::KEY0},
		{sf::Keyboard::Num1,KeyCode::KEY1},
		{sf::Keyboard::Num2,KeyCode::KEY2},
		{sf::Keyboard::Num3,KeyCode::KEY3},
		{sf::Keyboard::Num4,KeyCode::KEY4},
		{sf::Keyboard::Num5,KeyCode::KEY5},
		{sf::Keyboard::Num6,KeyCode::KEY6},
		{sf::Keyboard::Num7,KeyCode::KEY7},
		{sf::Keyboard::Num8,KeyCode::KEY8},
		{sf::Keyboard::Num9,KeyCode::KEY9},
		{sf::Keyboard::A,KeyCode::A},
		{sf::Keyboard::B,KeyCode::B},
		{sf::Keyboard::C,KeyCode::C},
		{sf::Keyboard::D,KeyCode::D},
		{sf::Keyboard::E,KeyCode::E},
		{sf::Keyboard::F,KeyCode::F},
		{sf::Keyboard::G,KeyCode::G},
		{sf::Keyboard::H,KeyCode::H},
		{sf::Keyboard::I,KeyCode::I},
		{sf::Keyboard::J,KeyCode::J},
		{sf::Keyboard::K,KeyCode::K},
		{sf::Keyboard::L,KeyCode::L},
		{sf::Keyboard::M,KeyCode::M},
		{sf::Keyboard::N,KeyCode::N},
		{sf::Keyboard::O,KeyCode::O},
		{sf::Keyboard::P,KeyCode::P},
		{sf::Keyboard::Q,KeyCode::Q},
		{sf::Keyboard::R,KeyCode::R},
		{sf::Keyboard::S,KeyCode::S},
		{sf::Keyboard::T,KeyCode::T},
		{sf::Keyboard::U,KeyCode::U},
		{sf::Keyboard::V,KeyCode::V},
		{sf::Keyboard::W,KeyCode::W},
		{sf::Keyboard::X,KeyCode::X},
		{sf::Keyboard::Y,KeyCode::Y},
		{sf::Keyboard::Z,KeyCode::Z},
		{sf::Keyboard::Up,KeyCode::UP},
		{sf::Keyboard::Down,KeyCode::DOWN},
		{sf::Keyboard::Left,KeyCode::LEFT},
		{sf::Keyboard::Right,KeyCode::RIGHT},
		{sf::Keyboard::Escape,KeyCode::ESCAPE},
		{sf::Keyboard::Return,KeyCode::RETURN},
		{sf::Keyboard::Space,KeyCode::SPACE},
		{sf::Keyboard::Numpad0,KeyCode::NUM0},
		{UINT32_MAX,KeyCode::NUM00},
		{UINT32_MAX,KeyCode::NUM000},
		{sf::Keyboard::Numpad1,KeyCode::NUM1},
		{sf::Keyboard::Numpad2,KeyCode::NUM2},
		{sf::Keyboard::Numpad3,KeyCode::NUM3},
		{sf::Keyboard::Numpad4,KeyCode::NUM4},
		{sf::Keyboard::Numpad5,KeyCode::NUM5},
		{sf::Keyboard::Numpad6,KeyCode::NUM6},
		{sf::Keyboard::Numpad7,KeyCode::NUM7},
		{sf::Keyboard::Numpad8,KeyCode::NUM8},
		{sf::Keyboard::Numpad9,KeyCode::NUM9}
	};
}

#endif
