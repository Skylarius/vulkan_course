#pragma once

#include <vulkan/vulkan.h>
#include <glfw_window.h>
#include <vector>
#include <optional>
#include <vertex.h>
#include <buffer_handle.h>
#include <texture_handle.h>

namespace veng {

struct Frame {
	VkSemaphore image_available_signal = VK_NULL_HANDLE;
	VkFence still_rendering_fence = VK_NULL_HANDLE;

	VkCommandBuffer command_buffer = VK_NULL_HANDLE;

	VkDescriptorSet uniform_set = VK_NULL_HANDLE;
	BufferHandle uniform_buffer;
	void* uniform_buffer_location = nullptr;
};

class Graphics {
	public:
	Graphics(gsl::not_null<Window*> window);
	~Graphics();

	private:
	struct QueueFamilyIndices {
		std::optional<std::uint32_t> graphics_family = std::nullopt;
		std::optional<std::uint32_t> presentation_family = std::nullopt;
		bool IsValid() const { return graphics_family.has_value() && presentation_family.has_value(); }
	};

	struct SwapChainProperties {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> present_modes;

		bool IsValid() const { return !formats.empty() && !present_modes.empty(); }
	};

	void InitializeVulkan();

	// Initialization
	void CreateInstance();
	void SetupDebugMessenger();
	void PickPhysicalDevice();
	void CreateLogicalDeviceAndQueues();
	void CreateSurface();
	void CreateSwapChain();
	void CreateImageViews();
	void CreateRenderPass();
	void CreateGraphicsPipeline();
	void CreateFramebuffers();
	void CreateCommandPool();
	void CreateCommandBuffer();
	void CreateSignals();
	void CreateDescriptorSetLayout();
	void CreateDescriptorPools();
	void CreateDescriptorSets();
	void CreateTextureSampler();
	void CreateDepthResources();

	void RecreateSwapChain();
	void CleanupSwapChain();

	// Rendering

	public:
	bool BeginFrame();
	void SetModelMatrix(glm::mat4 model);
	void SetViewProjection(glm::mat4 view, glm::mat4 projection);
	void SetTexture(TextureHandle handle);
	TextureHandle CreateImage(glm::ivec2 size, VkFormat image_format, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
	void TransitionImageLayout(VkImage image, VkImageLayout old_layout, VkImageLayout new_layout);
	void CopyBufferToImage(VkBuffer buffer, VkImage image, glm::ivec2 size);
	VkImageView CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspect_flag);
	void RenderBuffer(BufferHandle handle, std::uint32_t vertex_count);
	void RenderIndexedBuffer(BufferHandle vertex_buffer, BufferHandle index_buffer, std::uint32_t index_count);
	void EndFrame();

	BufferHandle CreateVertexBuffer(gsl::span<Vertex> vertices);
	BufferHandle CreateIndexBuffer(gsl::span<std::uint32_t> indices);
	void DestroyBuffer(BufferHandle handle);
	TextureHandle CreateTexture(gsl::czstring path);
	void DestroyTexture(TextureHandle handle);

	private:
	void BeginCommands();
	void EndCommands();

	std::vector<gsl::czstring> GetRequiredInstanceExtensions();

	static gsl::span<gsl::czstring> GetSuggestedInstanceExtensions();
	static std::vector<VkExtensionProperties> GetSupportedInstanceExtensions();
	static bool AreAllExtensionsSupported(gsl::span<gsl::czstring> extensions);

	static std::vector<VkLayerProperties> GetSupportedValidationLayers();
	static bool AreAllLayersSupported(gsl::span<gsl::czstring> extensions);

	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
	SwapChainProperties GetSwapChainProperties(VkPhysicalDevice device);
	bool IsDeviceSuitable(VkPhysicalDevice device);
	std::vector<VkPhysicalDevice> GetAvailableDevices();
	bool AreAllDeviceExtensionsSupported(VkPhysicalDevice device);
	std::vector<VkExtensionProperties> GetDeviceAvailableExtensions(VkPhysicalDevice device);

	VkSurfaceFormatKHR ChooseSwapSurfaceFormat(std::span<VkSurfaceFormatKHR> formats);
	VkPresentModeKHR ChooseSwapPresentMode(std::span<VkPresentModeKHR> modes);
	VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR capabilities);
	std::uint32_t ChooseSwapImageCount(const VkSurfaceCapabilitiesKHR& capabilities);

	VkShaderModule CreateShaderModule(gsl::span<std::uint8_t> buffer);
	VkViewport GetViewport();
	VkRect2D GetScissor();

	std::uint32_t FindMemoryType(std::uint32_t type_bits_filter, VkMemoryPropertyFlags required_properties);

	BufferHandle CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
	VkCommandBuffer BeginTransientCommandBuffer();
	void EndTransientCommandBuffer(VkCommandBuffer command_buffer);
	void CreateUniformBuffers();

	std::array<gsl::czstring, 1> required_device_extensions_ = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

	VkInstance instance_ = VK_NULL_HANDLE;

	// Device
	VkPhysicalDevice physical_device_ = VK_NULL_HANDLE;
	VkDevice logical_device_ = VK_NULL_HANDLE;
	VkQueue graphics_queue_ = VK_NULL_HANDLE;
	VkQueue presentation_queue_ = VK_NULL_HANDLE;
	VkDebugUtilsMessengerEXT debug_messenger_;

	VkSurfaceKHR surface_ = VK_NULL_HANDLE;
	VkSwapchainKHR swap_chain_ = VK_NULL_HANDLE;
	VkSurfaceFormatKHR surface_format_;
	VkPresentModeKHR present_mode_;
	VkExtent2D extent_;
	std::vector<VkImage> swap_chain_images_;
	std::vector<VkImageView> swap_chain_image_views_;
	std::vector<VkFramebuffer> swap_chain_framebuffers_;
	std::vector<VkSemaphore> render_finished_signals;

	VkPipelineLayout pipeline_layout_ = VK_NULL_HANDLE;
	VkRenderPass render_pass_ = VK_NULL_HANDLE;
	VkPipeline pipeline_ = VK_NULL_HANDLE;

	VkCommandPool command_pool_ = VK_NULL_HANDLE;

	std::uint32_t current_image_index_ = 0;

	VkDescriptorSetLayout uniform_set_layout_ = VK_NULL_HANDLE;
	VkDescriptorPool uniform_pool_ = VK_NULL_HANDLE;

	VkDescriptorSetLayout texture_set_layout_ = VK_NULL_HANDLE;
	VkDescriptorPool texture_pool_ = VK_NULL_HANDLE;
	VkSampler texture_sampler_ = VK_NULL_HANDLE;
	TextureHandle depth_texture_;

	std::array<Frame, MAX_BUFFERED_FRAMES> frames_;
	std::int32_t current_frame_ = 0;

	gsl::not_null<Window*> window_;
	bool validation_enabled_ = false;
};

bool IsLayerSupported(const gsl::span<VkLayerProperties> properties, gsl::czstring name);

}  // namespace veng
