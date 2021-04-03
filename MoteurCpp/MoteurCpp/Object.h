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

		Transform t(0.0f, 0.0f, 0.0f);
		t.objectName = o_name;

		listComponent.push_back(&t);
	}

	Object(std::string name)
	{
		o_name = name;
		o_tag = "default";

		Transform t(0.0f, 0.0f, 0.0f);
		t.objectName = o_name;

		listComponent.push_back(&t);
	}

	Object(std::string name, float px, float py, float pz)
	{
		o_name = name;
		o_tag = "default";

		Transform t(px, py, pz);
		t.objectName = o_name;

		listComponent.push_back(&t);
	}

	Object(std::string name, std::string tag, float px, float py, float pz)
	{
		o_name = name;
		o_tag = tag;

		Transform t(px, py, pz);
		t.objectName = o_name;

		listComponent.push_back(&t);
	}

	void Create()
	{
		std::cout << "CREATE OBJET " << o_name.c_str() << " TAG " << o_tag.c_str() << std::endl;		
	}

	void Update()
	{
		std::cout << "UPDATE OBJET " << o_name.c_str() << " TAG " << o_tag.c_str() << std::endl;

		//boucle sur les composants -> composant.update
		for (auto c : listComponent)
		{
			c->Update();
		}
	}
};