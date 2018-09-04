#pragma once
#include <string>

namespace file
{
	class Type 
	{
		public: virtual const std::string extension () const = 0;
		public: virtual const std::string name () const = 0;
	};
	class TxtType : public Type
	{
		public: const std::string extension () const
				{
					return "txt";
				}
		public: const std::string name () const
				{
					return "Plain Text";
				}
	};
}
