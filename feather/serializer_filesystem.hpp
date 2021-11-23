// Copyright 2021 Mustafa Moiz.

#pragma once

#include "serializer.hpp"

/**
 * Serializer capable of reading and writing
 * to and from a filesystem. Currently supports Windows only.
 */
class SerializerFilesystem final : public Serializer
{
public:

	SerializerFilesystem(std::string filename);

private:
	
	void serialize(std::string text) override;
	std::string deserialize() override;

	std::string filename_;
};
