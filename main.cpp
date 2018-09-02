#include <fs.hpp>

int main ()
{
	FS::FileSystem fs;
	fs ()->create_child (new file::TxtFile ("test_file_1.txt"))
		 ->create_child (new file::TxtFile ("test_file_2.txt"))
		 ->create_child (new directory::Directory ("New Folder"));
}
