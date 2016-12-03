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
#include "OutputHelper.h"
#include "Display.h"

const int PIXEL_WIDTH = 640;
const int PIXEL_HEIGHT = 400;
const int CONSOLE_WIDTH = 80;
const int CONSOLE_HEIGHT = 50;

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

int main()
{
	cl_int err = CL_SUCCESS;

	std::vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);
	OutputHelper::dumpPlatformDetails(platforms);
	if (platforms.size() == 0)
	{
		std::cout << "Platform size 0\n";
		return -1;	
	}

	cl_context_properties properties [] = { CL_CONTEXT_PLATFORM, (cl_context_properties) (platforms[0])(), 0 };
	cl::Context context(CL_DEVICE_TYPE_CPU, properties);
		
	std::vector<cl::Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();
	OutputHelper::dumpDeviceDetails(devices);

	ConverterToLargeBlocks conv;
	if (!conv.initialise(context, devices))
	{
		std::cout << "Failed to load ConverterToLargeBlocks kernel" << std::endl;
		std::cin.get();
		return -1;
	}

	// Allocate the RGBA frame buffer
	cl::Buffer frameBuf(context, CL_MEM_READ_WRITE, PIXEL_WIDTH*PIXEL_HEIGHT * sizeof(RGBA));
	// Allocate the space for the console colours
	cl::Buffer colourBuf(context, CL_MEM_READ_WRITE, 16 * sizeof(RGBA));
	// Allocate the space for the resulting console buffer
	cl::Buffer outputBuf(context, CL_MEM_READ_WRITE, CONSOLE_WIDTH * CONSOLE_HEIGHT * 2);

	if (!conv.buildKernel(frameBuf, colourBuf, outputBuf))
	{
		std::cout << "Failed to create the kernel" << std::endl;
		return -1;
	}

	// Create the queue that all actions are performed on
	cl::CommandQueue queue(context, devices[0], 0, &err);

	// Initialise the values in our shared buffer
	RGBA *data = (RGBA*) queue.enqueueMapBuffer(frameBuf, CL_TRUE, CL_MAP_WRITE, 0, PIXEL_WIDTH*PIXEL_HEIGHT);

/*	// Initialise to random RGB pixels
	for (int i = 0; i < (PIXEL_WIDTH*PIXEL_HEIGHT); ++i)
	{
		data[i].R = rand() % 256;
		data[i].G = rand() % 256;
		data[i].B = rand() % 256;
		data[i].A = 0;
	}*/

	// Load a RAW picture from a file
	if (!Utils::loadBinaryFile("Images\\BW-Swirls.data", (char*) data))
	//if (!Utils::loadBinaryFile("Images\\RGB-Megaman.data", (char*) data))
	{
		std::cout << "Failed to load the raw picture file" << std::endl;
		std::cin.get();
		return -1;
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

	// Get a pointer to the output buffer
	unsigned char* outputPtr = (unsigned char*) queue.enqueueMapBuffer(outputBuf, CL_TRUE, CL_MAP_READ, 0, CONSOLE_WIDTH*CONSOLE_HEIGHT*2);

	Display disp;
	disp.FillBuffer('-', 7);
	disp.UpdateConsole();

	// Create an object to hold our perf numbers
	StatsCounter sc;

	cl::Event event;
	for (int i = 0; i < 10; i++)
	{
		Timer::startTimer();

		if (CL_SUCCESS != queue.enqueueNDRangeKernel(
			conv.getKernel(),
			cl::NullRange,
			cl::NDRange(CONSOLE_WIDTH, CONSOLE_HEIGHT),
			cl::NullRange,
			NULL,
			&event))
		{
			std::cout << "Failed to enqueue the kernel to run" << std::endl;
			break;
		}

		event.wait();
		sc.AddValue(Timer::getTimer());

		disp.CopyToBuffer((char*)outputPtr);
		disp.UpdateConsole();

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	disp.MoveCursor(0, 50);
	sc.DumpValues();

	std::cin.get();
	return 0;
}