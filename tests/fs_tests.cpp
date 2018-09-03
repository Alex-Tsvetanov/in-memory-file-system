#include <fs.hpp>

#include <iostream>
#include <initializer_list>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

TEST_SUITE("FileSystem") {
	TEST_SUITE("create_child") {
		TEST_CASE("should add new file::File") {
			FS::FileSystem fs;

			REQUIRE(fs () != nullptr);
			REQUIRE(fs ()->get_size ().to_bytes () == 0);

			file::File* test_file = new file::TxtFile ("test_file_1.txt");
			fs ()->create_child (test_file);

			CHECK(fs ()->get_child_by_name("test_file_1.txt") == test_file);
			
			const std::initializer_list<unsigned char> content = {'A','l','e','x',' ','i', 's',' ','p','r','o','g','r','a','m','m','e','r','.'};
			test_file->write (new file::TxtContent (content));

			CHECK(fs ()->get_size ().to_bytes () == content.size ());
		}
		TEST_CASE("should add new directory::Directory") {
			FS::FileSystem fs;

			REQUIRE(fs () != nullptr);
			REQUIRE(fs ()->get_size ().to_bytes () == 0);

			directory::Directory* test_folder = new directory::Directory ("test_folder");
			fs ()->create_child (test_folder);

			CHECK(fs ()->get_child_by_name("test_folder") == test_folder);
		}
	}
}