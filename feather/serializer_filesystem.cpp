// Copyright 2021 Mustafa Moiz.

#include "serializer_filesystem.hpp"

#include <fstream>
#include <sstream>
#include <utility>

SerializerFilesystem::SerializerFilesystem(std::string filename)
	: filename_(std::move(filename))
{
}

void SerializerFilesystem::serialize(std::string text)
{
	std::ofstream writer{filename_};
	writer << text;
}

std::string SerializerFilesystem::deserialize()
{
	const std::ifstream reader{filename_};
	std::stringstream ss;
	ss << reader.rdbuf();
	return ss.str();
}
