#pragma once
#include <string>
#include <set>
#include <functional>
#include <exceptions/no_such_file_or_directory.hpp>
#include <iostream>

namespace directory
{
	class Directory;
}

namespace FS
{
	class Size
	{
		private: std::size_t bytes;
		public: Size (std::size_t s = 0) : bytes (s)
				{}
		public: std::size_t   operator + (const Size& a) const { return bytes + a.bytes; }
		public: std::size_t to_bytes () { return bytes / 1.0; }
		public:      double to_kilobytes () { return bytes / 1000.0; }
		public:      double to_megabytes () { return bytes / 1000000.0; }
		public:      double to_terabytes () { return bytes / 1000000000.0; }
		public:      double to_petabytes () { return bytes / 1000000000000.0; }
	};

	class Node 
	{
		    friend directory::Directory;
		  private: class compare
				   {
				      public: bool operator () (const Node* const a, const Node* const b) const
				      {
							return a->name < b->name;
				      }
				   };
		protected: std::string name;
		protected: Node* parent;
		protected: std::set < Node*, compare > children;
		   public: virtual ~Node () 
		   		   {
						 name.clear ();
						 children.clear ();
				   }
		   public: virtual Size get_size () const = 0;
		   public: virtual bool is_file () const = 0;
		   public: std::vector < const Node* > get_children () const
				   {
					   std::vector < const Node * > v;
					   for (auto& x : children)
						   v.push_back (const_cast <Node*> (x));

						return v;
				   }
		   public: Node (std::string label) : name (label)
		      	   {
		      	      this->parent = nullptr;
		      	   }
		   public: std::string get_path () const
				   {
				       if (this->parent == nullptr)
				        	 return this->name;
				       return this->parent->get_path () + "/" + this->name;
				   }
		   public: const std::string& get_name () const 
		   		   {
					   return this->name;
				   }
		   public: Node* find_by_full_path (const std::string& path)
		   		   {
					   if (path == "/")
					   		return this;
					   if (path [0] != '/')
					   		throw no_such_file_or_directory (path);
					   if (path [path.size () - 1] == '/')
							return _find_by_full_path(path.substr (0, path.size () - 1), 1);
					   else	
							return _find_by_full_path(path, 1);
				   }
		  private: Node* _find_by_full_path (const std::string& path, size_t ind);
		   public: Node* rm_r ()
		   		   {
						Node* p = this->parent;
						for (auto& x : this->children)
							x->rm_r ();
						p->children.erase (this);
						return this;
				   }
		   public: static Node* rm (Node* c)
		   		   {
						Node* p = c->parent;
						c->rm_r ();
						p->children.erase (c);
						delete c;
						return p;
				   }
		   public: Node* rm (const std::string& path)
		   		   {
						return FS::Node::rm (this->find_by_full_path (path));
				   }
	};
	class Find_node_pattern : public Node
	{
		public: Size get_size () const { return Size (); }
		public: bool is_file () const { return false; }

		public: Find_node_pattern (std::string s) : Node (s)
		{

		} 
	};
	Node* Node::_find_by_full_path (const std::string& path, size_t ind)
	{
		size_t split_ind = path.find ('/', ind);
		//std::cout << path.substr (ind) << " " << split_ind << " " << this->get_name () << std::endl;
		if (split_ind == std::string::npos)
		{
			//std::cout << this->get_name () << " == " << path.substr (ind) << std::endl;
			if (children.size () == 0)
				throw FS::no_such_file_or_directory (this->parent->get_path () + "/" + path.substr (ind, split_ind - ind));	

			Node* pattern = new Find_node_pattern (path.substr (ind));
			if (this->children.find (pattern) != this->children.end ())
				return (*this->children.find (pattern));
			else 
				throw FS::no_such_file_or_directory (this->parent->get_path () + "/" + path.substr (ind, split_ind - ind));	
		}
		else
		{
			auto pattern = new Find_node_pattern (path.substr (ind, split_ind - ind));
			//std::cout << this->get_name () << " == " << path.substr (ind, split_ind - ind) << (this->children.find (pattern) != this->children.end ()) << std::endl;

			if (this->children.find (pattern) != this->children.end ())
				return (*this->children.find (pattern))->_find_by_full_path (path, split_ind + 1);
			else 
			{
				//std::cout << "pre GRUM" << std::endl;
				//std::cout << ind << " " << split_ind - ind << std::endl;
				throw FS::no_such_file_or_directory (path);
				//std::cout << "post GRUM" << std::endl;
			}
		}
	}
}
