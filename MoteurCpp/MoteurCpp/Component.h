#pragma once

enum TYPE
{
	TRANSFORM,
	BEHAVIOR
};

struct Component
{
	Component();
	TYPE type;
	virtual ~Component();
};

struct Transform : public Component
{
	Transform()
	{
		type = TRANSFORM;
	}
};

struct Behavior : public Component
{
	Behavior()
	{
		type = BEHAVIOR;
	}
};