#pragma once
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#include <CL/cl.hpp>

class ConverterToLargeBlocks
{
public:
	ConverterToLargeBlocks();
	~ConverterToLargeBlocks();

	bool initialise(const cl::Context &context, const std::vector<cl::Device> &devices);
	bool buildKernel(cl::Buffer &frameBuf, cl::Buffer &colourBuf, cl::Buffer &outputBuf);

	const cl::Program& getProgram() const;
	const cl::Kernel& getKernel() const;
private:
	cl::Program _program;
	cl::Kernel	_kernel;
};

