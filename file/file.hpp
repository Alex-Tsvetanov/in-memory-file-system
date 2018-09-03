#pragma once
#include <fstream>
#include <file/type.hpp>
#include <file/content.hpp>
#include <fs_node.hpp>
#include <vector>

namespace file
{
	class File : public FS::Node
	{
		protected: file::Content* content;
		protected: file::Type* type;
		public: const file::Type* get_type () const
				{
					return type;
				}
		public: const file::Content* get_content () const
				{
					return const_cast <file::Content*> (this->content);
				}
		public: FS::Size get_size () const
				{
					if (content == nullptr)
						return 0;
					return this->content->get_size ();
				}
		public: const File* as_read_only () const
				{
					return const_cast <File*> (this);
				}
		public: File* write (Content* c, std::ios_base::openmode t = std::ofstream::app)
				{
					//TODO: write in different modes
					for (size_t i = 0 ; i < c->get_size () ; i ++)
						this->content->append (c->get_content ()[i]);
					return this;
				}
		public: bool is_file () const
				{
					return true;
				}
   
		public: File (std::string label) : FS::Node (label)
				{
				}
	};
	class TxtFile : public File
	{
		public: TxtFile (std::string label) : File (label)
				{
					this->content = new TxtContent ();
					this->type = new TxtType ();
				}
	};
}
