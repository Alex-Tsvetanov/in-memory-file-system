#pragma once
#include <string>
#include <set>
#include <functional>

namespace directory
{
	class Directory;
}

namespace FS
{
	class Size
	{
		private: std::size_t bits;
		public: Size (std::size_t s = 0) : bits (s)
				{}
		public: std::size_t   operator ()() { return bits; }
		public: std::size_t   operator + (const Size& a) const { return bits + a.bits; }
		public: double     to_bytes () { return bits / 8.0; }
		public: double to_kilobytes () { return bits / 8000.0; }
		public: double to_megabytes () { return bits / 8000000.0; }
		public: double to_terabytes () { return bits / 8000000000.0; }
		public: double to_petabytes () { return bits / 8000000000000.0; }
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
		   public: virtual Size get_size () const = 0;
		   public: virtual bool is_file () const = 0;
		   public: Node (std::string label) : name (label)
		      	   {
		      	      this->parent = nullptr;
		      	   }
		   public: std::string get_path () const
				   {
				       if (this->parent == nullptr)
				        	 return this->name;
				       return this->parent->get_path () + this->name;
				   }
	};
}
