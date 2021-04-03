#pragma once
#include "Component.h"
#include <vector>
#include <memory>

struct Object
{
	std::string o_name;
	std::string o_tag;
	std::vector<std::shared_ptr<Component>> listComponent;

	Object()
	{
		o_name = "objet";
		o_tag = "default";

		Transform t(0.0f, 0.0f, 0.0f);
		t.objectName = o_name;

		auto ptr = std::make_shared<Transform>(t);

		listComponent.push_back(ptr);
	}

	Object(std::string name)
	{
		o_name = name;
		o_tag = "default";

		Transform t(0.0f, 0.0f, 0.0f);
		t.objectName = name;

		auto ptr = std::make_shared<Transform>(t);

		listComponent.push_back(ptr);
	}

	Object(std::string name, float px, float py, float pz)
	{
		o_name = name;
		o_tag = "default";

		Transform t(px, py, pz);
		t.objectName = name;

		auto ptr = std::make_shared<Transform>(t);

		listComponent.push_back(ptr);
	}

	Object(std::string name, std::string tag, float px, float py, float pz)
	{
		o_name = name;
		o_tag = tag;

		Transform t(px, py, pz);
		t.objectName = name;

		auto ptr = std::make_shared<Transform>(t);

		listComponent.push_back(ptr);
	}

	void Create()
	{
		std::cout << "CREATE OBJET " << o_name.c_str() << " TAG " << o_tag.c_str() << std::endl;		
	}

	void DeInitialize()
	{
		std::cout << "DEINITIALIZATION OBJECT " << o_name.c_str() << std::endl;

		//détruire les composants
		for (int i = 0; i < listComponent.size(); i++)
		{
			listComponent[i]->~Component();
		}

		listComponent.clear();
	}

	void Destroy()
	{
		std::cout << "DESTRUCTION OBJECT " << o_name.c_str() << std::endl;
		listComponent.shrink_to_fit();
	}

	void Update()
	{
		//boucle sur les composants -> composant.update
		for (int i = 0; i < listComponent.size(); i++)
		{
			listComponent.at(i)->Update();
		}

		std::cout << "UPDATE OBJET " << o_name.c_str() << " TAG " << o_tag.c_str() << std::endl;
	}
};