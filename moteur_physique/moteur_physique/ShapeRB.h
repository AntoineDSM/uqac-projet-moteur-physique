#pragma once
#include <string>

typedef struct ShapeRB {
	std::string shape;

	ShapeRB()
	{
		shape = "";
	}

	ShapeRB(std::string _shape)
	{
		shape = _shape;
	}
};
