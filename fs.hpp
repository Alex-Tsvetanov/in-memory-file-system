#pragma once
#include <file/file.hpp>
#include <directory/directory.hpp>
#include <fs_node.hpp>

namespace FS
{
	class FileSystem
	{
		private: directory::Directory* root;
		public: directory::Directory* operator ()()
				{
					return root;
				}
		public: FileSystem ()
				{
					this->root = new directory::Directory ();	
				}
	};
}
