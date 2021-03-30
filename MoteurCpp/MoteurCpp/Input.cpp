#include "Input.h"

// pour quitter la boucle : a ne pas utiliser dans une vraie application
#include <conio.h>
#include <iostream>

bool Input::Initialize()
{
#if defined(_DEBUG)
	m_DebugName = "Input";
#endif
	std::cout << "[Input] initialized\n";
	return true;
}

void Input::DeInitialize()
{
	std::cout << "[Input] deinitialized\n";
}

// ce n'est pas une fonction virtuelle !
void Input::Update()
{
	QuitButtonPressed = GetQuitButtonState();
	std::cout << "[Input] update\n";
}

bool Input::GetQuitButtonState()
{
	if (_kbhit())
	{
		int ch = _getch();
		if (ch == 27)			// ESC 
			return true;
	}
	return false;
}