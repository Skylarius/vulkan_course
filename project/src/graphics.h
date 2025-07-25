#pragma once

#include <vulkan/vulkan.h>
#include <glfw_window.h>
#include <vector>
#include <optional>

namespace veng {

class Graphics {
	public:
	Graphics(gsl::not_null<Window*> window);
	~Graphics();

	private:

	struct QueueFamilyIndices {
		std::optional<std::uint32_t> graphics_family = std::nullopt;
		std::optional<std::uint32_t> presentation_family = std::nullopt;
		bool IsValid() const { return graphics_family.has_value() /* && presentation_family.has_value() */; }
	};
	void InitializeVulkan();
	void CreateInstance();
	void SetupDebugMessenger();

	bool IsDeviceSuitable(VkPhysicalDevice device);

	// Device
	void PickPhysicalDevice();
	void CreateLogicalDeviceAndQueues();

	std::vector<gsl::czstring> GetRequiredInstanceExtensions();


	static gsl::span<gsl::czstring> GetSuggestedInstanceExtensions();
	static std::vector<VkExtensionProperties> GetSupportedInstanceExtensions();
	static bool AreAllExtensionsSupported(gsl::span<gsl::czstring> extensions);

	static std::vector<VkLayerProperties> GetSupportedValidationLayers();
	static bool AreAllLayersSupported(gsl::span<gsl::czstring> extensions);

	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

	std::vector<VkPhysicalDevice> GetAvailableDevices();

	VkInstance instance_ = VK_NULL_HANDLE;

	//Device
	VkPhysicalDevice physical_device_ = VK_NULL_HANDLE;
	VkDevice logical_device_ = VK_NULL_HANDLE;
	VkQueue graphics_queue_ = VK_NULL_HANDLE;
	VkDebugUtilsMessengerEXT debug_messenger_;
	gsl::not_null<Window*> window_;
	bool validation_enabled_ = false;
};

bool IsLayerSupported(const gsl::span<VkLayerProperties> properties, gsl::czstring name);

}  // namespace veng
