#include <fs.hpp>

#include <iostream>
#include <initializer_list>

#include <tests/moka/moka.h>

Moka::Context fs_tests("Library for In-memory filesystem interface", [](Moka::Context& it) {
	it.has ("FS::", [](Moka::Context& it) {
		it.has ("FileSystem::", [](Moka::Context& it) {
			it.has ("FileSystem()", [](Moka::Context& it) {
				it.has ("operator()", [](Moka::Context& it) {
					it.should ("return existing root", []() {
						must_not_equal (FS::FileSystem ()(), nullptr);
					});
				});
				it.has ("get_iterator()", [](Moka::Context& it) {
					it.should ("return existing root", []() {
						must_not_equal (FS::FileSystem ().get_iterator (), nullptr);
					});
				});
			});
		});
		it.has ("Node::", [](Moka::Context& it) {
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
				it.should ("add an existing directory::Directory*", []() {
						FS::FileSystem fs;

						must_not_equal (fs (), nullptr);
						must_equal (fs ()->get_size ().to_bytes (), 0);
				
						directory::Directory* test_folder = new directory::Directory ("test_folder");
						fs ()->create_child (test_folder);

						must_throw (FS::file_exists, [&]()
								{ 
									fs ()->create_child(test_folder);
								} 
						);
				});
				it.should ("not add a new file:File* with same name as existing directory::Directory*", []() {
						FS::FileSystem fs;

						must_not_equal (fs (), nullptr);
						must_equal (fs ()->get_size ().to_bytes (), 0);
				
						directory::Directory* test_folder = new directory::Directory ("test_name");
						fs ()->create_child (test_folder);
				
						file::File* test_file = new file::TxtFile ("test_name");

						must_throw (FS::file_exists, [&]()
								{ 
									fs ()->create_child(test_file);
								} 
						);
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
				it.should ("not throw a FS::no_such_file_or_directory exception when remove an unexisting FS::Node*", []() {
						FS::FileSystem fs;

						must_not_equal (fs (), nullptr);
						must_equal (fs ()->get_size ().to_bytes (), 0);

						must_throw (FS::no_such_file_or_directory, [&]() { fs ()->rm ("test_folder"); }); 
				});
			});
		});
	});
	it.has ("file::", [](Moka::Context& it) {
		it.has ("File::", [](Moka::Context& it) {
			it.has ("get_type", [](Moka::Context& it) {
				it.should ("return TxtType for a file::TxtFile*", []() {
					file::File* f = new file::TxtFile ("test_name.txt");
					must_equal (f->get_type ()->extension (), 
												file::TxtType ().extension ());
					must_equal (f->get_type ()->name (), 
												file::TxtType ().name ());
				});
			});
			it.has ("get_content", [](Moka::Context& it) {
				it.should ("return TxtContent for a file::TxtFile*", []() {
					file::File* f = new file::TxtFile ("test_name.txt");
					f->write (new file::TxtContent ({'a','b','c'}));
					must_equal (f->get_content ()->to_ascii_string (), "abc");
				});
			});
			it.has ("is_file", [](Moka::Context& it) {
				it.should ("return true for a file::TxtFile*", []() {
					file::File* f = new file::TxtFile ("test_name.txt");
					must_equal (f->is_file (), true);
				});
			});
			it.has ("get_size", [](Moka::Context& it) {
				it.should ("return 0 for an empty file::TxtFile*", []() {
					file::File* f = new file::TxtFile ("test_name.txt");
					must_equal (f->get_size ().to_bytes (), 0);
				});
				it.should ("return 4 for file::TxtFile* with content \"Alex\"", []() {
					file::File* f = new file::TxtFile ("test_name.txt");
					f->write (new file::TxtContent ({'A','l','e','x'}));
					must_equal (f->get_size ().to_bytes (), 4);
				});
			});
		});
		it.has ("TxtFile::", [](Moka::Context& it) {
			it.has ("get_encoding", [](Moka::Context& it) {
				it.should ("return Encoding::ascii for file::TxtFile*", []() {
					file::File* f = new file::TxtFile ("test_name.txt");
					must_equal ((unsigned int)f->get_content ()->encoding (), (unsigned int)file::Encoding::ascii);
				});
			});
		});
	});
	it.has ("directory::", [](Moka::Context& it) {
		it.has ("Directory::", [](Moka::Context& it) {
			it.has ("is_file", [](Moka::Context& it) {
				it.should ("return false for any directory::Directory*", []() {
					directory::Directory* d = new directory::Directory ("test_name");
					must_equal (d->is_file (), false);
				});
			});
			it.has ("get_size", [](Moka::Context& it) {
				it.should ("return 0 for empty directory::Directory*", []() {
					directory::Directory* d = new directory::Directory ("test_name");
					must_equal (d->get_size ().to_bytes (), 0);
				});
				it.should ("return 4 for a directory::Directory* with a file::File* with size = 4", []() {
					directory::Directory* d = new directory::Directory ("test_name");
					file::File* f = new file::TxtFile ("test_file.txt");
					f->write (new file::TxtContent ({'A','l','e','x'}), std::ofstream::app);
					d->create_child (f);
					must_equal (d->get_size ().to_bytes (), f->get_size ().to_bytes ());
				});
			});
		});
	});
});
int main () 
{
	std::cout << "===============================  Testing  ===============================\n";
	Moka::Report report;
	fs_tests.test(report);
	report.print();
	return 0;
}
