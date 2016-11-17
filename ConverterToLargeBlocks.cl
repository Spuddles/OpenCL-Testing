/*
 * Convert a 640*400 grib of RGBA pixels into a 80*50 set of
 * console characters and attribute values
 */
__kernel void convertToLargeBlocks(__global uchar4 *input, __global uchar2 *output, __constant uchar4 *colours)
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

	for (int i=0;i<8;i++)
	{
		for (int j=0;j<8;j++)
		{
			
		}
	}
} 