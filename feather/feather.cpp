// Copyright 2021 Mustafa Moiz.

#include "feather.hpp"

#include <iostream>

#include "manipulator.hpp"
#include "navigator.hpp"
#include "input_handler.hpp"
#include "input_handler_console.hpp"
#include "output_handler_console.hpp"

Feather::Feather(std::unique_ptr<InputHandler> input_handler, 
	std::unique_ptr<OutputHandler> output_handler, 
	std::unique_ptr<Serializer> serializer)
	: input_handler_(std::move(input_handler))
	, output_handler_(std::move(output_handler))
	, serializer_(std::move(serializer))
{
}

void Feather::run()
{
	text_ = serializer_->deserialize();
	
	input_handler_->init();
	output_handler_->init();

	auto quit_requested{false};
	while (!quit_requested)
	{
		output_handler_->render(text_, cursor_);
		
		switch (const Input input{input_handler_->get()}; input.type)
		{
		case InputType::Backspace:
			text_ = Manipulator::delet(std::move(text_), cursor_ - 1);
			cursor_ = Navigator::move_left(text_, cursor_);
			break;
		case InputType::Character:
			text_ = Manipulator::insert(std::move(text_), cursor_, input.value);
			cursor_ = Navigator::move_right(text_, cursor_);
			break;
		case InputType::Delete:
			text_ = Manipulator::delet(std::move(text_), cursor_);
			break;
		case InputType::MoveDown:
			cursor_ = Navigator::move_down(text_, cursor_);
			break;
		case InputType::MoveLeft: 
			cursor_ = Navigator::move_left(text_, cursor_);
			break;
		case InputType::MoveRight: 
			cursor_ = Navigator::move_right(text_, cursor_);
			break;
		case InputType::MoveUp: 
			cursor_ = Navigator::move_up(text_, cursor_);
			break;
		case InputType::None:
			continue;
		case InputType::Quit:
			quit_requested = true;
			continue;
		case InputType::Save:
			serializer_->serialize(text_);
			break;
		}
	}

	input_handler_->shutdown();
	output_handler_->shutdown();
}
