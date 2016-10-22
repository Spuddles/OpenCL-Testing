//#define CL_USE_DEPRECIATED_OPENCL_2_0_APIS
//#define __CL_ENABLE_EXCEPTIONS

#include <CL/cl.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>

const int WIDTH = 640;
const int HEIGHT = 700;

std::chrono::high_resolution_clock::time_point _start;

void startTimer()
{
	_start = std::chrono::high_resolution_clock::now();
}

unsigned int getTimer()
{
	std::chrono::high_resolution_clock::time_point _end = std::chrono::high_resolution_clock::now();

	std::chrono::microseconds us = std::chrono::duration_cast<std::chrono::microseconds>(_end - _start);

	std::cout << "microseconds=" << us.count() << std::endl;

	return us.count();
}

std::string LoadFile(const std::string &filename)
{
	std::ifstream input(filename);
	if (input)
	{
		std::ostringstream contents;

		contents << input.rdbuf();

		return contents.str();	
	}
	return "";
}

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
	//try
	{	
		std::vector<cl::Platform> platforms;
		cl::Platform::get(&platforms);
		if (platforms.size() == 0)
		{
			std::cout << "Platform size 0\n";
			return -1;	
		}

		// Iterate through the platforms the print out their details
		dumpPlatformDetails(platforms);

		cl_context_properties properties [] = { CL_CONTEXT_PLATFORM, (cl_context_properties) (platforms[0])(), 0 };
		cl::Context context(CL_DEVICE_TYPE_GPU, properties);
		
		std::vector<cl::Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();
		
		// See what devices we have to use
		dumpDeviceDetails(devices);

		// Create a local copy of the source code
		std::string str = LoadFile("SimpleTest.cl");
		cl::Program::Sources source(1, std::make_pair(str.c_str(), str.size()));

		// Make the buffer we want to pass to the kernel
		//unsigned char buffer[WIDTH*HEIGHT];
//		cl::Buffer memBuf(context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY, sizeof(buffer));
		cl::Buffer memBuf(context, CL_MEM_READ_WRITE, WIDTH*HEIGHT);

		cl::Program program_ = cl::Program(context, source);
		program_.build(devices);

		std::string log;
		program_.getBuildInfo<std::string>(devices[0], CL_PROGRAM_BUILD_OPTIONS, &log);
		program_.getBuildInfo<std::string>(devices[0], CL_PROGRAM_BUILD_LOG, &log);
		program_.getBuildInfo<std::string>(devices[0], CL_PROGRAM_BUILD_STATUS, &log);

		cl::Kernel kernel(program_, "hello", &err);
		kernel.setArg(0, memBuf);

		cl::Event event;
		cl::CommandQueue queue(context, devices[0], 0, &err);

		for (int i = 0; i < 20; i++)
		{
			startTimer();

			queue.enqueueNDRangeKernel(
				kernel,
				cl::NullRange,
				cl::NDRange(WIDTH,HEIGHT),
				cl::NullRange,
				NULL,
				&event);

			event.wait();

			// Copy the buffer from GPU to CPU memory
			//queue.enqueueReadBuffer(memBuf, CL_TRUE, 0, sizeof(buffer), buffer);

			// Try mapping memory to avoid the copy
			char *result = (char*)queue.enqueueMapBuffer(memBuf, CL_TRUE, CL_MAP_READ, 0, WIDTH*HEIGHT);
			
			// Unmap once we have finished
			queue.enqueueUnmapMemObject(memBuf, result);

			getTimer();

			//std::this_thread::sleep_for(std::chrono::seconds(1));
		}

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; ++j)
			{
//				std::cout << (int) buffer[(i*WIDTH)+j] << " ";
			}
//			std::cout << std::endl;
		}
//		std::cout << std::endl;
	}
	/*catch (cl::Error err)
	{
		std::cerr
			 << "ERROR: "
			 << err.what()
			 << "("
			 << err.err()
			 << ")"
			 << std::endl;
		
	}*/
	std::cin.get();
	return 0;
}