#pragma once
#include "InfraStructure.h"
#include "Object.h"
#include <thread>
using namespace std;

// "forward declaration" d'une structure qui elle meme reference des classes
	// qui ne sont pas encore definies (fonctionne ici car il s'agit de pointeurs,
	// seul le typage interesse le compilateur dans ce cas)	
struct Context;

struct EngineSystem
{
	double targetFrameRate = 1.0 / 60.0;
	double accumulatedTime = 0.0;
	int maxIterations = 2;
	int threadDispo;
	
	vector<std::thread> fork;


	bool Create(int nbThread, vector<Object*>* listeObjet);

	void Destroy() {}
	bool Initialize() { return true; }
	void DeInitialize() {}

	//update les objets via un parall�lisme
	void Update(float deltaTime) 
	{

	}

	bool traitement(int balise1, int balise2);

	void FixedUpdate(float deltaTime) {}
};

struct Engine : public InfraStructure
{
	// simple exemple, ou alors un vector ou une liste simplement chainee (intrusive) de systems
	EngineSystem* m_AIEngine;

	//Nombre de thread disponible 
	int nbThread;

	//liste des objets g�r�s par le moteur
	std::vector<Object*> listObject;

	Engine();


	void ProcessSystems(double elapsedTime);

	// ---

	bool Initialize() final;

	void DeInitialize() final;

	// ce n'est pas une fonction virtuelle !
	void Update(Context& context);

};