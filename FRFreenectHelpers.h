//
//  FRFreenectHelpers.h
//  cocoa-freenect-example
//
//  Created by James Reuss on 18/07/2013.
//  Copyright (c) 2013 James Reuss. All rights reserved.
//

#ifndef cocoa_freenect_example_FRFreenectHelpers_h
#define cocoa_freenect_example_FRFreenectHelpers_h

#define FREENECT_FRAME_W 640
#define FREENECT_FRAME_H 480
#define FREENECT_FRAME_PIX (FREENECT_FRAME_H*FREENECT_FRAME_W)

#define FREENECT_DEPTH_11BIT_SIZE (FREENECT_FRAME_PIX*sizeof(uint16_t))
#define FREENECT_VIDEO_RGB_SIZE (FREENECT_FRAME_PIX*3)

// These may need altering for your own Kinect to be accurate.
#define REGISTERED_MIN_DEPTH    0
#define REGISTERED_SCALE_FACTOR 0.00174

double worldXfromFrame(int x, int z);
double worldYfromFrame(int y, int z);

unsigned int depthIndex(unsigned int x, unsigned int y);
unsigned int rgbIndex(unsigned int x, unsigned int y);
void frameXYfromIndex(unsigned int* x, unsigned int* y, unsigned int index);
void worldFromIndex(double* wx, double* wy, unsigned int index, int z);
void indexFromWorld(unsigned int* index, double wx, double wy, int z);
void frameFromWorld(unsigned int* x, unsigned int *y, double wx, double wy, int z);

void swapPtr16(uint16_t **firstPtr, uint16_t **secondPtr);
void swapPtr8(uint8_t **firstPtr, uint8_t **secondPtr);

#endif
