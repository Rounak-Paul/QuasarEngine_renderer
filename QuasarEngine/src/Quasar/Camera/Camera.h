#pragma once
#include "qspch.h"

namespace Quasar
{
	class Camera
	{
	public:
		void SetOrthographicsProjection(float leftPlane, float rightPlane, float topPlane, float bottomPlane, float nearPlane, float farPlane);

		void SetPerspectiveProjection(float fovy, float aspect, float nearPlane, float farPlane);

		const glm::mat4& GetProjection() const { return projectionMatrix; }

	private:
		glm::mat4 projectionMatrix{ 1.0f };
	};
}


