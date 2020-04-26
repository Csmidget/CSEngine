#ifndef GAME_ENGINE_KEYCODE_SDL_H
#define GAME_ENGINE_KEYCODE_SDL_H

//This file provides conversions from SDL input codes to Engine input codes.

namespace CSEngine {

	const std::map<Uint32, Uint32> sdlControllerCodes
	{
		{SDL_CONTROLLER_BUTTON_A,ControllerCode::CONTA},
		{SDL_CONTROLLER_BUTTON_B,ControllerCode::CONTB},
		{SDL_CONTROLLER_BUTTON_X,ControllerCode::CONTX},
		{SDL_CONTROLLER_BUTTON_Y,ControllerCode::CONTY},
		{SDL_CONTROLLER_BUTTON_BACK,ControllerCode::CONTBACK},
		{SDL_CONTROLLER_BUTTON_START,ControllerCode::CONTSTART},
		{SDL_CONTROLLER_BUTTON_GUIDE,ControllerCode::CONTGUIDE},
		{SDL_CONTROLLER_BUTTON_DPAD_UP,ControllerCode::CONTDPADUP},
		{SDL_CONTROLLER_BUTTON_DPAD_DOWN,ControllerCode::CONTDPADDOWN},
		{SDL_CONTROLLER_BUTTON_DPAD_LEFT,ControllerCode::CONTDPADLEFT},
		{SDL_CONTROLLER_BUTTON_DPAD_RIGHT,ControllerCode::CONTDPADRIGHT},
		{SDL_CONTROLLER_BUTTON_LEFTSHOULDER,ControllerCode::CONTLEFTSHOULDER},
		{SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,ControllerCode::CONTRIGHTSHOULDER},
		{SDL_CONTROLLER_AXIS_TRIGGERLEFT,ControllerCode::CONTA},
		{SDL_CONTROLLER_AXIS_TRIGGERRIGHT,ControllerCode::CONTA},
		{SDL_CONTROLLER_BUTTON_LEFTSTICK,ControllerCode::CONTA},
		{SDL_CONTROLLER_BUTTON_RIGHTSTICK,ControllerCode::CONTA},
		{SDL_CONTROLLER_BUTTON_A,ControllerCode::CONTA},
		{SDL_CONTROLLER_BUTTON_A,ControllerCode::CONTA},
		{SDL_CONTROLLER_BUTTON_A,ControllerCode::CONTA}
	};


	const std::map<Uint32, Uint32> sdlMouseCodes
	{
		{SDL_BUTTON_LEFT,MouseCode::MBLEFT},
		{SDL_BUTTON_MIDDLE,MouseCode::MBMID},
		{SDL_BUTTON_RIGHT,MouseCode::MBRIGHT},
		{SDL_BUTTON_X1,MouseCode::MBX1},
		{SDL_BUTTON_X2,MouseCode::MBX2}
	};

	const std::map<Uint32, Uint32> sdlKeyCodes
	{
		{SDLK_0,KeyCode::KEY0},
		{SDLK_1,KeyCode::KEY1},
		{SDLK_2,KeyCode::KEY2},
		{SDLK_3,KeyCode::KEY3},
		{SDLK_4,KeyCode::KEY4},
		{SDLK_5,KeyCode::KEY5},
		{SDLK_6,KeyCode::KEY6},
		{SDLK_7,KeyCode::KEY7},
		{SDLK_8,KeyCode::KEY8},
		{SDLK_9,KeyCode::KEY9},
		{SDLK_a,KeyCode::A},
		{SDLK_b,KeyCode::B},
		{SDLK_c,KeyCode::C},
		{SDLK_d,KeyCode::D},
		{SDLK_e,KeyCode::E},
		{SDLK_f,KeyCode::F},
		{SDLK_g,KeyCode::G},
		{SDLK_h,KeyCode::H},
		{SDLK_i,KeyCode::I},
		{SDLK_j,KeyCode::J},
		{SDLK_k,KeyCode::K},
		{SDLK_l,KeyCode::L},
		{SDLK_m,KeyCode::M},
		{SDLK_n,KeyCode::N},
		{SDLK_o,KeyCode::O},
		{SDLK_p,KeyCode::P},
		{SDLK_q,KeyCode::Q},
		{SDLK_r,KeyCode::R},
		{SDLK_s,KeyCode::S},
		{SDLK_t,KeyCode::T},
		{SDLK_u,KeyCode::U},
		{SDLK_v,KeyCode::V},
		{SDLK_w,KeyCode::W},
		{SDLK_x,KeyCode::X},
		{SDLK_y,KeyCode::Y},
		{SDLK_z,KeyCode::Z},
		{SDLK_UP,KeyCode::UP},
		{SDLK_DOWN,KeyCode::DOWN},
		{SDLK_LEFT,KeyCode::LEFT},
		{SDLK_RIGHT,KeyCode::RIGHT},
		{SDLK_ESCAPE,KeyCode::ESCAPE},
		{SDLK_RETURN,KeyCode::RETURN},
		{SDLK_SPACE,KeyCode::SPACE},
		{SDLK_KP_0,KeyCode::NUM0},
		{SDLK_KP_00,KeyCode::NUM00},
		{SDLK_KP_000,KeyCode::NUM000},
		{SDLK_KP_1,KeyCode::NUM1},
		{SDLK_KP_2,KeyCode::NUM2},
		{SDLK_KP_3,KeyCode::NUM3},
		{SDLK_KP_4,KeyCode::NUM4},
		{SDLK_KP_5,KeyCode::NUM5},
		{SDLK_KP_6,KeyCode::NUM6},
		{SDLK_KP_7,KeyCode::NUM7},
		{SDLK_KP_8,KeyCode::NUM8},
		{SDLK_KP_9,KeyCode::NUM9}
	};
}

#endif
