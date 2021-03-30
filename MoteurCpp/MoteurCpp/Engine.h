#pragma once
#include "InfraStructure.h"
#include "Object.h"

// "forward declaration" d'une structure qui elle meme reference des classes
	// qui ne sont pas encore definies (fonctionne ici car il s'agit de pointeurs,
	// seul le typage interesse le compilateur dans ce cas)	
struct Context;

struct EngineSystem
{
	double targetFrameRate = 1.0 / 60.0;
	double accumulatedTime = 0.0;
	int maxIterations = 2;

	bool Create() 
	{ 
		std::cout << "CREATE SUB SYSTEM" << std::endl;
		return true;
	}
	void Destroy() {}
	bool Initialize() { return true; }
	void DeInitialize() {}

	//update les objets via un parallèlisme
	void Update(float deltaTime) 
	{

	}

	void FixedUpdate(float deltaTime) {}
};

struct Engine : public InfraStructure
{
	// simple exemple, ou alors un vector ou une liste simplement chainee (intrusive) de systems
	EngineSystem* m_AIEngine;

	//liste des objets gérés par le moteur


	void ProcessSystems(double elapsedTime);

	// ---

	bool Initialize() final;

	void DeInitialize() final;

	// ce n'est pas une fonction virtuelle !
	void Update(Context& context);

};