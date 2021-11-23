cmake_minimum_required(VERSION 3.19)
project(feather)

add_executable(feather 
	"feather/main.cpp"
	"feather/feather.cpp"
	"feather/manipulator.cpp"
	"feather/input.cpp"
	"feather/navigator.cpp"
	"feather/input_handler_console.cpp"
	"feather/output_handler_console.cpp"
	"feather/serializer_filesystem.cpp")
set_target_properties(feather PROPERTIES CXX_STANDARD 17)
target_include_directories(feather PRIVATE "feather")

add_executable(tests
	"feather/main.test.cpp"
	"feather/manipulator.test.cpp"
	"feather/serializer_filesystem.cpp"
	"feather/serializer_filesystem.test.cpp"
	"feather/manipulator.cpp"
	"feather/navigator.cpp"
	"feather/navigator.test.cpp")
set_target_properties(feather PROPERTIES CXX_STANDARD 17)
target_include_directories(tests PRIVATE "feather")
find_package(Catch2 REQUIRED)
target_link_libraries(tests Catch2::Catch2)
