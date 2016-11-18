#include "ConverterToLargeBlocks.h"
#include "Utils.h"
#include <iostream>

ConverterToLargeBlocks::ConverterToLargeBlocks()
{
}

ConverterToLargeBlocks::~ConverterToLargeBlocks()
{
}

bool ConverterToLargeBlocks::initialise(const cl::Context &context, const std::vector<cl::Device> &devices)
{
	std::string sourceStr = Utils::loadFile("ConverterToLargeBlocks.cl");
 
	cl::Program::Sources source(1, std::make_pair(sourceStr.c_str(), sourceStr.size()));

	_program = cl::Program(context, source);
	if (_program.build(devices, "-g") != CL_SUCCESS)
	{
		std::string log;
		_program.getBuildInfo<std::string>(devices[0], CL_PROGRAM_BUILD_LOG, &log);
		std::cout << "Build Log:" << log << std::endl;
		return false;
	}
	return true;
}

bool ConverterToLargeBlocks::buildKernel(cl::Buffer &frameBuf, cl::Buffer &colourBuf, cl::Buffer &outputBuf)
{
	cl_int	err;
	
	_kernel = cl::Kernel(_program, "convertToLargeBlocks", &err);

	if (err != CL_SUCCESS)
		return false;

	_kernel.setArg(0, frameBuf);
	_kernel.setArg(1, colourBuf);
	_kernel.setArg(2, outputBuf);

	return true;
}

const cl::Program& ConverterToLargeBlocks::getProgram() const
{
	return _program;
}

const cl::Kernel& ConverterToLargeBlocks::getKernel() const
{
	return _kernel;
}