#pragma once
#include <stdexcept>
class OutOfScoreException : public std::exception
{
public:
	OutOfScoreException();
};

