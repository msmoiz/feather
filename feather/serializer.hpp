// Copyright 2021 Mustafa Moiz.

#pragma once

#include <string>

/**
 * Interface representing the operations
 * supported by a serializer.
 */
class Serializer
{
public:
	
	/**
	 * Save text to target device.
	 */
	virtual void serialize(std::string text) = 0;

	/**
	 * Get text from target device.
	 */
	virtual std::string deserialize() = 0;
	
	virtual ~Serializer() = default;
};
