#pragma once
#include <fstream>
#include <fs_node.hpp>

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
					this->children.insert (child);
					return this;
				}
		public: Directory (std::string label = "/") : FS::Node (label)
				{}
	};
}

