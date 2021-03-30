#include "Engine.h"

// par contre lors de la definition de la fonction il faut une implementation complete
#include "Context.h"
#include "Timer.h"
#include <iostream>
#include <thread>



Engine::Engine() {

	nbThread = thread::hardware_concurrency();

}

void Engine::ProcessSystems(double elapsedTime)
{
	EngineSystem& system = *m_AIEngine;

	system.accumulatedTime += elapsedTime;

	float deltaTime = static_cast<float>(elapsedTime);

	system.Update(deltaTime);

	int loops = system.maxIterations;
	// on sort de la boucle des que l'un des deux tests est faux
	while ((system.accumulatedTime > system.targetFrameRate) && (loops > 0))
	{
		system.accumulatedTime -= system.targetFrameRate;

		// alternativement on pourrait recalculer le deltaTime a chaque tour de boucle
		// et rappeler Update() si loops < system.maxIterations

		system.FixedUpdate(static_cast<float>(system.targetFrameRate));

		--loops;
	}
}

bool Engine::Initialize()
{
#if defined(_DEBUG)
	m_DebugName = "Engine";
#endif

	// Les systemes pourraient etre cree de facon data-driven, plugins, ou en dur
	EngineSystem* system = new EngineSystem;
	system->Create(thread::hardware_concurrency(), &listObject);
	system->Initialize();

	m_AIEngine = system;

	std::cout << "[Engine] initialized\n";

	return true;
}

void Engine::DeInitialize()
{
	// libere et detruit les systems
	m_AIEngine->DeInitialize();
	m_AIEngine->Destroy();

	std::cout << "[Engine] deinitialized\n";
}

// ce n'est pas une fonction virtuelle !
void Engine::Update(Context& context)
{
	std::cout << "[Engine] update\n";

	double elapsedTime = context.clock.ElapsedTime;

	// tout lag est maximise 100 ms (1/10 de seconde)
	// cela permet d'eviter de faire sauter le moteur en cas de breakpoint ou lag enorme
	// alternativement on peut appliquer une correction en extrapolant a partir du temps ecoule 
	if (elapsedTime > 0.10)
		elapsedTime = 0.10;

	ProcessSystems(elapsedTime);
}

bool EngineSystem::Create(int nbThread, std::vector<Object*>* listeObjet) {

	int threadNbObject = listeObjet->size();

	for (int i = 0; i < nbThread; i++) {

		fork.push_back(std::thread(&EngineSystem::traitement, i * threadNbObject, (i * threadNbObject) + threadNbObject));
	
	}


}

bool EngineSystem::traitement(int balise1, int balise2) {

	return true;

}