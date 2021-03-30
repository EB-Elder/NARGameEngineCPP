#pragma once
#include "InfraStructure.h"

struct Input : public InfraStructure
{
	bool QuitButtonPressed = false;

	bool Initialize() final;

	void DeInitialize() final;

	// ce n'est pas une fonction virtuelle !
	void Update();

	bool GetQuitButtonState();
};