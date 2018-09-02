#pragma once
#include <string>

namespace file
{
	class Type 
	{
		public: virtual const std::string extension () = 0;
		public: virtual const std::string name () = 0;
	};
	class TxtType : public Type
	{

		public: const std::string extension ()
				{
					return "txt";
				}
		public: const std::string name ()
				{
					return "Plain Text";
				}
				
	};
}
