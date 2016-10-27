struct RGBA
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
	unsigned char A;
};

__kernel void hello(__global struct RGBA* data)
{
	// Find out our X and Y co-ordinates for this pixel 
	int x = get_global_id(0);
	int y = get_global_id(1);

	// Find the width and height of the data set
	int xw = get_global_size(0);
	int yw = get_global_size(1);

	// Calculate the luminance of the pixel
	float lum = (0.2126f*data[ (y*xw) + x ].R) + (0.7152f*data[ (y*xw) + x ].G) + (0.0722f*data[ (y*xw) + x ].B);

	// Look for the closest console colour

	data[ (y*xw) + x ].A = (unsigned char)lum;
}

__kernel void testreduction(__global char* input, __global char* output)
{

}

