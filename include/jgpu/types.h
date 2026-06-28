#pragma once

namespace jgpu
{
	struct DeviceCreateInfo
	{

	};

	struct SwapchainSpecification
	{
		uint32_t width = 0;
		uint32_t height = 0;
		uint32_t bufferCount = 2;
		Format format = Format::RGBA8_UNORM;
		void* windowHandle = nullptr;
	};
}