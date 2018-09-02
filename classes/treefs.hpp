#include <fs.hpp>
#include <string>

class TreeFS : FileSystem
{
	private: FS::Node* label;
	 public: TreeFileSystem (std::string name = "/") : label (name)
			 {}
};
