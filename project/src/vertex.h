#pragma once

#include <vulkan/vulkan.h>

namespace veng {
struct Vertex {

	Vertex() : position(glm::vec3(0.0f)), uv(glm::vec2(0.0f)) {}
	Vertex(glm::vec3 _position, glm::vec2 _uv) : position(_position), uv(_uv) {}

	glm::vec3 position;
	glm::vec2 uv;

	static VkVertexInputBindingDescription GetBindingDescription() {
		VkVertexInputBindingDescription binding_description = {};
		binding_description.binding = 0;
		binding_description.stride = sizeof(Vertex);
		binding_description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		return binding_description;
	}

	static std::array<VkVertexInputAttributeDescription, 2> GetAttributeDescriptions() {
		std::array<VkVertexInputAttributeDescription, 2> attribute_descriptions = {};
		attribute_descriptions[0].binding = 0;
		attribute_descriptions[0].location = 0;
		attribute_descriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attribute_descriptions[0].offset = offsetof(Vertex, position);

		attribute_descriptions[1].binding = 0;
		attribute_descriptions[1].location = 1;
		attribute_descriptions[1].format = VK_FORMAT_R32G32_SFLOAT;
		attribute_descriptions[1].offset = offsetof(Vertex, uv);
		
		return attribute_descriptions;
	}
};
}  // namespace veng
