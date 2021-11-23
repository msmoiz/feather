// Copyright 2021 Mustafa Moiz.

#include <catch2/catch.hpp>

#include "manipulator.hpp"

TEST_CASE("Manipulator behaves as expected")
{
	std::string start{"Hello world"};

	SECTION("Insert should add character under cursor")
	{
		const Cursor cursor{11};
		const std::string end = Manipulator::insert(std::move(start), cursor, '!');
		REQUIRE(end == "Hello world!");
	}

	SECTION("Delete should remove character after cursor")
	{
		const Cursor cursor{10};
		const std::string end = Manipulator::delet(std::move(start), cursor);
		REQUIRE(end == "Hello worl");
	}
}
