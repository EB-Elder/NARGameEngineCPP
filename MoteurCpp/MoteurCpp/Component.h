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
	TYPE type = INVALID;
	std::string objectName = "";
	virtual ~Component() {};

	virtual void Update()=0;
};

struct Transform : public Component
{
private:
	float positionX, positionY, positionZ;
	float rotationX, rotationY, rotationZ;
	float scaleX, scaleY, scaleZ;
	glm::mat4 transformMatrix;

public:
	Transform(const Transform& copiedTransform)
	{
		transformMatrix = glm::mat4(1.0f);
		type = copiedTransform.type;

		positionX = copiedTransform.positionX;
		positionY = copiedTransform.positionY;
		positionZ = copiedTransform.positionZ;
		rotationX = copiedTransform.rotationX;
		rotationY = copiedTransform.rotationY;
		rotationZ = copiedTransform.rotationZ;
		scaleX = copiedTransform.scaleX;
		scaleY = copiedTransform.scaleY;
		scaleZ = copiedTransform.scaleZ;

		transformMatrix = copiedTransform.transformMatrix;
		type = copiedTransform.type;
	}

	Transform()
	{
		transformMatrix = glm::mat4(1.0f);
		type = TRANSFORM;

		positionX = 0.0f;
		positionY = 0.0f;
		positionZ = 0.0f;
		rotationX = 0.0f;
		rotationY = 0.0f;
		rotationZ = 0.0f;

		scaleX = 1.0f;
		scaleY = 1.0f;
		scaleZ = 1.0f;

		transformMatrix[0][0] = 1.0f;
		transformMatrix[0][1] = 0.0f;
		transformMatrix[0][2] = 0.0f;
		transformMatrix[0][3] = 0.0f;

		transformMatrix[1][0] = 0.0f;
		transformMatrix[1][1] = 1.0f;
		transformMatrix[1][2] = 0.0f;
		transformMatrix[1][3] = 0.0f;

		transformMatrix[2][0] = 0.0f;
		transformMatrix[2][1] = 0.0f;
		transformMatrix[2][2] = 1.0f;
		transformMatrix[2][3] = 0.0f;

		transformMatrix[3][0] = 0.0f;
		transformMatrix[3][1] = 0.0f;
		transformMatrix[3][2] = 0.0f;
		transformMatrix[3][3] = 1.0f;
	}

	Transform(float px, float py, float pz)
	{
		transformMatrix = glm::mat4(1.0f);
		type = TRANSFORM;

		positionX = px;
		positionY =	py;
		positionZ =	pz;

		rotationX = 0.0f;
		rotationY = 0.0f;
		rotationZ = 0.0f;

		scaleX = 1.0f;
		scaleY = 1.0f;
		scaleZ = 1.0f;

		transformMatrix[0][0] = 1.0f;
		transformMatrix[0][1] = 0.0f;
		transformMatrix[0][2] = 0.0f;
		transformMatrix[0][3] = px;

		transformMatrix[1][0] = 0.0f;
		transformMatrix[1][1] = 1.0f;
		transformMatrix[1][2] = 0.0f;
		transformMatrix[1][3] = py;

		transformMatrix[2][0] = 0.0f;
		transformMatrix[2][1] = 0.0f;
		transformMatrix[2][2] = 1.0f;
		transformMatrix[2][3] = pz;

		transformMatrix[3][0] = 0.0f;
		transformMatrix[3][1] = 0.0f;
		transformMatrix[3][2] = 0.0f;
		transformMatrix[3][3] = 1.0f;
	}

	~Transform()
	{
		std::cout << "DESTRUCTION COMPONENT TRANSFORM OF " << objectName.c_str() << std::endl;
	}

	void Update()
	{
		positionX = transformMatrix[0][3];
		positionY = transformMatrix[1][3];
		positionZ = transformMatrix[2][3];

		scaleX = transformMatrix[0][0];
		scaleY = transformMatrix[1][1];
		scaleZ = transformMatrix[2][2];

		std::cout << "UPDATE TRANSFORM COMPONENT OF " << objectName.c_str() << " in position (" << positionX << ", " << positionY << ", " << positionZ << ")" << std::endl;
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

	~Behavior()
	{
		std::cout << "DESTRUCTION COMPONENT BEHAVIOR OF " << objectName.c_str() << std::endl;
	}

	void Update()
	{
		std::cout << "UPDATE BEHAVIOR COMPONENT OF " << objectName.c_str() << std::endl;
	}
};