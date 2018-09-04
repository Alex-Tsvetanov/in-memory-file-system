#pragma once
#include <system_error>

namespace FS
{
	class no_such_file_or_directory : public std::system_error
	{
		public: no_such_file_or_directory (std::string path) : 
										std::system_error(
											std::error_code(2, std::system_category()), 
											path)
		{ }
	};
	class file_exists : public std::system_error
	{
		public: file_exists (std::string path) : 
										std::system_error(
											std::error_code(17, std::system_category()), 
											path)
		{ }
	};
}