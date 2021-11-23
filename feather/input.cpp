// Copyright 2021 Mustafa Moiz.

#include "input.hpp"

Input::Input(InputType in_type)
	: type(in_type)
{
}

Input::Input(char in_value)
	: type(InputType::Character)
	, value(in_value)
{
}
