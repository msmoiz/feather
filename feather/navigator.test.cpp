// Copyright 2021 Mustafa Moiz.

#include <catch2/catch.hpp>

#include "navigator.hpp"

TEST_CASE("Cursor movement behaves as expected")
{
	const std::string text
	{
		"12\n"
		"456\n"
		"89"
	};

	SECTION("Cursor should move left when in middle of text")
	{
		const Cursor start{5};
		const Cursor end = Navigator::move_left(text, start);
		REQUIRE(end == start - 1);
	}

	SECTION("Cursor should not move left when at start of text")
	{
		const Cursor start{0};
		const Cursor end = Navigator::move_left(text, start);
		REQUIRE(end == start);
	}

	SECTION("Cursor should move right when in middle of text")
	{
		const Cursor start{0};
		const Cursor end = Navigator::move_right(text, start);
		REQUIRE(end == start + 1);
	}

	SECTION("Cursor should not move right when at end of text")
	{
		const Cursor start{9};
		const Cursor end = Navigator::move_right(text, start);
		REQUIRE(end == start);
	}

	SECTION("Cursor should move up when in middle of text")
	{
		const Cursor start{8};
		const Cursor end = Navigator::move_up(text, start);
		REQUIRE(end == 4);
	}

	SECTION("Cursor should move up to correct position when line above is longer")
	{
		const Cursor start{9};
		const Cursor end = Navigator::move_up(text, start);
		REQUIRE(end == 5);
	}

	SECTION("Cursor should move up to correct position when line above is shorter")
	{
		const Cursor start{6};
		const Cursor end = Navigator::move_up(text, start);
		REQUIRE(end == 2);
	}

	SECTION("Cursor should not move up when on top line")
	{
		const Cursor start{2};
		const Cursor end = Navigator::move_up(text, start);
		REQUIRE(end == start);
	}

	SECTION("Cursor should not move up when at beginning of text")
	{
		const Cursor start{0};
		const Cursor end = Navigator::move_up(text, start);
		REQUIRE(end == start);
	}

	SECTION("Cursor should move down when in middle of text")
	{
		const Cursor start{4};
		const Cursor end = Navigator::move_down(text, start);
		REQUIRE(end == 8);
	}

	SECTION("Cursor should move down to correct position when on empty line")
	{
		const std::string text_2{"\n\nHello test\n"};
		const Cursor start{1};
		const Cursor end = Navigator::move_down(text_2, start);
		REQUIRE(end == 2);
	}

	SECTION("Cursor should move down to correct position when line below is longer")
	{
		const Cursor start{2};
		const Cursor end = Navigator::move_down(text, start);
		REQUIRE(end == 5);
	}

	SECTION("Cursor should move down to correct position when line below is shorter")
	{
		const Cursor start{6};
		const Cursor end = Navigator::move_down(text, start);
		REQUIRE(end == 9);
	}

	SECTION("Cursor should move down when positioned at 0")
	{
		const Cursor start{0};
		const Cursor end = Navigator::move_down(text, start);
		REQUIRE(end == 3);
	}

	SECTION("Cursor should not move down when on bottom line")
	{
		const Cursor start{8};
		const Cursor end = Navigator::move_down(text, start);
		REQUIRE(end == start);
	}
}
