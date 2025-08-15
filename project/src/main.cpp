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

	while (!window.ShouldClose()) {
		glfwPollEvents();
		if (graphics.BeginFrame())
		{
			graphics.RenderTriangle();
			graphics.EndFrame();
		}
	}

	return EXIT_SUCCESS;
}
