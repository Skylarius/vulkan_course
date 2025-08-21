#include <precomp.h>
#include <GLFW/glfw3.h>
#include <glfw_monitor.h>
#include <glfw_initialization.h>
#include <glfw_window.h>
#include <graphics.h>
#include <chrono>
#include <thread>
#include <glm/gtc/matrix_transform.hpp>

int main(std::size_t argc, gsl::zstring* argv)
{
	const veng::GlfwInitialization _glfw;  // resource acquisition in initialization

	veng::Window window("VulkanEngine", {800, 600});

	window.TryMoveToMonitor(0);

	veng::Graphics graphics(&window);

	std::array<veng::Vertex, 4> vertices = {
	    veng::Vertex({-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f}), // top left
	    veng::Vertex({0.5f, -0.5f, 0.0f}, {1.0f, 1.0f}), // top right
	    veng::Vertex({-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f}), // bottom -left
	    veng::Vertex({0.5f, 0.5f, 0.0f}, {1.0f, 0.0f}) // bottom -right
	};

	veng::BufferHandle vertex_buffer = graphics.CreateVertexBuffer(vertices);


	std::array<std::uint32_t, 6> indices = {0, 3, 2, 0, 1, 3 };

	veng::BufferHandle index_buffer = graphics.CreateIndexBuffer(indices);

	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.0f));
	glm::ivec2 window_size = window.GetWindowSize();
	glm::mat4 projection = glm::perspective(glm::radians(60.0f), float(window_size.x) / window_size.y, 0.1f, 100.0f);
	graphics.SetViewProjection(view, projection);


	while (!window.ShouldClose()) {
		glfwPollEvents();
		if (graphics.BeginFrame()) {
			graphics.RenderIndexedBuffer(vertex_buffer, index_buffer, indices.size());
			graphics.EndFrame();
		}
	}

	graphics.DestroyBuffer(vertex_buffer);
	graphics.DestroyBuffer(index_buffer);

	return EXIT_SUCCESS;
}
