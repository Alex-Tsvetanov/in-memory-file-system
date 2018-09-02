#pragma once
#include <string>
#include <vector>
#include <file/encoding.hpp>

namespace file
{
	class Content 
	{
		protected: std::vector <unsigned char> content;
		public: virtual Encoding encoding () const = 0;
		public: std::string to_ascii_string () const
				{
					return std::string (content.begin (), content.end ());
				}
		public: Content* append (unsigned char c)
				{
					content.push_back (c);
					return this;
				}
		public: size_t get_size () const
				{
					return content.size ();
				}
		public: std::vector <unsigned char> get_content () const
				{
					return content;
				}
	};
	class TxtContent : public Content 
	{
		public: Encoding encoding () const
				{
					return Encoding::ascii;
				}
		public: TxtContent ()
				{
					this->content = {};
				}
	};
}
