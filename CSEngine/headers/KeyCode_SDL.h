#ifndef GAME_ENGINE_KEYCODE_H
#define GAME_ENGINE_KEYCODE_H

#include <SDL/SDL.h>

namespace CSEngine {

	//!Defines codes for Controller input
	class ControllerCode
	{
	public:
		static const Uint32 CONTA = SDL_CONTROLLER_BUTTON_A;
		static const Uint32 CONTB = SDL_CONTROLLER_BUTTON_B;
		static const Uint32 CONTX = SDL_CONTROLLER_BUTTON_X;
		static const Uint32 CONTY = SDL_CONTROLLER_BUTTON_Y;

		static const Uint32 CONTBACK = SDL_CONTROLLER_BUTTON_BACK;
		static const Uint32 CONTSTART = SDL_CONTROLLER_BUTTON_START;
		static const Uint32 CONTGUIDE = SDL_CONTROLLER_BUTTON_GUIDE;

		static const Uint32 CONTDPADUP = SDL_CONTROLLER_BUTTON_DPAD_UP;
		static const Uint32 CONTDPADDOWN = SDL_CONTROLLER_BUTTON_DPAD_DOWN;
		static const Uint32 CONTDPADLEFT = SDL_CONTROLLER_BUTTON_DPAD_LEFT;
		static const Uint32 CONTDPADRIGHT = SDL_CONTROLLER_BUTTON_DPAD_RIGHT;

		static const Uint32 CONTLEFTSHOULDER = SDL_CONTROLLER_BUTTON_LEFTSHOULDER;
		static const Uint32 CONTRIGHTSHOULDER = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;
		static const Uint32 CONTLEFTTRIGGER = SDL_CONTROLLER_AXIS_TRIGGERLEFT;
		static const Uint32 CONTRIGHTTRIGGER = SDL_CONTROLLER_AXIS_TRIGGERRIGHT;

		static const Uint32 CONTLEFTSTICK = SDL_CONTROLLER_BUTTON_LEFTSTICK;
		static const Uint32 CONTRIGHTSTICK = SDL_CONTROLLER_BUTTON_RIGHTSTICK;
	};

	//!Defines codes for Mouse input
	class MouseCode
	{
	public:
		static const Uint32 MBLEFT = SDL_BUTTON_LEFT;
		static const Uint32 MBMID = SDL_BUTTON_MIDDLE;
		static const Uint32 MBRIGHT = SDL_BUTTON_RIGHT;
		static const Uint32 MBX1 = SDL_BUTTON_X1;
		static const Uint32 MBX2 = SDL_BUTTON_X2;
	};

	//!Defines codes for Keyboard input
	class KeyCode {

	public:
		static const Uint32 ESCAPE = SDLK_ESCAPE;
		static const Uint32 RETURN = SDLK_RETURN;
		static const Uint32 SPACE = SDLK_SPACE;

		static const Uint32 UP = SDLK_UP;
		static const Uint32 DOWN = SDLK_DOWN;
		static const Uint32 LEFT = SDLK_LEFT;
		static const Uint32 RIGHT = SDLK_RIGHT;

		static const Uint32 KEY0 = SDLK_0;
		static const Uint32 KEY1 = SDLK_1;
		static const Uint32 KEY2 = SDLK_2;
		static const Uint32 KEY3 = SDLK_3;
		static const Uint32 KEY4 = SDLK_4;
		static const Uint32 KEY5 = SDLK_5;
		static const Uint32 KEY6 = SDLK_6;
		static const Uint32 KEY7 = SDLK_7;
		static const Uint32 KEY8 = SDLK_8;
		static const Uint32 KEY9 = SDLK_9;

		static const Uint32 NUM0 = SDLK_KP_0;
		static const Uint32 NUM00 = SDLK_KP_00;
		static const Uint32 NUM000 = SDLK_KP_000;
		static const Uint32 NUM1 = SDLK_KP_1;
		static const Uint32 NUM2 = SDLK_KP_2;
		static const Uint32 NUM3 = SDLK_KP_3;
		static const Uint32 NUM4 = SDLK_KP_4;
		static const Uint32 NUM5 = SDLK_KP_5;
		static const Uint32 NUM6 = SDLK_KP_6;
		static const Uint32 NUM7 = SDLK_KP_7;
		static const Uint32 NUM8 = SDLK_KP_8;
		static const Uint32 NUM9 = SDLK_KP_9;

		static const Uint32 A = SDLK_a;
		static const Uint32 B = SDLK_b;
		static const Uint32 C = SDLK_c;
		static const Uint32 D = SDLK_d;
		static const Uint32 E = SDLK_e;
		static const Uint32 F = SDLK_f;
		static const Uint32 G = SDLK_g;
		static const Uint32 H = SDLK_h;
		static const Uint32 I = SDLK_i;
		static const Uint32 J = SDLK_j;
		static const Uint32 K = SDLK_k;
		static const Uint32 L = SDLK_l;
		static const Uint32 M = SDLK_m;
		static const Uint32 N = SDLK_n;
		static const Uint32 O = SDLK_o;
		static const Uint32 P = SDLK_p;
		static const Uint32 Q = SDLK_q;
		static const Uint32 R = SDLK_r;
		static const Uint32 S = SDLK_s;
		static const Uint32 T = SDLK_t;
		static const Uint32 U = SDLK_u;
		static const Uint32 V = SDLK_v;
		static const Uint32 W = SDLK_w;
		static const Uint32 X = SDLK_x;
		static const Uint32 Y = SDLK_y;
		static const Uint32 Z = SDLK_z;
	};//KeyCode

}

#endif
