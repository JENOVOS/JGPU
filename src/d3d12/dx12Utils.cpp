#include "dx12Utils.h"

namespace jgpu::d3d12::utils
{
	void ThrowIfFailed(HRESULT hr)
	{
		if (FAILED(hr))
		{
			throw std::runtime_error("HRESULT ERROR");
		}
	}
}