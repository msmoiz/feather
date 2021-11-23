// Copyright 2021 Mustafa Moiz.

#include <iostream>
#include <filesystem>

#include "feather.hpp"
#include "input_handler_console.hpp"
#include "output_handler_console.hpp"
#include "serializer_filesystem.hpp"

int main(int argument_count, const char* arguments[])
{
	if (argument_count < 2)
	{
		std::cerr << "Missing filename argument" << std::endl;
		return 1;
	}

	std::string filename{arguments[1]};
	
	Feather feather
	{
		std::make_unique<InputHandlerConsole>(),
		std::make_unique<OutputHandlerConsole>(),
		std::make_unique<SerializerFilesystem>(filename)
	};
	
	feather.run();
}
