#pragma once
#include <file/file.hpp>
#include <exceptions/no_such_file_or_directory.hpp>
#include <directory/directory.hpp>
#include <fs_node.hpp>

#include <iostream>

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
		 public: const FS::Node* get_iterator () const
				 {
					 return (FS::Node*)(this->root);
				 }
		 public: const FS::Node* get_by_full_path (const std::string& path) const
				 {
					 if (path [0] != '/')
					 	throw FS::no_such_file_or_directory (path);
					 return (this->root->find_by_full_path (path));
				 }
		 public: static void printTree (const FS::Node* node, size_t level = 0)
				 {	 
					 for(size_t i = 0 ; i < level ; i ++)
					 {
						 std::cout << "\t";
					 }
					 
					 if (node->is_file ())
					 {
						 std::cout << node->get_path() << " (Size: " << node->get_size ().to_bytes() << " bytes)" << std::endl;
					 }
					 else
					 {
						 std::cout << node->get_path() << "/ (Total: " << node->get_size ().to_bytes() << " bytes)" << std::endl;
					 }
					 for (auto& x : node->get_children ())
					 	printTree (x, level + 1); 
				 }
	};
}
