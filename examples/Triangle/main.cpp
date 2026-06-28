#include <iostream>
#include <vector>
#include <jgpu/jgpu.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <type_traits>

template<class T>
T UnwrapOrExit(jgpu::JResult<T>&& result)
{
	if (!result)
	{
		std::cerr << result.error() << std::endl;
		std::exit(-1);
	}

	return std::move(result.value());
}

void UnwrapOrExit(jgpu::JVoidResult&& result)
{
	if (!result)
	{
		std::cerr << result.error() << std::endl;
		std::exit(-1);
	}
}

static constexpr uint32_t WINDOW_WIDTH = 1280;
static constexpr uint32_t WINDOW_HEIGHT = 720;
static constexpr uint32_t DOUBLE_BUFFERING = 2;

struct FrameResource
{
	jgpu::JPtr<jgpu::CommandEncoder> cmdEncoder;
};

int main()
{
	if (!glfwInit()) return -1;
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Example App", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	auto factory = UnwrapOrExit(jgpu::CreateFactory(jgpu::GraphicsAPI::DirectX12));
	auto instance = UnwrapOrExit(factory->CreateInstance());
	auto adapter = UnwrapOrExit(instance->FindAdapter());
	auto device = UnwrapOrExit(adapter->CreateDevice());
	auto graphicsQueue = UnwrapOrExit(device->CreateQueue(jgpu::QueueType::Graphics));

	jgpu::SwapchainSpecification swapchainSpec{};
	swapchainSpec.width = WINDOW_WIDTH;
	swapchainSpec.height = WINDOW_HEIGHT;
	swapchainSpec.bufferCount = DOUBLE_BUFFERING;
	swapchainSpec.format = jgpu::Format::RGBA8_UNORM;
	swapchainSpec.windowHandle = glfwGetWin32Window(window);

	auto swapchain = UnwrapOrExit(instance->CreateSwapchain(*graphicsQueue, swapchainSpec));

	std::vector<jgpu::JPtr<jgpu::Texture>> backBuffers;
	std::vector<jgpu::JPtr<jgpu::TextureView>> backBufferViews;
	backBuffers.reserve(swapchainSpec.bufferCount);
	backBufferViews.reserve(swapchainSpec.bufferCount);
	for (uint32_t i = 0; i < swapchainSpec.bufferCount; i++)
	{
		auto backBuffer = UnwrapOrExit(swapchain->GetBackBuffer(i));

		jgpu::TextureViewSpecification texViewSpec{};
		texViewSpec.type = jgpu::TextureViewType::RenderTarget;
		texViewSpec.format = swapchainSpec.format;
		auto textureView = UnwrapOrExit(device->CreateTextureView(*backBuffer, texViewSpec));

		backBufferViews.push_back(std::move(textureView));
		backBuffers.push_back(std::move(backBuffer));
	}

	std::vector<FrameResource> frameResources;
	frameResources.resize(swapchainSpec.bufferCount);
	for (uint32_t i = 0; i < swapchainSpec.bufferCount; i++)
	{
		frameResources[i].cmdEncoder = std::move(UnwrapOrExit(device->CreateCommandEncoder(jgpu::QueueType::Graphics)));
	}

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		graphicsQueue->WaitIdle();
		
		const auto frameIdx = swapchain->GetCurrentBackBufferIdx();
		auto& frame = frameResources[frameIdx];

		frame.cmdEncoder->Begin();
		frame.cmdEncoder->TransitionTexture(*backBuffers[frameIdx], jgpu::ResourceState::Present, jgpu::ResourceState::RenderTarget);

		jgpu::ClearColor col{.r = 0.1f, .g = 0.1f, .b = 0.1f };
		frame.cmdEncoder->ClearTextureView(*backBufferViews[frameIdx], col);
		
		frame.cmdEncoder->TransitionTexture(*backBuffers[frameIdx], jgpu::ResourceState::RenderTarget, jgpu::ResourceState::Present);
		frame.cmdEncoder->Finish();
		graphicsQueue->Submit(*frame.cmdEncoder);
		swapchain->Present();
	}

	graphicsQueue->WaitIdle();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}