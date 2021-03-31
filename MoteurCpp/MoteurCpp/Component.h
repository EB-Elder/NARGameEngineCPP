#pragma once

#include <glm/gtc/matrix_transform.hpp> 
#include <iostream>

using Vector3f = glm::vec3;
using Matrix4f = glm::mat4;

enum TYPE:uint32_t
{
	INVALID,
	TRANSFORM,
	BEHAVIOR
};

struct Component
{
	Component() :type(TYPE::INVALID) {};
	Component(const Component&) = delete;
	TYPE type;
	virtual ~Component() {};

	virtual void Update()=0;
};

struct Transform : public Component
{
private:
	float positionX, positionY, positionZ;
	float rotationX, rotationY, rotationZ;
	float scaleX, scaleY, scaleZ;
	glm::mat4 transformMatrix = Matrix4f(1.0f);


public:
	Transform(const Transform& copiedTransform)
	{
		type = copiedTransform.type;
	}

	Transform()
	{
		type = TRANSFORM;
	}

	~Transform()
	{

	}

	void Update()
	{
		std::cout << "UPDATE TRANSFORM COMPONENT" << std::endl;
		positionX = transformMatrix[3][0];
		positionY = transformMatrix[3][1];
		positionZ = transformMatrix[3][2];

		scaleX = transformMatrix[0][0];
		scaleY = transformMatrix[1][1];
		scaleZ = transformMatrix[2][2];
	}

	void Translate(float newX, float newY, float newZ)
	{
		transformMatrix[3][0] = newX;
		transformMatrix[3][1] = newY;
		transformMatrix[3][2] = newZ;
	}

	void Rotation(float angleX, float angleY, float angleZ)
	{
		rotationX = angleX;
		rotationY = angleY;
		rotationZ = angleZ;
		if (angleX != 0)
		{
			transformMatrix = glm::rotate(transformMatrix, angleX, glm::vec3(1.0f, 0.0f, 0.0f));
		}

		if (angleY != 0)
		{
			transformMatrix = glm::rotate(transformMatrix, angleY, glm::vec3(0.0f, 1.0f, 0.0f));
		}

		if (angleZ != 0)
		{
			transformMatrix = glm::rotate(transformMatrix, angleZ, glm::vec3(0.0f, 0.0f, 1.0f));
		}
	}

	void Scale(float newX, float newY, float newZ)
	{
		transformMatrix[0][0] = newX;
		transformMatrix[1][1] = newY;
		transformMatrix[2][2] = newZ;
	}

	//friend std::ostream& operator<<(std::ostream& os, const Transform& tf);

};

/*std::ostream& operator<<(std::ostream& os, const Transform& tf)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			os << tf.transformMatrix[j][i] << " ";
		}
		os << std::endl;
	}
	os << std::endl;

	return os;
}*/


struct Behavior : public Component
{
	Behavior()
	{
		type = BEHAVIOR;
	}
};