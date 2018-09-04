#include <fs.hpp>

#include <iostream>
#include <initializer_list>

#include <tests/moka/moka.h>

Moka::Context fs_tests("FS::", [](Moka::Context& it) {
	it.has ("FileSystem::", [](Moka::Context& it) {
		it.has ("create_child", [](Moka::Context& it) {
			it.should ("add new file::File*", []() {
					FS::FileSystem fs;

					must_not_equal (fs (), nullptr);
					must_equal (fs ()->get_size ().to_bytes (), 0);

					file::File* test_file = new file::TxtFile ("test_file_1.txt");
					fs ()->create_child (test_file);

					must_equal (fs ()->get_child_by_name("test_file_1.txt"), test_file);
					
					const std::initializer_list<unsigned char> content = {'A','l','e','x',' ','i', 's',' ','p','r','o','g','r','a','m','m','e','r','.'};
					test_file->write (new file::TxtContent (content));

					must_equal (fs ()->get_size ().to_bytes (), content.size ());
			});
			it.should ("add new directory::Directory*", []() {
					FS::FileSystem fs;

					must_not_equal (fs (), nullptr);
					must_equal (fs ()->get_size ().to_bytes (), 0);
			
					directory::Directory* test_folder = new directory::Directory ("test_folder");
					fs ()->create_child (test_folder);

					must_equal (fs ()->get_child_by_name("test_folder"), test_folder);
			});
		});
		it.has ("rm", [](Moka::Context& it) {
			it.should ("remove an existing file::File*", []() {
					FS::FileSystem fs;

					must_not_equal (fs (), nullptr);
					must_equal (fs ()->get_size ().to_bytes (), 0);

					file::File* test_file = new file::TxtFile ("test_file_1.txt");
					fs ()->create_child (test_file);

					must_equal (fs ()->get_child_by_name("test_file_1.txt"), test_file);
					
					const std::initializer_list<unsigned char> content = {'A','l','e','x',' ','i', 's',' ','p','r','o','g','r','a','m','m','e','r','.'};
					test_file->write (new file::TxtContent (content));

					must_equal (fs ()->get_size ().to_bytes (), content.size ());

					fs ()->rm (fs ()->get_child_by_name ("test_file_1.txt"));
					
					must_equal (fs ()->get_size ().to_bytes (), 0);
					must_equal (fs ()->get_children().size (), 0); 
			});
			it.should ("remove an existing directory::Directory*", []() {
					FS::FileSystem fs;

					must_not_equal (fs (), nullptr);
					must_equal (fs ()->get_size ().to_bytes (), 0);

					directory::Directory* test_folder = new directory::Directory ("test_folder");
					fs ()->create_child (test_folder);

					must_equal (fs ()->get_child_by_name("test_folder"), test_folder);

					fs ()->rm (fs ()->get_child_by_name ("test_folder"));
					must_equal (fs ()->get_children().size (), 0); 
			});
			it.should ("throw a FS::no_such_file_or_directory exception when remove an unexisting FS::Node*", []() {
					FS::FileSystem fs;

					must_not_equal (fs (), nullptr);
					must_equal (fs ()->get_size ().to_bytes (), 0);

					must_throw (FS::no_such_file_or_directory, [&]() { fs ()->rm ("test_folder"); }); 
			});
		});
	});
});
int main () 
{
	std::cout << "===============================  Testing  ===============================\n\n";
	Moka::Report report;
	fs_tests.test(report);
	report.print();
	return 0;
}
