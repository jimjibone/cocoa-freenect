//
//  FRAppDelegate.m
//  cocoa-freenect-example
//
//  Created by James Reuss on 18/07/2013.
//  Copyright (c) 2013 James Reuss (jamesreuss.co.uk) All rights reserved.
//
//	Licensed under the Apache License, Version 2.0 (the "License");
//	you may not use this file except in compliance with the License.
//	You may obtain a copy of the License at
//
//	http://www.apache.org/licenses/LICENSE-2.0
//
//	Unless required by applicable law or agreed to in writing, software
//	distributed under the License is distributed on an "AS IS" BASIS,
//	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//	See the License for the specific language governing permissions and
//	limitations under the License.
//

#import "FRAppDelegate.h"
#import "FRFreenectHelpers.h"

@interface FRAppDelegate () {
	uint16_t *_kinectDepth;
	uint8_t  *_kinectRGB;
}

@end

@implementation FRAppDelegate

- (void)dealloc
{
    [super dealloc];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	// Initialise and start the Kinect controller.
	freenectController = [[FRFreenect alloc] initWithLEDColour:LED_GREEN];
	
	// Allocate memory for the kinect and display data
	_kinectDepth	= (uint16_t*)malloc(FREENECT_DEPTH_11BIT_SIZE);
	_kinectRGB		= (uint8_t*)malloc(FREENECT_VIDEO_RGB_SIZE);
	
	displayTimer = [[NSTimer alloc] initWithFireDate:[NSDate dateWithTimeIntervalSinceNow:(NSTimeInterval)1.0] interval:0.1 target:self selector:@selector(transferFrames) userInfo:nil repeats:YES];
	[[NSRunLoop mainRunLoop] addTimer:displayTimer forMode:NSDefaultRunLoopMode];
}

- (void)transferFrames
{
	// Collect new frames.
	BOOL newData = NO;
	newData  = [freenectController swapDepthData:&_kinectDepth];
	newData |= [freenectController swapRGBData:&_kinectRGB];
	
	if (newData) {
		// Send the new frames to the display.
		[self.cloudView swapInNewDepthFrame:&_kinectDepth RGBFrame:&_kinectRGB];
	}
}

- (IBAction)startKinect:(id)sender
{
	if (!displayTimer) {
		displayTimer = [[NSTimer alloc] initWithFireDate:[NSDate dateWithTimeIntervalSinceNow:(NSTimeInterval)1.0] interval:0.1 target:self selector:@selector(transferFrames) userInfo:nil repeats:YES];
		[[NSRunLoop mainRunLoop] addTimer:displayTimer forMode:NSDefaultRunLoopMode];
	}
}

- (IBAction)stopKinect:(id)sender
{
	if (displayTimer) {
		[displayTimer invalidate];
	}
}

@end
