//#define CL_USE_DEPRECIATED_OPENCL_2_0_APIS
//#define __CL_ENABLE_EXCEPTIONS

#define CL_USE_DEPRECATED_OPENCL_1_2_APIS

#include <CL/cl.hpp>
#include <iostream>
#include <thread>

#include "Timer.h"
#include "StatsCounter.h"
#include "ConverterToLargeBlocks.h"
#include "Utils.h"

const int WIDTH = 640;
const int HEIGHT = 400;

struct RGBA
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
	unsigned char A;
};

std::vector<RGBA>	vecColours{
{ 0,0,0 },
{ 0,0,128 },
{ 0,128,0 },
{ 0,128,128 },
{ 128,0,0 },
{ 128,0,128 },
{ 128,128,0 },
{ 192,192,192 },
{ 128,128,128 },
{ 0,0,255 },
{ 0,255,0 },
{ 0,255,255 },
{ 255,0,0 },
{ 255,0,255 },
{ 255,255,0 },
{ 255,255,255 } };


void dumpPlatformDetails(const std::vector<cl::Platform> &platforms)
{
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

		std::cout << "Platform:" << name;
		std::cout << " Profile:" << profile;
		std::cout << " Vendor:" << vendor;
		std::cout << " Version:" << version << std::endl;
	}
}

void dumpDeviceDetails(const std::vector<cl::Device> &devices)
{
	for (cl::Device d : devices)
	{
		std::string name;
		d.getInfo(CL_DEVICE_NAME, &name);

		cl_bool available;
		d.getInfo(CL_DEVICE_AVAILABLE, &available);

		std::cout << "Device:" << name;
		std::cout << " Available:" << available;
		std::cout << std::endl;
	}
}

int main()
{
	cl_int err = CL_SUCCESS;

	std::vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);
	if (platforms.size() == 0)
	{
		std::cout << "Platform size 0\n";
		return -1;	
	}

	// Iterate through the platforms the print out their details
	//dumpPlatformDetails(platforms);

	cl_context_properties properties [] = { CL_CONTEXT_PLATFORM, (cl_context_properties) (platforms[0])(), 0 };
	cl::Context context(CL_DEVICE_TYPE_GPU, properties);
		
	std::vector<cl::Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();
		
	// See what devices we have to use
	//dumpDeviceDetails(devices);

	// Create a local copy of the source code
	std::string str = Utils::loadFile("SimpleTest.cl");
	if (str.empty())
	{
		std::cout << "Failed to load the openCL kernel file" << std::endl;
	}

	cl::Program::Sources source(1, std::make_pair(str.c_str(), str.size()));

	cl::Program program = cl::Program(context, source);
	if (program.build(devices, "-g") != CL_SUCCESS)
	{
		std::string buildOptions;
		program.getBuildInfo<std::string>(devices[0], CL_PROGRAM_BUILD_OPTIONS, &buildOptions);

		std::string log;
		program.getBuildInfo<std::string>(devices[0], CL_PROGRAM_BUILD_LOG, &log);
		std::cout << "Build Log:" << log << std::endl;

		std::string buildStatus;
		program.getBuildInfo<std::string>(devices[0], CL_PROGRAM_BUILD_STATUS, &buildStatus);

		std::cin.get();
		return -1;
	}

	// Allocate the RGBA frame buffer
	cl::Buffer frameBuf(context, CL_MEM_READ_WRITE, WIDTH*HEIGHT * sizeof(RGBA));
	// Allocate the space for the console colours
	cl::Buffer colourBuf(context, CL_MEM_READ_WRITE, 16 * sizeof(RGBA));

	//ConverterToLargeBlocks conv();

	// Setup and run the kernel
	//cl::Kernel kernel(program_, "generateLuminance", &err);
	cl::Kernel kernel(program, "generateConsoleColour", &err);

	//kernel.getInfo(
	kernel.setArg(0, frameBuf);
	kernel.setArg(1, colourBuf);

	// Create the queue that all actions are performed on
	cl::CommandQueue queue(context, devices[0], 0, &err);

	// Initialise the values in our shared buffer
	RGBA *data = (RGBA*) queue.enqueueMapBuffer(frameBuf, CL_TRUE, CL_MAP_WRITE, 0, WIDTH*HEIGHT);
	for (int i = 0; i < (WIDTH*HEIGHT); ++i)
	{
		data[i].R = rand() % 256;
		data[i].G = rand() % 256;
		data[i].B = rand() % 256;
		data[i].A = 0;
	}
	// Not sure if I need to unmap this if I want to use it later
	queue.enqueueUnmapMemObject(frameBuf, data);

	RGBA *coldata = (RGBA*) queue.enqueueMapBuffer(colourBuf, CL_TRUE, CL_MAP_WRITE, 0, 16*sizeof(RGBA));
	for (int i = 0; i < 16; ++i)
	{
		coldata[i].R = vecColours[i].R;
		coldata[i].G = vecColours[i].G;
		coldata[i].B = vecColours[i].B;
		coldata[i].A = 0;
	}
	// Not sure if I need to unmap this if I want to use it later
	queue.enqueueUnmapMemObject(colourBuf, coldata);

	// Create an object to hold our perf numbers
	StatsCounter sc;

	cl::Event event;
	for (int i = 0; i < 100; i++)
	{
		Timer::startTimer();

		if (CL_SUCCESS != queue.enqueueNDRangeKernel(
			kernel,
			cl::NullRange,
			cl::NDRange(WIDTH, HEIGHT),
			cl::NullRange,
			NULL,
			&event))
		{
			std::cout << "Failed to enqueue the kernel to run" << std::endl;
			break;
		}

		event.wait();
		
		sc.AddValue(Timer::getTimer());

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	sc.DumpValues();

	std::cin.get();
	return 0;
}