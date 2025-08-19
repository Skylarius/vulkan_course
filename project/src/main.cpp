#include <precomp.h>
#include <GLFW/glfw3.h>
#include <glfw_monitor.h>
#include <glfw_initialization.h>
#include <glfw_window.h>
#include <graphics.h>
#include <chrono>
#include <thread>

int main(std::size_t argc, gsl::zstring* argv)
{
	const veng::GlfwInitialization _glfw;  // resource acquisition in initialization

	veng::Window window("VulkanEngine", {800, 600});

	window.TryMoveToMonitor(0);

	veng::Graphics graphics(&window);

	std::array<veng::Vertex, 3> vertices = {
	    veng::Vertex{glm::vec3{0.0f, -0.5f, 0.0f}, glm::vec3{1.0f, 1.0f, 1.0f}},
		veng::Vertex{glm::vec3{0.5f, 0.5f, 0.0f}, glm::vec3{0.0f, 1.0f, 0.0f}},
	    veng::Vertex{glm::vec3{-0.5f, 0.5f, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f}}
	};

	veng::BufferHandle buffer = graphics.CreateVertexBuffer(vertices);

	while (!window.ShouldClose()) {
		glfwPollEvents();
		if (graphics.BeginFrame()) {
			graphics.RenderBuffer(buffer, vertices.size());
			graphics.EndFrame();
		}
	}

	graphics.DestroyVertexBuffer(buffer);

	return EXIT_SUCCESS;
}
