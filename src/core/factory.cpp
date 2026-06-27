#include "jgpu/factory.h"

#include "d3d12/dx12Factory.h"

namespace jgpu
{
	JCreateResult<Factory> CreateFactory(GraphicsAPI type)
	{
		switch (type)
		{
		case GraphicsAPI::DirectX12:
			return std::make_unique<d3d12::DX12Factory>();
		case GraphicsAPI::Vulkan:
			return std::unexpected{ "Failed to create factory" };
		}

		return std::unexpected{ "Failed to create factory" };
	}
}