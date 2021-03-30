#pragma once
#include "Component.h"
#include <vector>

struct Object
{
	std::string o_name;
	std::string o_tag;
	std::vector<Component*> listComponent;

	Object()
	{
		o_name = "objet";
		o_tag = "default";

		//listComponent.push_back();
	}

	Object(std::string name, std::string tag)
	{
		o_name = name;
		o_tag = tag;
	}

	Object(std::string name)
	{
		o_name = name;
		o_tag = "default";
	}
};