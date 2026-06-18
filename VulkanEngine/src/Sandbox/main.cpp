#include "Engine/VulkanEngine.h"

int main(int argc, char* argv[])
{
	VulkanEngine _engine{};

	_engine.init();
	_engine.run();
}