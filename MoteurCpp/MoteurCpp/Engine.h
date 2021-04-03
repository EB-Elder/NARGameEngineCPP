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

	void Destroy();
	bool Initialize(std::vector<Object*>* listeObjet);
	void DeInitialize();

	//update les objets via un parallèlisme
	void Update(float deltaTime, int nbThread, std::vector<Object*>* listeObjet);

	void FixedUpdate(float deltaTime) {}
};

struct Engine : public InfraStructure
{
	// simple exemple, ou alors un vector ou une liste simplement chainee (intrusive) de systems
	EngineSystem* m_AIEngine;

	//Nombre de thread disponible 
	int nbThread;

	//liste des objets gérés par le moteur
	std::vector<Object*> listObject;

	Engine();

	//findObjet by tag
	vector<Object*> FindObjectsByTag(std::string tag);
	Object* FindObjectByName(std::string name);

	void ProcessSystems(double elapsedTime);

	bool Initialize() final;

	void DeInitialize() final;

	void Update(Context& context);

};
