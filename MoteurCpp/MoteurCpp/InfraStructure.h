#pragma once
#include <string>

struct InfraStructure
{
#if defined(_DEBUG)
	std::string m_DebugName;
	const std::string& DebugName() { return m_DebugName; }
#endif

	// on pourrait egalement ajouter des fonctions Create() & Destroy() 
	// si l'on souhaite controler les allocations memoires des classes "cores"

	virtual bool Initialize() = 0;
	virtual void DeInitialize() = 0;

};