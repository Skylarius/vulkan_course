#include <precomp.h>
#include <GLFW/glfw3.h>
#include <glfw_monitor.h>
#include <glfw_initialization.h>
#include <glfw_window.h>
#include <graphics.h>
#include <chrono>
#include <thread>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>
#include <thread>

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

	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.0f));
	glm::ivec2 window_size = window.GetWindowSize();
	glm::mat4 projection = glm::perspective(glm::radians(60.0f), float(window_size.x) / window_size.y, 0.1f, 100.0f);
	graphics.SetViewProjection(view, projection);
	veng::TextureHandle texture = graphics.CreateTexture("paving-stones.jpg");

	// PERSONAL: FRAMERATE LIMIT
	const std::float_t frame_rate = 60.0f;
	const long long frame_time_nanoseconds = static_cast<long long>(1'000'000'000 / frame_rate);
	long long time_begin, time_end;


	while (!window.ShouldClose()) {
		glfwPollEvents();
		if (graphics.BeginFrame()) {
			time_begin = std::chrono::high_resolution_clock::now().time_since_epoch().count();
			graphics.SetTexture(texture);
			//graphics.RenderIndexedBuffer(vertex_buffer, index_buffer, indices.size());

			graphics.SetModelMatrix(rotation);
			rotation = glm::rotate(rotation, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			graphics.RenderIndexedBuffer(vertex_buffer, index_buffer, indices.size());
			time_end = std::chrono::high_resolution_clock::now().time_since_epoch().count();
			std::this_thread::sleep_for(std::chrono::nanoseconds(std::clamp(frame_time_nanoseconds - (time_end - time_begin), 0LL, frame_time_nanoseconds)));
			graphics.EndFrame();
			graphics.SetViewProjection(view, projection);
		}
	}
	graphics.DestroyTexture(texture);
	graphics.DestroyBuffer(vertex_buffer);
	graphics.DestroyBuffer(index_buffer);

	return EXIT_SUCCESS;
}
