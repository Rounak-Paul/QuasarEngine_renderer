#pragma once
#include "qspch.h"
#include <Quasar/RenderSystem/Device.h>

namespace Quasar 
{

	class Model
	{
	public:

		struct Vertex
		{
			glm::vec3 position;
			glm::vec3 color;

			static std::vector<VkVertexInputBindingDescription> GetBindingDescriptions();
			static std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions();
		};

		Model(Device& device, const std::vector<Vertex>& vertices);
		~Model();

		Model(const Model&) = delete;
		Model &operator=(const Model&) = delete;

		void Bind(VkCommandBuffer commandBuffer);
		void Draw(VkCommandBuffer commandBuffer);

	private:
		void CreateVertexBuffers(const std::vector<Vertex>& vertices);

		Device& qsDevice;
		VkBuffer vertexBuffer;
		VkDeviceMemory vertexBufferMemory;
		uint32_t vertexCount;
	};
}



