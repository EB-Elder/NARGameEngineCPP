#include <iostream>
#include "Object.h"
#include "Timer.h"
#include "Input.h"
#include "Engine.h"
#include "Context.h"
#include "Utils.h"
#include <iostream>
#include <vector>
#include <thread>

void OneTimeEvent()
{
	std::cout << "One Time Event\n";
}

void RecurringTimeEvent()
{
	std::cout << "Recurring Time Event\n";
}

Clock& Context::Clock() const { return clock; }
Input& Context::Input() const { return input; }
Engine& Context::Engine() const { return engine; }

struct Application
{
	std::vector<Object*> listObj;
	std::vector<InfraStructure*> cores;

	Context& engine_context;
	uint64_t frameCpt = 0;
	bool quit = false;

	//constructeurs
	Application(Context& context) : engine_context(context) {}
	Application() : Application(Application::CreateContext()) {}
	Application(Application& app) = delete;

	void Update()
	{
		// Ici le role et l'ordre de chaque classe est bien defini 

		engine_context.Clock().Update();

		engine_context.Input().Update();

		engine_context.Engine().Update(engine_context);
	}

	void Run()
	{
		bool createOk = Create();

		if(createOk) createOk = Initialization();
		else
		{
			std::cout << "ERREUR CREATION SOUS SYSTEMES" << std::endl;
		}

		if (createOk)
		{
			while (quit == false)
			{
				std::cout << "[Application] frame # " << frameCpt << std::endl;

				Update();

				// emule un delai de traitement (une synchro verticale par ex.)
				std::this_thread::sleep_for(std::chrono::milliseconds(10));

				quit = engine_context.Input().QuitButtonPressed;

				frameCpt++;
			}
		}
		else
		{
			std::cout << "ERREUR INITIALISATION" << std::endl;
		}

		//Déinitialisation
		DeInitialisation();

		//libération de la mémoire
		Destroy();
	}

	bool Create()
	{
		// l'ordre peut etre important si c'est l'ordre d'update
		cores.reserve(3);
		cores.emplace_back(&engine_context.clock);
		cores.emplace_back(&engine_context.input);
		cores.emplace_back(&engine_context.engine);

		return true;
	}

	static Context& CreateContext()
	{
		Clock* clock = new Clock;
		Input* input = new Input;
		Engine* engine = new Engine;

		static Context context(*clock, *input, *engine);
		return context;
	}

	//initialiser les sous-systèmes
	bool Initialization()
	{
		bool allOk = true;
		for (auto * core : cores)
		{
			allOk &= core->Initialize();
		}

		Timer timer1{ 9.0, 0.0, false };
		engine_context.Clock().AddTimer(timer1, &OneTimeEvent);

		Timer timer2{ 5.0, 0.0, true };
		engine_context.Clock().AddTimer(timer2, &RecurringTimeEvent);

		return allOk;
	}

	void DeInitialisation()
	{
		for (auto * core : make_reverse(cores)) 
		{
			core->DeInitialize();
		}
	}

	void Destroy()
	{
		//destruction des sous systèmes
		for (auto* core : make_reverse(cores))
		{
			std::cout << "DESTRUCTION CORE " << core->DebugName().c_str() << std::endl;
			delete core;
		}

		cores.clear();
		cores.shrink_to_fit();
	}
};


int main()
{
	Application gameEngine;

	Object o("Cube", "object", 0.0f, 1.0f, 5.0f);
	Object o2("Camera", "camera", 0.0f, 0.0f, 0.0f);

	gameEngine.engine_context.engine.listObject.push_back(&o);
	gameEngine.engine_context.engine.listObject.push_back(&o2);

	gameEngine.Run();

	return 0;
}

