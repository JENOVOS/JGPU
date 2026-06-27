#include <iostream>
#include <jgpu/jgpu.h>

int main()
{
	auto factory = jgpu::CreateFactory(jgpu::GraphicsAPI::DirectX12);
	auto instance = factory->CreateInstance(true);
	return 0;
}