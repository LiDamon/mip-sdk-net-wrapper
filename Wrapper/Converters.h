#pragma once

#include <locale>

using namespace System;
using namespace System::Runtime::InteropServices;

//static const char* net_string_to_char_array(String^ string)
//{
//	const char* str = (const char*)(Marshal::StringToHGlobalAnsi(string)).ToPointer();
//	return str;
//}

static std::string net_string_to_std_string(String^ string)
{
	const char* char_array = (const char*)(Marshal::StringToHGlobalAnsi(string)).ToPointer();
	std::string str = std::string(char_array);
	return str;
}

static String^ std_string_to_net_string(std::string string)
{
	String^ str = gcnew String(string.c_str());
	return str;
}
