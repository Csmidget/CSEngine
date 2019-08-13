//Acts as an interface between the engine and the debug outputs. This could be files or just the normal iostreams.
//Defaulted to cout and cerr streams.

#ifndef GAME_ENGINE_DEBUG_H
#define GAME_ENGINE_DEBUG_H

#include <string>
#include <iostream>

//TODO: add optional file output streams to allow propper logging of debug info.

namespace GameEngine
{
	class Debug
	{
	public:

		template<typename Arg, typename... Args>
		inline static void Log(Arg&& _logStr, Args&&... args)
		{
#if _DEBUG
			Write(std::cout, _logStr, args...);
			std::cout << std::endl;
#endif
		}//Debug::Log()

		template<typename Arg, typename... Args>
		inline static void LogError(Arg&& _logStr, Args&&... args)
		{
#if _DEBUG
			Write(std::cerr, _logStr, args...);
			std::cerr << std::endl;
#endif
		}//Debug::LogError()

	private:

		template<typename Arg, typename... Args>
		inline static void Write(std::ostream& os, Arg&& _logStr, Args&&... args)
		{
			os << _logStr;
			Write(os, args...);
		}//Debug::Write(ostream, Arg, Args...)

		template<typename Arg>
		inline static void Write(std::ostream& os, Arg&& _logStr)
		{
			os << _logStr;
		}//Debug::Write(ostream, Arg)

	};
}
#endif