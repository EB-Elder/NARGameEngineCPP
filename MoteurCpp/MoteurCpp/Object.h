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

	void Create()
	{
		//std::cout << "CREATE OBJET " << o_name.c_str() << " TAG " << o_tag.c_str() << std::endl;

		//boucle sur les composants -> composant.create
		
	}

	void Update()
	{
		//std::cout << "UPDATE OBJET " << o_name.c_str() << " TAG " << o_tag.c_str() << std::endl;

		//boucle sur les composants -> composant.update
		for (auto c : listComponent)
		{
			c->Update();
		}
	}
};