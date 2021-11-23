// Copyright 2021 Mustafa Moiz.

#include "navigator.hpp"

char Navigator::newline_{'\n'};

Cursor Navigator::move_left(const std::string& text, Cursor cursor)
{
	return cursor == 0
		       ? cursor
		       : std::max(Cursor{0}, cursor - 1);
}

Cursor Navigator::move_right(const std::string& text, Cursor cursor)
{
	return cursor == std::numeric_limits<Cursor>::max()
		       ? cursor
		       : std::min(text.length(), cursor + 1);
}

Cursor Navigator::move_up(const std::string& text, Cursor cursor)
{
	if (cursor == 0)
	{
		return cursor;
	}
	
	const auto current_line_start{text.find_last_of(newline_, cursor - 1) + 1};
	if (current_line_start == 0) // current line is top line
	{
		return cursor;
	}
	const auto current_line_pos{cursor - current_line_start};

	const auto previous_line_start{text.find_last_of(newline_, current_line_start - 2) + 1};
	const auto previous_line_length{current_line_start - previous_line_start - 1};

	return std::min(previous_line_start + current_line_pos, previous_line_start + previous_line_length);
}

Cursor Navigator::move_down(const std::string& text, Cursor cursor)
{
	const auto current_line_start{cursor > 0 ? text.find_last_of(newline_, cursor - 1) + 1 : 0};
	const auto current_line_pos{cursor - current_line_start};

	const auto next_line_start{text.find_first_of(newline_, current_line_start + 1) + 1};
	if (next_line_start == 0) // next line is bottom line
	{
		return cursor;
	}
	const auto next_line_end{text.find_first_of(newline_, next_line_start) + 1};
	const auto next_line_length
	{
		next_line_end == 0
			? text.length() - next_line_start
			: next_line_end - next_line_start - 1
	};

	return std::min(next_line_start + current_line_pos, next_line_start + next_line_length);
}
