#pragma once
#include <fstream>
#include <fs_node.hpp>
#include <exception>

namespace directory
{
	class Directory : public FS::Node
	{
		public: FS::Size get_size () const
				{
					FS::Size ans (0);
					for (const auto& x : children)
						ans = ans + x->get_size ();
					return ans;
				}
		public: bool is_file () const
				{
					return false;
				}

		public: Directory* create_child (Node* child)
				{
					child->parent = this;
					auto x = this->children.insert (child);
					if (x.second == false)
						throw FS::file_exists (this->get_path());
					return this;
				}

		public: Node* get_child_by_name (const std::string& name)
				{
					auto it = this->children.find (new FS::Find_node_pattern (name));
					if (it == this->children.end ())
					 	throw FS::no_such_file_or_directory (this->get_path ()+ "/" + name);
					return *it;
				}
		public: Directory (std::string label = "") : FS::Node (label)
				{}
	};
}

