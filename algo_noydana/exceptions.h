#pragma once

class Exceptions {
public:
	virtual ~Exceptions() = default;
};

class InvalidValueException : public Exceptions {};

class OutOfBoundsException : public InvalidValueException
{};

class NotSimpleGraph : public InvalidValueException 
{};