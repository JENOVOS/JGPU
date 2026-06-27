#include "jgpu/factory.h"

#include "d3d12/dx12Factory.h"

namespace jgpu
{
	std::unique_ptr<Factory> CreateFactory(GraphicsAPI type)
	{
		switch (type)
		{
		case GraphicsAPI::DirectX12:
			return std::make_unique<d3d12::DX12Factory>();
		case GraphicsAPI::Vulkan:
			return nullptr;
		}

		return nullptr;
	}
}