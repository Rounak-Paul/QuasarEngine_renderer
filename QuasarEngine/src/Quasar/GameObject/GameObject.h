#pragma once
#include <Quasar/Model/Model.h>

namespace Quasar
{
	struct TransformComponent
	{
		glm::vec3 translate{};
		glm::vec3 scale{ 1.0f, 1.0f, 1.0f };
		glm::vec3 rotation{};

		/// <summary>
		///		<para>
		///			Matrix corresponds to translate * Ry * Rx * Rz * scale transformation
		///		</para> 
		///		<para>
		///			Rotation convention: tait-bryan angles with axis order Y(1), X(2), Z(3)
		///		</para>
		/// </summary>
		/// <returns>
		///		glm::mat4 transform
		/// </returns>
		glm::mat4 mat4() 
		{
			const float c3 = glm::cos(rotation.z);
			const float s3 = glm::sin(rotation.z);
			const float c2 = glm::cos(rotation.x);
			const float s2 = glm::sin(rotation.x);
			const float c1 = glm::cos(rotation.y);
			const float s1 = glm::sin(rotation.y);
			return glm::mat4
			{
				{
					scale.x * (c1 * c3 + s1 * s2 * s3),
					scale.x * (c2 * s3),
					scale.x * (c1 * s2 * s3 - c3 * s1),
					0.0f,
				},
				{
					scale.y * (c3 * s1 * s2 - c1 * s3),
					scale.y * (c2 * c3),
					scale.y * (c1 * c3 * s2 + s1 * s3),
					0.0f,
				},
				{
					scale.z * (c2 * s1),
					scale.z * (-s2),
					scale.z * (c1 * c2),
					0.0f,
				},
				{translate.x, translate.y, translate.z, 1.0f}
			};
		}
	};

	class GameObject
	{
	public:
		using id_t = unsigned int;

		static GameObject CreateGameObject()
		{
			static id_t currentId = 0;
			return GameObject(currentId++);
		}

		GameObject(const GameObject&) = delete;
		GameObject& operator=(const GameObject&) = delete;
		GameObject(GameObject&&) = default;
		GameObject& operator=(GameObject&&) = default;

		const id_t GetId() { return id; }

		std::shared_ptr<Model> model{};
		glm::vec3 color{};
		TransformComponent transform{};

	private:
		GameObject(id_t objId) : id{objId} {}

		id_t id;
	};
}


