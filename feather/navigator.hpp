// Copyright 2021 Mustafa Moiz.

#pragma once

#include <string>

#include "cursor.hpp"

/**
 * Static function library for navigating a cursor
 * within a body of text.
 */
class Navigator
{
public:

	/**
	 * Move a cursor left within a body of text.
	 * Will not move past the beginning of the text.
	 */
	static Cursor move_left(const std::string& text, Cursor cursor);

	/**
	 * Move a cursor right within a body of text.
	 * Will not move past the end of the text.
	 */
	static Cursor move_right(const std::string& text, Cursor cursor);

	/**
	 * Move a cursor up within a body of text.
	 * If line above is shorter than current line position,
	 * cursor will be placed at end of line above.
	 * If line above is longer than or equal to current line position,
	 * cursor will be placed at matching line position in line above.
	 * Will not move cursor if already on top line.
	 */
	static Cursor move_up(const std::string& text, Cursor cursor);

	/**
	 * Move a cursor down within a body of text.
	 * If line below is shorter than current line position,
	 * cursor will be placed at end of line below.
	 * If line below is longer than or equal to current line position,
	 * cursor will be placed at matching line position in line below.
	 * Will not move cursor if already on bottom line.
	 */
	static Cursor move_down(const std::string& text, Cursor cursor);

private:

	static char newline_;
};
