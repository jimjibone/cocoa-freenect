//
//  FRFreenectHelpers.c
//  cocoa-freenect-example
//
//  Created by James Reuss on 18/07/2013.
//  Copyright (c) 2013 James Reuss. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <libfreenect/libfreenect.h>
#include "FRFreenectHelpers.h"

double worldXfromFrame(int x, int z) {
    return (x - 640/2)*(z + REGISTERED_MIN_DEPTH)*REGISTERED_SCALE_FACTOR;
}
double worldYfromFrame(int y, int z) {
    return -(y - 480/2)*(z + REGISTERED_MIN_DEPTH)*REGISTERED_SCALE_FACTOR;
}

unsigned int depthIndex(unsigned int x, unsigned int y) {
	return x + y*FREENECT_FRAME_W;
}
unsigned int rgbIndex(unsigned int x, unsigned int y) {
	return 3*(x + y*FREENECT_FRAME_W);
}
void frameXYfromIndex(unsigned int* x, unsigned int* y, unsigned int index) {
	//framePix = x + y*FREENECT_FRAME_W;
	*x = index % FREENECT_FRAME_W;
	*y = (index - *x) / FREENECT_FRAME_W;
}

void worldFromIndex(double* wx, double* wy, unsigned int index, int z) {
	unsigned int x = index % FREENECT_FRAME_W;
	unsigned int y = (index - x) / FREENECT_FRAME_W;
	
	*wx = (double)((x - 640/2.0)*(z + REGISTERED_MIN_DEPTH)*REGISTERED_SCALE_FACTOR);
	*wy = (double)((y - 480/2.0)*(z + REGISTERED_MIN_DEPTH)*REGISTERED_SCALE_FACTOR*-1.0);
}
void indexFromWorld(unsigned int* index, double wx, double wy, int z) {
	double x = wx/REGISTERED_SCALE_FACTOR/(z + REGISTERED_MIN_DEPTH) + 640/2.0;
	double y = wy/REGISTERED_SCALE_FACTOR/(z + REGISTERED_MIN_DEPTH)/(-1.0) + 480/2.0;
	
	x = (x > 0.0) ? floor(x + 0.5) : ceil(x - 0.5);
	y = (y > 0.0) ? floor(y + 0.5) : ceil(y - 0.5);
	
	*index = (unsigned int)(x + y*FREENECT_FRAME_W);
}
void frameFromWorld(unsigned int* x, unsigned int *y, double wx, double wy, int z) {
	double nx = wx/REGISTERED_SCALE_FACTOR/(z + REGISTERED_MIN_DEPTH) + 640/2.0;
	double ny = wy/REGISTERED_SCALE_FACTOR/(z + REGISTERED_MIN_DEPTH)/(-1.0) + 480/2.0;
	
	*x = (unsigned int)( (nx > 0.0) ? floor(nx + 0.5) : ceil(nx - 0.5) );
	*y = (unsigned int)( (ny > 0.0) ? floor(ny + 0.5) : ceil(ny - 0.5) );
}


// Pointer swapping c functions.
void swapPtr16(uint16_t **firstPtr, uint16_t **secondPtr) {
	uint16_t *temp = *firstPtr;
	*firstPtr = *secondPtr;
	*secondPtr = temp;
	return;
}
void swapPtr8(uint8_t **firstPtr, uint8_t **secondPtr) {
	uint8_t *temp = *firstPtr;
	*firstPtr = *secondPtr;
	*secondPtr = temp;
	return;
}
