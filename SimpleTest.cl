struct RGBA
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
	unsigned char A;
};

__kernel void hello(__global struct RGBA* data, __constant struct RGBA* colours)
{
	// Find out our X and Y co-ordinates for this pixel 
	int x = get_global_id(0);
	int y = get_global_id(1);

	// Find the width and height of the data set
	int xw = get_global_size(0);
	int yw = get_global_size(1);

	// Calculate the current pixel offset
	int offset = (y*xw) + x;
	__global struct RGBA *p = &data[offset];

	// Calculate the luminance of the pixel
	float lum = (0.2126f*p->R) + (0.7152f*p->G) + (0.0722f*p->B);
	data[ (y*xw) + x ].A = (unsigned char)lum;

	// Look for the closest console colour
	int closest = 0;
	float closestDist = 99999.9f;
	for (int i=0;i<16;i++)
	{
		float temp = (colours[i].R-p->R); // + pow((colours[i].G-p->G),2) + pow((colours[i].B-p->B),2);
		temp = sqrt(temp);
		
		if (temp < closestDist)
		{
			closest = i;
			closestDist = temp;
		} 
	}
	data[offset].A = (unsigned char)closest;
}

__kernel void testreduction(__global char* input, __global char* output)
{

}

