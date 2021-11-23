// Copyright 2021 Mustafa Moiz.

#include "input_handler_console.hpp"

#include <iostream>
#include <unordered_map>

#include <Windows.h>

/**
 * Console mode manipulations to enable virtual terminal processing,
 * as well as virtual terminal sequences used here, are pulled from
 * the following sources:
 * - https://docs.microsoft.com/en-us/windows/console/setconsolemode
 * - https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
 */

const char InputHandlerConsole::escape{'\x1b'};
const char InputHandlerConsole::backspace{'\x7f'};
const char InputHandlerConsole::carriage_return{'\r'};
const char InputHandlerConsole::newline{'\n'};
const char InputHandlerConsole::ctrl_s{19};
const std::unordered_map<std::string, InputType> InputHandlerConsole::supported_escape_sequences
{
	{"[A", InputType::MoveUp},
	{"[B", InputType::MoveDown},
	{"[C", InputType::MoveRight},
	{"[D", InputType::MoveLeft},
	{"[3~", InputType::Delete},
	{"", InputType::Quit}
};

void InputHandlerConsole::init()
{
	HANDLE standard_input_handle{GetStdHandle(STD_INPUT_HANDLE)};
	DWORD console_mode{0};
	GetConsoleMode(standard_input_handle, &console_mode);
	console_mode |= ENABLE_VIRTUAL_TERMINAL_INPUT;
	console_mode = console_mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);
	if (!SetConsoleMode(standard_input_handle, console_mode))
	{
		std::cerr << "Failed to set console mode." << std::endl;
		std::cerr << "Error: " << GetLastError() << std::endl;
	}
}

Input InputHandlerConsole::get()
{
	static HANDLE standard_input_handle{GetStdHandle(STD_INPUT_HANDLE)};
	
	char c;

	/**
	 * Using Windows API instead of std::cin >> operator or std::cin.get()
	 * because disabling ENABLE_LINE_INPUT flag on init messes up reading
	 * newlines from input buffer.
	 * See https://stackoverflow.com/questions/61162279/how-can-i-generate-an-backspace-in-a-visual-studio-debug-console/61175657#61175657.
	 */
	{
		const DWORD chars_to_read{1};
		DWORD chars_read;
		ReadConsole(standard_input_handle, &c, chars_to_read, &chars_read, nullptr);
	}

	switch (c)
	{
	case backspace:
		return Input{InputType::Backspace};
	case carriage_return:
		return Input{newline};
	case ctrl_s:
		return Input{InputType::Save};
	case escape:
		{
			char sequence[10]{""};

			DWORD inputs_left_in_buffer;
			GetNumberOfConsoleInputEvents(standard_input_handle, &inputs_left_in_buffer);
			if (inputs_left_in_buffer > 0)
			{
				const DWORD chars_to_read{10};
				DWORD chars_read;
				ReadConsole(standard_input_handle, sequence, chars_to_read, &chars_read, nullptr);
			}

			const auto search = supported_escape_sequences.find(sequence);
			return search != supported_escape_sequences.end() ? Input{search->second} : Input{InputType::None};
		}
	default:
		return Input{c};
	}
}

void InputHandlerConsole::shutdown()
{
	// no op
}
