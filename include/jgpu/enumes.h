#pragma once

namespace jgpu
{
	enum class GraphicsAPI : uint8_t
	{
		DirectX12,
		Vulkan
	};

	enum class QueueType : uint8_t
	{
		Graphics,
		Compute,
		Copy
	};
}