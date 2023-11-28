#include "qspch.h"
#include "Camera.h"

namespace Quasar
{
	void Camera::SetOrthographicsProjection(float leftPlane, float rightPlane, float topPlane, float bottomPlane, float nearPlane, float farPlane)
	{
		projectionMatrix = glm::mat4{ 1.0f };
		projectionMatrix[0][0] = 2.f / (rightPlane - leftPlane);
		projectionMatrix[1][1] = 2.f / (bottomPlane - topPlane);
		projectionMatrix[2][2] = 1.f / (farPlane - nearPlane);
		projectionMatrix[3][0] = -(rightPlane + leftPlane) / (rightPlane - leftPlane);
		projectionMatrix[3][1] = -(bottomPlane + topPlane) / (bottomPlane - topPlane);
		projectionMatrix[3][2] = -nearPlane / (farPlane - nearPlane);
	}

	void Camera::SetPerspectiveProjection(float fovy, float aspect, float nearPlane, float farPlane)
	{
		assert(glm::abs(aspect - std::numeric_limits<float>::epsilon()) > 0.0f);
		const float tanHalfFovy = tan(fovy / 2.f);
		projectionMatrix = glm::mat4{ 0.0f };
		projectionMatrix[0][0] = 1.f / (aspect * tanHalfFovy);
		projectionMatrix[1][1] = 1.f / (tanHalfFovy);
		projectionMatrix[2][2] = farPlane / (farPlane - nearPlane);
		projectionMatrix[2][3] = 1.f;
		projectionMatrix[3][2] = -(farPlane * nearPlane) / (farPlane - nearPlane);
	}
}
