#include "OutputHelper.h"
#include <iostream>

OutputHelper::OutputHelper()
{
}

OutputHelper::~OutputHelper()
{
}

void OutputHelper::dumpPlatformDetails(const std::vector<cl::Platform> &platforms)
{
	int platformCount = 0;
	for (cl::Platform p : platforms)
	{
		std::string name;
		p.getInfo(CL_PLATFORM_NAME, &name);

		std::string profile;
		p.getInfo(CL_PLATFORM_PROFILE, &profile);

		std::string vendor;
		p.getInfo(CL_PLATFORM_VENDOR, &vendor);

		std::string version;
		p.getInfo(CL_PLATFORM_VERSION, &version);

		std::cout << "Platform " << platformCount++ << ":" << name;
		std::cout << " Profile:" << profile;
		std::cout << " Vendor:" << vendor;
		std::cout << " Version:" << version << std::endl;
	}
}

void OutputHelper::dumpDeviceDetails(const std::vector<cl::Device> &devices)
{
	int deviceCount = 0;
	for (cl::Device d : devices)
	{
		std::string name;
		d.getInfo(CL_DEVICE_NAME, &name);

		cl_bool available;
		d.getInfo(CL_DEVICE_AVAILABLE, &available);

		std::cout << "Device " << deviceCount++ << ":" << name;
		std::cout << " Available:" << available;
		std::cout << std::endl;
	}
}
