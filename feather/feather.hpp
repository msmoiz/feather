// Copyright 2021 Mustafa Moiz.

#pragma once

#include <memory>
#include <string>

#include "input_handler.hpp"
#include "cursor.hpp"
#include "output_handler.hpp"
#include "serializer.hpp"

/**
 * Text editor that handles the following standard
 * operations:
 * - Navigation
 * - Manipulation
 * - Display
 * - Serialization
 */
class Feather
{
public:

	Feather(std::unique_ptr<InputHandler> input_handler, 
		std::unique_ptr<OutputHandler> output_handler, 
		std::unique_ptr<Serializer> serializer);
	
	void run();

private:

	std::unique_ptr<InputHandler> input_handler_{nullptr};
	std::unique_ptr<OutputHandler> output_handler_{nullptr};
	std::unique_ptr<Serializer> serializer_{nullptr};
	std::string text_;
	Cursor cursor_{0};
};
