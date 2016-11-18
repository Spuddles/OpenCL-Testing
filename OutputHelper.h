#pragma once
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#include <CL/cl.hpp>
#include <vector>

class OutputHelper
{
public:
	OutputHelper();
	~OutputHelper();

	static void dumpPlatformDetails(const std::vector<cl::Platform> &platforms);
	static void dumpDeviceDetails(const std::vector<cl::Device> &devices);
};

