/*
-------------------------------------------------------------------------------
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Vector4 Studios <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

Application	:		Quasar Engine

Author		:		Rounak Paul
Email		:		paulrounak1999@gmail.com
Date		:		4th Dec 2023

Description	:		Camera class, contains methods related to various 
					transformations responsible for projection to camera space
-------------------------------------------------------------------------------
*/

#pragma once
#include "qspch.h"
#include <Core/Core.h>

namespace Quasar
{
	class QUASAR_API Camera
	{
	public:
		/// <summary>
		/// This function calculates the projection matrix based on the dimensions of the viewing frustum.
		/// The resulting matrix transforms a point in 3D space onto the 2D viewing plane.
		/// </summary>
		/// <param name="leftPlane">The left plane of the viewing frustum</param>
		/// <param name="rightPlane">The right plane of the viewing frustum</param>
		/// <param name="topPlane">The top plane of the viewing frustum</param>
		/// <param name="bottomPlane">The bottom plane of the viewing frustum</param>
		/// <param name="nearPlane">The near plane of the viewing frustum</param>
		/// <param name="farPlane">The far plane of the viewing frustum</param>
		void SetOrthographicsProjection(float leftPlane, float rightPlane, float topPlane, float bottomPlane, float nearPlane, float farPlane);

		/// <summary>
		/// This function sets the perspective projection for the camera.
		/// It calculates the projection matrix based on the field of view (fovy), aspect ratio (aspect), and the distances to the near and far clipping planes (nearPlane and farPlane).
		/// The resulting projection matrix transforms a 3D point in the camera's view volume to a 2D point in the normalized device coordinates.
		/// </summary>
		/// <param name="fovy">The field of view angle in the y direction</param>
		/// <param name="aspect">The aspect ratio, defined as width divided by height</param>
		/// <param name="nearPlane">The distance to the near clipping plane</param>
		/// <param name="farPlane">The distance to the far clipping plane</param>
		void SetPerspectiveProjection(float fovy, float aspect, float nearPlane, float farPlane);

		/// <summary>
		/// Sets the view direction for the camera.
		/// This function sets the view direction for the camera by calculating the view matrix.
		/// The view matrix is calculated using the position, direction, and up vectors.
		/// </summary>
		/// <param name="position">The position vector of the camera.</param>
		/// <param name="direction">The direction vector of the camera.</param>
		/// <param name="up">The up vector of the camera.</param>
		void SetViewDirection(glm::vec3 position, glm::vec3 direction, glm::vec3 up = glm::vec3{0.f, -1.f, 0.f});

		/// <summary>
		/// Sets the view target for the camera.
		/// This function sets the view target for the camera by calling the SetViewDirection function.
		/// </summary>
		/// <param name="position">The position vector of the camera.</param>
		/// <param name="target">The target vector of the camera.</param>
		/// <param name="up">The up vector of the camera.</param>
		void SetViewTarget(glm::vec3 position, glm::vec3 target, glm::vec3 up = glm::vec3{ 0.f, -1.f, 0.f });

		/// <summary>
		/// Sets the view direction for the camera using YXZ rotation.
		/// This function sets the view direction for the camera by calculating the view matrix.
		/// The view matrix is calculated using the position and rotation vectors.
		/// </summary>
		/// <param name="position">The position vector of the camera.</param>
		/// <param name="rotation">The rotation vector of the camera.</param>
		void SetViewYXZ(glm::vec3 position, glm::vec3 rotation);

		const glm::mat4& GetProjection() const { return projectionMatrix; }
		const glm::mat4& GetView() const { return viewMatrix; }

	private:
		glm::mat4 projectionMatrix{ 1.0f };
		glm::mat4 viewMatrix{ 1.0f };
	};
}


