// Copyright 2021 Mustafa Moiz.

#include "output_handler_console.hpp"

#include <iostream>
#include <sstream>
#include <vector>

#include <Windows.h>

/**
 * Console mode manipulations to enable virtual terminal processing,
 * as well as virtual terminal sequences used here, are pulled from
 * the following sources:
 * - https://docs.microsoft.com/en-us/windows/console/setconsolemode
 * - https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
 */

const std::string OutputHandlerConsole::switch_to_alt_buffer{"\x1b[?1049h"};
const std::string OutputHandlerConsole::switch_to_main_buffer{"\x1b[?1049l"};
const std::string OutputHandlerConsole::show_cursor{"\x1b[?25h"};
const std::string OutputHandlerConsole::hide_cursor{"\x1b[?25l"};
const std::string OutputHandlerConsole::clear_screen{"\x1b[2J"};
const std::string OutputHandlerConsole::clear_line{"\x1b[0K"};
const std::string OutputHandlerConsole::enable_cursor_blink{"\x1b[?12h"};
const std::string OutputHandlerConsole::disable_cursor_blink{"\x1b[?12l"};

void OutputHandlerConsole::init()
{
	HANDLE standard_output_handle{GetStdHandle(STD_OUTPUT_HANDLE)};
	DWORD console_mode{0};
	GetConsoleMode(standard_output_handle, &console_mode);
	console_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	if (!SetConsoleMode(standard_output_handle, console_mode))
	{
		std::cerr << "Failed to set console mode." << std::endl;
		std::cerr << "Error: " << GetLastError() << std::endl;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(standard_output_handle, &csbi);
	viewport_.width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	viewport_.height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	std::cout << switch_to_alt_buffer;
	std::cout << disable_cursor_blink;
}

void OutputHandlerConsole::render(const std::string& text, Cursor cursor)
{
	std::cout << hide_cursor;

	set_cursor_coordinates(1, 1);
	std::cout << clear_screen;

	const auto [target_x, target_y] = calculate_absolute_cursor_target_coordinates(text, cursor);	
	while (target_y < viewport_.y) { --viewport_.y; }
	while (target_y >= (viewport_.y + viewport_.height - 1)) { ++viewport_.y; }
	while (target_x < viewport_.x) { --viewport_.x; }
	while (target_x >= (viewport_.x + viewport_.width - 1)) { ++viewport_.x; }

	std::cout << get_text_view(text, cursor, {target_x, target_y});

	set_cursor_coordinates(1, viewport_.height);
	std::cout << clear_line;
	std::cout << "Line: " << target_y << ", Position: " << target_x;

	const auto [rel_x, rel_y] = std::pair{target_x - viewport_.x + 1, target_y - viewport_.y + 1};
	set_cursor_coordinates(rel_x, rel_y);

	std::cout << show_cursor;
}

void OutputHandlerConsole::shutdown()
{
	std::cout << enable_cursor_blink;
	std::cout << switch_to_main_buffer;
}

void OutputHandlerConsole::set_cursor_coordinates(std::size_t x, std::size_t y)
{
	std::cout << "\x1b[" << y << ";" << x << "H";
}

std::pair<std::size_t, std::size_t> OutputHandlerConsole::calculate_absolute_cursor_target_coordinates(const std::string& text, Cursor cursor)
{
	if (cursor == 0)
	{
		return {1, 1};
	}
	
	size_t y = 1;
    for (size_t pos = 0; (pos = text.find('\n', pos)) != std::string::npos && pos < cursor; ++pos, ++y)
		;
	
	const auto current_line = text.find_last_of('\n', cursor - 1) + 1;
	const auto x = cursor - current_line + 1;

	return {x, y};
}

std::string OutputHandlerConsole::get_text_view(const std::string& text, Cursor cursor,
	std::pair<std::size_t, std::size_t> absolute_target_coordinates)
{
	const auto first_row_start = viewport_.y - 1 == 0 ? 0 : get_nth_occurrence('\n', text, 0, viewport_.y - 1);
	const auto last_row_start = get_nth_occurrence('\n', text, 0, viewport_.y + viewport_.height - 2);
	const std::string row_limited_text = text.substr(first_row_start, last_row_start - first_row_start - 1);

	std::vector<std::string> rows;
	{
		std::stringstream ss{row_limited_text};
		std::string row;
		while (std::getline(ss, row, '\n'))
		{
			rows.push_back(row);
		}
	}

	for (std::string& row : rows)
	{
		row = viewport_.x - 1 < row.length()
			? row.substr(viewport_.x - 1, viewport_.width)
			: "";
	}

	std::string row_and_column_limited_text;
	for (const std::string& row: rows)
	{
		row_and_column_limited_text.append(row).append("\n");
	}
	row_and_column_limited_text.erase(row_and_column_limited_text.end() - 1);
	
	return row_and_column_limited_text;
}

std::size_t OutputHandlerConsole::get_nth_occurrence(char needle, const std::string& haystack, std::size_t pos, std::size_t n)
{
	const size_t found_pos = haystack.find(needle, pos);
	if (0 == n || std::string::npos == found_pos) { return found_pos; }
    return get_nth_occurrence(needle, haystack, found_pos + 1, n - 1);
}
