__kernel void hello(__global char* data)
{
	// Find out our X and Y co-ordinates for this pixel 
	int x = get_global_id(0);
	int y = get_global_id(1);

	// Find the width and height of the data set
	int xw = get_global_size(0);
	int yw = get_global_size(1);

	//data[0] = xw;
	//data[1] = yw;

	data[ (y*xw) + x ] = x % 2;
}

__kernel void testreduction(__global char* input, __global char* output)
{

}

