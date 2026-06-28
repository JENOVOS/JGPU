#pragma once
#include "enumes.h"

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

	struct TextureViewSpecification
	{
		TextureViewType type;
		Format format;
		uint32_t mipLevel = 0;
		uint32_t arrayLayer = 0;
	};

	struct ClearColor
	{
		float r = 0;
		float g = 0;
		float b = 0;
		float a = 1;
	};

}