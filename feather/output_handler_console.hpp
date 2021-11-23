// Copyright 2021 Mustafa Moiz.

#pragma once

#include <string>

#include "output_handler.hpp"

/**
 * Output handler capable of processing and rendering
 * output to a console. Currently supports Windows only.
 */
class OutputHandlerConsole final : public OutputHandler
{
	void init() override;
	void render(const std::string& text, Cursor cursor) override;
	void shutdown() override;

	void set_cursor_coordinates(std::size_t x, std::size_t y);
	std::pair<std::size_t, std::size_t> calculate_absolute_cursor_target_coordinates(const std::string& text, Cursor cursor);
	std::size_t get_nth_occurrence(char needle, const std::string& haystack, std::size_t pos, std::size_t n);

	struct
	{
		std::size_t width{0};
		std::size_t height{0};
		std::size_t x{1};
		std::size_t y{1};
	} viewport_;

	static const std::string switch_to_alt_buffer;
	static const std::string switch_to_main_buffer;
	static const std::string show_cursor;
	static const std::string hide_cursor;
	static const std::string clear_screen;
	static const std::string clear_line;
	static const std::string enable_cursor_blink;
	static const std::string disable_cursor_blink;
};
