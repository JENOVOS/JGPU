#include "dx12TextureView.h"

namespace jgpu::d3d12
{
	DX12TextureView::DX12TextureView(RtvHandle&& handle)
		: handle_(std::move(handle))
	{}
}