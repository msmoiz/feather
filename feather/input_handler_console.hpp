// Copyright 2021 Mustafa Moiz.

#pragma once

#include <string>
#include <unordered_map>

#include "input_handler.hpp"

/**
 * Input handler capable of reading and processing
 * input from a console. Currently supports Windows only.
 */
class InputHandlerConsole final : public InputHandler
{
	void init() override;
	Input get() override;
	void shutdown() override;

	static const char escape;
	static const char backspace;
	static const char carriage_return;
	static const char newline;
	static const char ctrl_s;
	static const std::unordered_map<std::string, InputType> supported_escape_sequences;
};
