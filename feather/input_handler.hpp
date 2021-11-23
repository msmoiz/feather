// Copyright 2021 Mustafa Moiz.

#pragma once

#include "input.hpp"

/**
 * Interface representing the operations
 * supported by an input handler.
 */
class InputHandler
{
public:

	/**
	 * Initialize the handler.
	 * Called exactly once.
	 */
	virtual void init() = 0;

	/**
	 * Get input from the target device.
	 */
	virtual Input get() = 0;

	/**
	 * Shutdown the handler.
	 * Called exactly once.
	 */
	virtual void shutdown() = 0;

	virtual ~InputHandler() = default;
};
