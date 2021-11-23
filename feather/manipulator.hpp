// Copyright 2021 Mustafa Moiz.

#pragma once

#include <string>

#include "cursor.hpp"

/**
 * Static function library for manipulating text
 * beneath a cursor.
 */
class Manipulator
{
public:

	/**
	 * Insert the provided character directly ahead of the cursor.
	 * Following characters are moved forward.
	 * If the cursor is beyond the bounds of the text,
	 * the operation silently fails.
	 */
	static std::string insert(std::string&& text, Cursor cursor, char c);

	/**
	 * Delete the character directly ahead of the cursor.
	 * Following characters are moved backward.
	 * If the cursor is beyond the bounds of the text,
	 * the operation silently fails.
	 */
	static std::string delet(std::string&& text, Cursor cursor);
};
