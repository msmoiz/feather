// Copyright 2021 Mustafa Moiz.

#include "output_handler_console.hpp"

#include <iostream>
#include <sstream>

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

	const auto text_view_start = viewport_.y - 1 == 0 ? 0 : get_nth_occurrence('\n', text, 0, viewport_.y - 1);
	const auto text_view_end = get_nth_occurrence('\n', text, 0, viewport_.y + viewport_.height - 2);

	std::cout << text.substr(text_view_start, text_view_end - text_view_start - 1);

	set_cursor_coordinates(1, viewport_.height);
	std::cout << clear_line;
	std::cout << "Line: " << target_y << ", Position: " << target_x;
	
	set_cursor_coordinates(target_x, target_y - viewport_.y + 1);

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

std::size_t OutputHandlerConsole::get_nth_occurrence(char needle, const std::string& haystack, std::size_t pos, std::size_t n)
{
	const size_t found_pos = haystack.find(needle, pos);
	if (0 == n || std::string::npos == found_pos) { return found_pos; }
    return get_nth_occurrence(needle, haystack, found_pos + 1, n - 1);
}
