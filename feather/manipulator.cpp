// Copyright 2021 Mustafa Moiz.

#include "manipulator.hpp"

std::string Manipulator::insert(std::string&& text, Cursor cursor, char c)
{
	return cursor >= 0 && cursor <= text.length() ? text.insert(cursor, 1, c) : text;
}

std::string Manipulator::delet(std::string&& text, Cursor cursor)
{
	return cursor >= 0 && cursor < text.length() ? text.erase(cursor, 1) : text;
}
