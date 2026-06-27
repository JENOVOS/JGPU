#include "dx12Utils.h"

#include <expected>

namespace jgpu::d3d12::utils
{
	void ThrowIfFailed(HRESULT hr)
	{
		if (FAILED(hr))
		{
			throw std::runtime_error("HRESULT ERROR");
		}
	}

	std::unexpected<std::string> MakeHResultError(const char* message, HRESULT hr)
	{
		return std::unexpected<std::string>{
			std::format("{} HRESULT: 0x{:08X}", message, static_cast<unsigned int>(hr))
		};
	}
}