#include <iostream>
#include <jgpu/jgpu.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

int main()
{
	if (!glfwInit())
	{
		return -1;
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Example App", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	auto factory = jgpu::CreateFactory(jgpu::GraphicsAPI::DirectX12);
	if (!factory)
	{
		std::cerr << factory.error() << std::endl;
		return -1;
	}

	auto instance = (*factory)->CreateInstance(true);
	if (!instance)
	{
		std::cerr << instance.error() << std::endl;
		return -1;
	}

	auto adapter = (*instance)->FindAdapter();
	if (!adapter)
	{
		std::cerr << adapter.error() << std::endl;
		return -1;
	}

	auto device = (*adapter)->CreateDevice();
	if (!device)
	{
		std::cerr << device.error() << std::endl;
		return -1;
	}

	auto graphicsQueue = (*device)->CreateQueue(jgpu::QueueType::Graphics);
	if (!graphicsQueue)
	{
		std::cerr << graphicsQueue.error() << std::endl;
		return -1;
	}

	jgpu::SwapchainSpecification swapchainSpec{};
	swapchainSpec.width = 1280;
	swapchainSpec.height = 720;
	swapchainSpec.bufferCount = 2;
	swapchainSpec.windowHandle = glfwGetWin32Window(window);

	auto swapchain = (*instance)->CreateSwapchain(*(*graphicsQueue), swapchainSpec);
	if (!swapchain)
	{
		std::cerr << swapchain.error() << std::endl;
		return -1;
	}

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}