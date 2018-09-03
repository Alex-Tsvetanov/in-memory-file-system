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
}