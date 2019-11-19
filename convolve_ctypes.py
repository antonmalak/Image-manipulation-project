#convolve_ctypes.py
#!/usr/bin/python
import sys
import ctypes

#load the BMP file into a string
def loadBMPImage( img_name ):
	img_in = open( img_name, 'rb' )
	img_data = img_in.read()
	img_in.close()
	return img_data

# Read the filter information from command line and 
def parseFilterCmdArgs( cmd_args ):

  filter_width = int( cmd_args[3] )
  filter_weights = []
  filter_offsets = []

  for i in range(0,filter_width*filter_width):
    filter_weights.append( float(cmd_args[4+i] ))

  return ( filter_width, filter_weights )

#function to write file
def writeFile(out_img_data, name):
	img_out = open( name, 'wb' )
	img_out.write( out_img_data )
	img_out.close()

# Function that feeds data into fast_filter
def doConvolution( img_data, filter_weights, filter_width, name):
	clib = ctypes.cdll.LoadLibrary("libfast_filter.so")

	#passing filter_weights as a float array
	cfloat=ctypes.c_float * len(filter_weights)
	cfai=cfloat(*filter_weights)

	#setting out_image_data to size of img_data
	out_img_data = " "* len(img_data)

	#Passing the data into the fast filter
	clib.doFiltering(img_data, cfai, filter_width, out_img_data)

	writeFile(out_img_data, name)

# The main code starts here 
img_data = loadBMPImage( sys.argv[1] )
(filter_width, filter_weights) = parseFilterCmdArgs( sys.argv )
#call the do convolution function
doConvolution(img_data, filter_weights, filter_width, sys.argv[2])









