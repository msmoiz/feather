// Copyright 2021 Mustafa Moiz.

#pragma once

/**
 * Exhaustive enumeration of the inputs
 * supported by the editor.
 */
enum class InputType
{
	Backspace,
	Character,
	Delete,
	MoveDown,
	MoveLeft,
	MoveRight,
	MoveUp,
	None,
	Quit,
	Save
};

/**
 * Thin wrapper around input type and
 * an optional value for that type
 * (used when type == InputType::Character).
 */
struct Input
{
	explicit Input(InputType in_type);
	explicit Input(char in_value);

	InputType type;
	char value{' '};
};
