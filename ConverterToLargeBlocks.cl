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

			// For now, just fill everything with stars
			//output[offset].x = '*';
			//output[offset].y = 15;
		}
		pixelOffset += 640;
	}

	// Now calculate the average
	r /= 64;
	g /= 64;
	b /= 64;

	if (r+g+b > 100)
	{
		output[offset].x = '*';
		output[offset].y = 15;
	}
	else
	{
		output[offset].x = ' ';
		output[offset].y = 0;
	}
} 