#pragma once
#include <string>
class IFormattable
{
public:
	virtual std::wstring format() = 0;
	virtual void prettyPrint(const IFormattable& object) = 0;
};
