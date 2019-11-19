//convolve fast
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fast_filter.h" //calls the fast_filter library

//Main Method:
int main(int argc, char *argv[] )
{
	//declare two pointers to files
	FILE *img_in = NULL;
	FILE *img_out = NULL;

	img_in = fopen( argv[1], "rb" ); //open the image file
	if( img_in == NULL ){ //Error checking to make sure image opened
		printf( "Could not open the input image file.\n" );
		return 0;
	}
	
//To determine the size of the file:
	int size = 0; //initialize the size to count the number of chars in the file
	int read_code;
	char c;
	while( ( read_code = fgetc( img_in )) != EOF ){
		size++; //each successive loop increment the index;
	}
	fclose(img_in); //close the file

//INPUT: Read from the inputed file
	img_in = fopen( argv[1], "rb" ); //reopen the file to reset the pointer
	char img_data[size];
	int i=0;
	while( ( read_code = fgetc( img_in )) != EOF ){
		c = (char)read_code;
		img_data[i]=c; //populates the img_data array
		i++;
	}
	fclose(img_in); //Close the file

//WEIGHTS: Filter_Weights initialization
	float filter_weights[argc-4];
	for(i=0;i<argc-4;i++){
		filter_weights[i] = atof(argv[i+4]); //casts to a float
	}

//WIDTH: Filter width initialization
	int filter_width= atoi(argv[3]); //casts to an integer

//DOFILTER: pass through the doFiltering function
	//first initialize out_img_data
	unsigned char* out_img_data = malloc(sizeof(char)*size);
	doFiltering(img_data,filter_weights,filter_width,out_img_data);

//OUTPUT: Write the modified file:
	img_out = fopen( argv[2], "wb" ); //open second file
	for(i=0;i<size;i++){
		fputc( out_img_data[i], img_out ); //loop to write the modified file
	}
	fclose(img_out); //close the file
}

