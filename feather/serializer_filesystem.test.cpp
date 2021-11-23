// Copyright 2021 Mustafa Moiz.

#include <catch2/catch.hpp>

#include "serializer_filesystem.hpp"

TEST_CASE("File serialization and deserialization behaves as expected")
{
	const std::string text
	{
		"12\n"
		"456\n"
		"89"
	};
	std::string filename{"ser_de_test.txt"};

	std::unique_ptr<Serializer> serializer{std::make_unique<SerializerFilesystem>(filename)};
	serializer->serialize(text);
	auto output{serializer->deserialize()};
	REQUIRE(output == text);
}
