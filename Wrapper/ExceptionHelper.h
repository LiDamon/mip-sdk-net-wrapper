#pragma once

#include <exception>

#include "Converters.h"

namespace CLI
{
	class ExceptionHelper
	{
	public:
		static System::String^ GetExceptionMessage(std::exception_ptr e)
		{
			System::String^ msg = nullptr;

			try { std::rethrow_exception(e); }
			catch (const std::exception &e)
			{
				msg = std_string_to_net_string(e.what());
			}

			return msg;
		}
	};
}