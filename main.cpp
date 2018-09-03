#include <fs.hpp>

int main ()
{
	FS::FileSystem fs;
	fs ()->create_child (new file::TxtFile ("test_file_1.txt"))
		 ->create_child (new file::TxtFile ("test_file_2.txt"))
		 ->create_child (new directory::Directory ("New Folder"));
	FS::FileSystem::printTree (fs.get_iterator());

	reinterpret_cast<directory::Directory*>(fs ()->get_child_by_name ("New Folder"))->create_child (new file::TxtFile ("test_file_3.txt"));

	FS::FileSystem::printTree (fs.get_iterator());

	reinterpret_cast<file::File*>(reinterpret_cast<directory::Directory*>(fs ()->get_child_by_name ("New Folder"))->get_child_by_name ("test_file_3.txt"))->write (new file::TxtContent ({'a','b','c','d'}), std::ofstream::app);

	FS::FileSystem::printTree (fs.get_iterator());
	
	try {
		FS::Node* file = reinterpret_cast<directory::Directory*>(fs ()->get_child_by_name ("New Folder"))->get_child_by_name ("There_is_no_file_like.that");
	}
	catch (FS::no_such_file_or_directory exc) { std::cout << exc.what () << std::endl; }

	try {
		fs ()->find_by_full_path ("/");
		std::cout << "/ => done" << std::endl;
	} catch (FS::no_such_file_or_directory exc) { std::cout << exc.what () << std::endl; }
	
	try {
		fs ()->find_by_full_path ("/New Folder");
		std::cout << "/New Folder => done" << std::endl;
	} catch (FS::no_such_file_or_directory exc) { std::cout << exc.what () << std::endl; }
	
	try {
		fs ()->find_by_full_path ("/New Folder/");
		std::cout << "/New Folder/ => done" << std::endl;
	} catch (FS::no_such_file_or_directory exc) { std::cout << exc.what () << std::endl; }
	
	try {
		fs ()->find_by_full_path ("/New Folder/test_file_3.txt");
		std::cout << "/New Folder/test_file_3.txt => done" << std::endl;
	} catch (FS::no_such_file_or_directory exc) { std::cout << exc.what () << std::endl; }

	try { fs ()->find_by_full_path ("/asdf/asdf/asdf"); }
	catch (FS::no_such_file_or_directory exc) 
	{ 
		std::cout << exc.what () << std::endl; 
		std::cout << "/asdf/asdf/asdf => done" << std::endl;
	}

	try {
		FS::Node::rm (fs ()->find_by_full_path("/test_file_2.txt"));
	} catch (FS::no_such_file_or_directory exc) { std::cout << exc.what () << std::endl; }

	FS::FileSystem::printTree (fs.get_iterator());
}
