/*
 * Convert a 640*400 grid of RGBA pixels into a 80*50 set of
 * console characters and attribute values
 */
__kernel void convertToLargeBlocks(__global uchar4 *input, __constant uchar4 *colours, __global uchar2 *output )
{ 
	// Find out our X and Y co-ordinates for this pixel 
	int x = get_global_id(0);
	int y = get_global_id(1);

	// Find the width and height of the data set
	int xw = get_global_size(0);
	int yw = get_global_size(1);
	
	int offset = (y*xw) + x;

	// We need to process a 8*8 block to get the average colour
	unsigned int r=0,g=0,b=0;

	__global uchar4 *pixelOffset = input;
	pixelOffset += (x*8)+(y*640*8);

	for (int i=0;i<8;i++)
	{
		for (int j=0;j<8;j++)
		{
			r += pixelOffset->x;
			g += pixelOffset->y;
			b += pixelOffset->z;
			pixelOffset++;
		}
		pixelOffset += 640-8;
	}

	// Now calculate the average
	r /= 64;
	g /= 64;
	b /= 64;

	if (r+g+b > 100)
	{
		output[offset].x = 219;
		output[offset].y = 15;
	}
	else
	{
		output[offset].x = ' ';
		output[offset].y = 0;
	}
}

/*
 * Convert a 640*400 grid of RGBA pixels into a 80*100 set of
 * console characters and attribute values
 */
__kernel void convertToSmallBlocks(__global uchar4 *input, __constant uchar4 *colours, __global uchar2 *output )
{ 
	// Find out our X and Y co-ordinates for this pixel 
	int x = get_global_id(0);
	int y = get_global_id(1);

	// Find the width and height of the data set
	int xw = get_global_size(0);
	int yw = get_global_size(1);
	
	int offset = (y*xw) + x;

	// We need to process 2 blocks of 8*4 to get the average colour
	unsigned int r1=0,g1=0,b1=0;
	unsigned int r2=0,g2=0,b2=0;

	__global uchar4 *pixelOffset = input;
	pixelOffset += (x*8)+(y*640*8);

	for (int i=0;i<4;i++)
	{
		for (int j=0;j<8;j++)
		{
			r1 += pixelOffset->x;
			g1 += pixelOffset->y;
			b1 += pixelOffset->z;
			pixelOffset++;
		}
		pixelOffset += 640-8;
	}

	for (int i=0;i<4;i++)
	{
		for (int j=0;j<8;j++)
		{
			r2 += pixelOffset->x;
			g2 += pixelOffset->y;
			b2 += pixelOffset->z;
			pixelOffset++;
		}
		pixelOffset += 640-8;
	}

	// Now calculate the average
	r1 /= 64;
	g1 /= 64;
	b1 /= 64;

	r2 /= 64;
	g2 /= 64;
	b2 /= 64;

	if (r1+g1+b1 > 100)
	{
		if (r2+g2+b2 > 100)
		{
			// Top and bottom need drawing
			output[offset].x = 219;
			output[offset].y = 15;
		}
		else
		{
			// Just the top needs drawing
			output[offset].x = 223;
			output[offset].y = 15;
		}
	}
	else
	{
		if (r2+g2+b2 > 100)
		{
			// Just the bottom needs drawing
			output[offset].x = 220;
			output[offset].y = 15;
		}
		else
		{
			// It's blank
			output[offset].x = ' ';
			output[offset].y = 0;
		}
	}
} 