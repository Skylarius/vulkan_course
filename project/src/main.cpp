#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <gsl/gsl>
#include <GLFW/glfw3.h>

#include <glfw_initialization.h>

int main(std::size_t argc, gsl::zstring* argv)
{
	veng::GlfwInitialization _glfw; // resource acquisition in initialization

	gsl::not_null<GLFWwindow*> window = glfwCreateWindow(800, 600, "VulkanEngine", nullptr, nullptr);
	gsl::final_action _cleanup_window([window]() {
		glfwDestroyWindow(window);
	});

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}

	return EXIT_SUCCESS;
}
