#ifndef GAME_ENGINE_KEYCODE_H
#define GAME_ENGINE_KEYCODE_H

#include <SDL/SDL.h>

namespace GameEngine {

	//!Defines codes for Controller input
	class ControllerCode
	{
	public:
		static const int CONTA = SDL_CONTROLLER_BUTTON_A;
		static const int CONTB = SDL_CONTROLLER_BUTTON_B;
		static const int CONTX = SDL_CONTROLLER_BUTTON_X;
		static const int CONTY = SDL_CONTROLLER_BUTTON_Y;

		static const int CONTBACK = SDL_CONTROLLER_BUTTON_BACK;
		static const int CONTSTART = SDL_CONTROLLER_BUTTON_START;
		static const int CONTGUIDE = SDL_CONTROLLER_BUTTON_GUIDE;

		static const int CONTDPADUP = SDL_CONTROLLER_BUTTON_DPAD_UP;
		static const int CONTDPADDOWN = SDL_CONTROLLER_BUTTON_DPAD_DOWN;
		static const int CONTDPADLEFT = SDL_CONTROLLER_BUTTON_DPAD_LEFT;
		static const int CONTDPADRIGHT = SDL_CONTROLLER_BUTTON_DPAD_RIGHT;

		static const int CONTLEFTSHOULDER = SDL_CONTROLLER_BUTTON_LEFTSHOULDER;
		static const int CONTRIGHTSHOULDER = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;
		static const int CONTLEFTTRIGGER = SDL_CONTROLLER_AXIS_TRIGGERLEFT;
		static const int CONTRIGHTTRIGGER = SDL_CONTROLLER_AXIS_TRIGGERRIGHT;

		static const int CONTLEFTSTICK = SDL_CONTROLLER_BUTTON_LEFTSTICK;
		static const int CONTRIGHTSTICK = SDL_CONTROLLER_BUTTON_RIGHTSTICK;
	};

	//!Defines codes for Mouse input
	class MouseCode
	{
	public:
		static const int MBLEFT = SDL_BUTTON_LEFT;
		static const int MBMID = SDL_BUTTON_MIDDLE;
		static const int MBRIGHT = SDL_BUTTON_RIGHT;
		static const int MBX1 = SDL_BUTTON_X1;
		static const int MBX2 = SDL_BUTTON_X2;
	};

	//!Defines codes for Keyboard input
	class KeyCode {

	public:
		static const int ESCAPE = SDLK_ESCAPE;
		static const int RETURN = SDLK_RETURN;
		static const int SPACE = SDLK_SPACE;

		static const int UP = SDLK_UP;
		static const int DOWN = SDLK_DOWN;
		static const int LEFT = SDLK_LEFT;
		static const int RIGHT = SDLK_RIGHT;

		static const int KEY0 = SDLK_0;
		static const int KEY1 = SDLK_1;
		static const int KEY2 = SDLK_2;
		static const int KEY3 = SDLK_3;
		static const int KEY4 = SDLK_4;
		static const int KEY5 = SDLK_5;
		static const int KEY6 = SDLK_6;
		static const int KEY7 = SDLK_7;
		static const int KEY8 = SDLK_8;
		static const int KEY9 = SDLK_9;

		static const int NUM0 = SDLK_KP_0;
		static const int NUM00 = SDLK_KP_00;
		static const int NUM000 = SDLK_KP_000;
		static const int NUM1 = SDLK_KP_1;
		static const int NUM2 = SDLK_KP_2;
		static const int NUM3 = SDLK_KP_3;
		static const int NUM4 = SDLK_KP_4;
		static const int NUM5 = SDLK_KP_5;
		static const int NUM6 = SDLK_KP_6;
		static const int NUM7 = SDLK_KP_7;
		static const int NUM8 = SDLK_KP_8;
		static const int NUM9 = SDLK_KP_9;

		static const int A = SDLK_a;
		static const int B = SDLK_b;
		static const int C = SDLK_c;
		static const int D = SDLK_d;
		static const int E = SDLK_e;
		static const int F = SDLK_f;
		static const int G = SDLK_g;
		static const int H = SDLK_h;
		static const int I = SDLK_i;
		static const int J = SDLK_j;
		static const int K = SDLK_k;
		static const int L = SDLK_l;
		static const int M = SDLK_m;
		static const int N = SDLK_n;
		static const int O = SDLK_o;
		static const int P = SDLK_p;
		static const int Q = SDLK_q;
		static const int R = SDLK_r;
		static const int S = SDLK_s;
		static const int T = SDLK_t;
		static const int U = SDLK_u;
		static const int V = SDLK_v;
		static const int W = SDLK_w;
		static const int X = SDLK_x;
		static const int Y = SDLK_y;
		static const int Z = SDLK_z;
	};//KeyCode

}

#endif
