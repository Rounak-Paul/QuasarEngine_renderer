#pragma once
#include "qspch.h"

namespace Quasar
{
	class Camera
	{
	public:
		void SetOrthographicsProjection(float leftPlane, float rightPlane, float topPlane, float bottomPlane, float nearPlane, float farPlane);

		void SetPerspectiveProjection(float fovy, float aspect, float nearPlane, float farPlane);

		void SetViewDirection(glm::vec3 position, glm::vec3 direction, glm::vec3 up = glm::vec3{0.f, -1.f, 0.f});
		void SetViewTarget(glm::vec3 position, glm::vec3 target, glm::vec3 up = glm::vec3{ 0.f, -1.f, 0.f });
		void SetViewYXZ(glm::vec3 position, glm::vec3 rotation);

		const glm::mat4& GetProjection() const { return projectionMatrix; }
		const glm::mat4& GetView() const { return viewMatrix; }

	private:
		glm::mat4 projectionMatrix{ 1.0f };
		glm::mat4 viewMatrix{ 1.0f };
	};
}


