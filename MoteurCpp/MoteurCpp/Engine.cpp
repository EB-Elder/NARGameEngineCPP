#include "Engine.h"
#include "Context.h"
#include "Timer.h"
#include "Object.h"
#include <iostream>
#include <thread>
#include <vector>


Engine::Engine() {

	nbThread = thread::hardware_concurrency();

}

void Engine::ProcessSystems(double elapsedTime)
{
	EngineSystem& system = *m_AIEngine;

	system.accumulatedTime += elapsedTime;

	float deltaTime = static_cast<float>(elapsedTime);

	system.Update(deltaTime, nbThread, &listObject);

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
	system->Initialize(&listObject);

	m_AIEngine = system;

	std::cout << "[Engine] initialized\n";

	return true;
}

void Engine::DeInitialize()
{
	// libere et detruit les systems
	m_AIEngine->DeInitialize();
	m_AIEngine->Destroy();

	for (int i = 0; i < listObject.size(); i++)
	{
		listObject[i]->DeInitialize();
		listObject[i]->Destroy();
	}

	listObject.clear();
	listObject.shrink_to_fit();

	std::cout << "[Engine] deinitialized\n";
}

void EngineSystem::DeInitialize()
{
	fork.clear();
}

void EngineSystem::Destroy()
{
	fork.shrink_to_fit();
}

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

vector<Object*> Engine::FindObjectsByTag(std::string tag)
{
	int nbObj = 0;
	for (int i = 0; i < listObject.size(); i++)
	{
		if (listObject[i]->o_tag == tag) nbObj++;
	}

	std::vector<Object*> res(nbObj);
	for (int i = 0; i < listObject.size(); i++)
	{
		if (listObject[i]->o_tag == tag)
		{
			res.push_back(listObject[i]);
		}
	}

	return res;
}

Object* Engine::FindObjectByName(std::string name)
{
	for (int i = 0; i < listObject.size(); i++)
	{
		if (listObject[i]->o_name == name)
		{
			return listObject[i];
		}
	}

	return nullptr;
}

bool EngineSystem::Create(int nbThread, std::vector<Object*>* listeObjet)
{
	int nbObjsPerThread = listeObjet->size() / nbThread;

	//si on a moins d'objets que de threads
	if (nbObjsPerThread < 1)
	{
		for (int i = 0; i < nbObjsPerThread; i++)
		{
			fork.push_back(std::thread([this, listeObjet](int balise1, int balise2)
			{
				//traitement create
				for (int j = balise1; j < balise2; j++)
				{
					listeObjet->at(j)->Create();
				}

			}, i, i + 1));
		}
	}
	else
	{
		//si le nombre d'objets n'est pas divisible entièrement par le nombre de threads
		if (listeObjet->size() % nbThread != 0)
		{
			int reste = listeObjet->size() % nbThread;

			for (int i = 0; i < nbThread - 1; i++)
			{
				fork.push_back(std::thread([this, listeObjet](int balise1, int balise2)
				{
					//traitement create
					for (int j = balise1; j < balise2; j++)
					{
						listeObjet->at(j)->Create();
					}

				}, i * nbObjsPerThread, i * (nbObjsPerThread + 1)));
			}

			//le dernier thread aura le reste à traiter en plus
			fork.push_back(std::thread([this, listeObjet](int balise1, int balise2)
			{
				//traitement create
				for (int j = balise1; j < balise2; j++)
				{
					listeObjet->at(j)->Create();
				}

			}, (nbThread - 1) * nbObjsPerThread, (nbThread - 1) * (nbObjsPerThread + 1) + reste));
		}
		else
		{
			for (int i = 0; i < nbThread; i++)
			{
				fork.push_back(std::thread([this, listeObjet](int balise1, int balise2)
				{
					//traitement create
					for (int j = balise1; j < balise2; j++)
					{
						listeObjet->at(j)->Create();
					}

				}, i * nbObjsPerThread, i * (nbObjsPerThread + 1)));
			}
		}
	}

	for (int i = 0; i < fork.size(); i++)
	{
		fork[i].join();
	}

	return true;
}

void EngineSystem::Update(float deltaTime, int nbThread, std::vector<Object*>* listeObjet)
{
	int nbObjsPerThread = listeObjet->size() / nbThread;
	
	//si on a moins d'objets que de threads
	if (nbObjsPerThread < 1)
	{
		for (int i = 0; i < listeObjet->size(); i++)
		{
			fork.push_back(std::thread([this, listeObjet](int balise1, int balise2)
			{
				//traitement update
				for (int j = balise1; j < balise2; j++)
				{
					listeObjet->at(j)->Update();
				}

			}, i, i + 1));
		}
	}
	else
	{
		//si le nombre d'objets n'est pas divisible entièrement par le nombre de threads
		if (listeObjet->size() % nbThread != 0)
		{
			int reste = listeObjet->size() % nbThread;

			for (int i = 0; i < nbThread - 1; i++)
			{
				fork.push_back(std::thread([this, listeObjet](int balise1, int balise2)
				{
					//traitement update
					for (int j = balise1; j < balise2; j++)
					{
						listeObjet->at(j)->Update();
					}

				}, i * nbObjsPerThread, i * (nbObjsPerThread + 1)));
			}

			//le dernier thread aura le reste à traiter en plus
			fork.push_back(std::thread([this, listeObjet](int balise1, int balise2)
			{
				//traitement update
				for (int j = balise1; j < balise2; j++)
				{
					listeObjet->at(j)->Update();
				}

			}, (nbThread - 1) * nbObjsPerThread, (nbThread - 1) * (nbObjsPerThread + 1) + reste));
		}
		else
		{
			for (int i = 0; i < nbThread; i++)
			{
				fork.push_back(std::thread([this, listeObjet](int balise1, int balise2)
				{
					//traitement update
					for (int j = balise1; j < balise2; j++)
					{
						listeObjet->at(j)->Update();
					}

				}, i * nbObjsPerThread, i * (nbObjsPerThread + 1)));
			}
		}
	}

	for (int i = 0; i < fork.size(); i++)
	{
		fork[i].join();
	}

	fork.clear();
}

bool EngineSystem::Initialize(std::vector<Object*>* listeObjet)
{
	for (int i = 0; i < listeObjet->size(); i++)
	{
		listeObjet->at(i)->Create();
	}

	return true;
}
