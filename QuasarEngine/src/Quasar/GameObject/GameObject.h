#pragma once

#define CAMERA_SPACE 0
#define SCREEN_SPACE 1
#define WORLD_SPACE 2

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
		glm::mat4 mat4();

		glm::mat3 normalMatrix();
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

		int space = CAMERA_SPACE;

	private:
		GameObject(id_t objId) : id{objId} {}

		id_t id;
	};
}


