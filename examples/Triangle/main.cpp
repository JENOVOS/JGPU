#include <iostream>
#include <jgpu/jgpu.h>

int main()
{
	auto factory = jgpu::CreateFactory(jgpu::GraphicsAPI::DirectX12);
	if (!factory)
	{
		std::cerr << factory.error() << std::endl;
		return -1;
	}

	auto instance = (*factory)->CreateInstance(true);
	if (!instance)
	{
		std::cerr << instance.error() << std::endl;
		return -1;
	}

	auto adapter = (*instance)->FindAdapter();
	if (!adapter)
	{
		std::cerr << adapter.error() << std::endl;
		return -1;
	}

	auto device = (*adapter)->CreateDevice();
	if (!device)
	{
		std::cerr << device.error() << std::endl;
		return -1;
	}

	return 0;
}