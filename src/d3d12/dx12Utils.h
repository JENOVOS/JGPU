#pragma once
#include <expected>

namespace jgpu::d3d12::utils
{
	void ThrowIfFailed(HRESULT hr);
	std::unexpected<std::string> MakeHResultError(const char* message, HRESULT hr);
}