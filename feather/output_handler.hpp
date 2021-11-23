// Copyright 2021 Mustafa Moiz.

#pragma once

#include "cursor.hpp"

/**
 * Interface representing the operations
 * supported by an output handler.
 */
class OutputHandler
{
public:

	/**
	 * Initialize the handler.
	 * Called exactly once.
	 */
	virtual void init() = 0;

	/**
	 * Display output on the target device.
	 */
	virtual void render(const std::string& text, Cursor cursor) = 0;

	/**
	 * Shutdown the handler.
	 * Called exactly once.
	 */
	virtual void shutdown() = 0;
	
	virtual ~OutputHandler() = default;
};
