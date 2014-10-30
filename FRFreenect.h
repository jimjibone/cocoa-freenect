//
//  FRFreenect.h
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

#import <Foundation/Foundation.h>
#import <libfreenect/libfreenect.h>

typedef enum {
	KINECT_STOPPED = 0,
	KINECT_STARTING,
	KINECT_NO_DEVICES,
	KINECT_RUNNING,
	KINECT_FAILED_OPEN,
	KINECT_FAILED_INIT,
	KINECT_SHUTDOWN
} FRKinectStatus;

@class FRFreenect;
@protocol FRFreenectDelegate
@required
- (void)freenectDidUpdateStatus:(NSString*)stringRepesentation code:(FRKinectStatus)statusCode;
@optional
- (void)freenectDidUpdateHardware;
@end

@interface FRFreenect : NSObject {
	id<FRFreenectDelegate> delegate;
}

@property (nonatomic, readonly) NSNumber *depthFPS;
@property (nonatomic, readonly) NSNumber *rgbFPS;
@property (nonatomic, readonly) NSNumber *kinectAngle;
@property (nonatomic, readonly) freenect_led_options kinectLed;

@property (assign, nonatomic) NSMutableDictionary *kinectStatusDict;
@property (assign, nonatomic) NSMutableDictionary *kinectHardwareDict;

- (id)initWithLEDColour:(freenect_led_options)ledColour initialTilt:(float)initTilt;
- (id)initWithLEDColour:(freenect_led_options)ledColour;
- (id)init;

- (void)setDelegate:(id<FRFreenectDelegate>)aDelegate;

- (BOOL)swapDepthData:(uint16_t**)swapData;
- (BOOL)swapRGBData:(uint8_t**)swapData;
- (uint16_t*)createDepthData;
- (uint8_t*)createRGBData;

- (void)stopKinectSoon;
- (void)stopKinectImmediately;
- (void)startKinectSoon;

- (void)setKinectTilt:(float)tilt;
- (void)setKinectLED:(freenect_led_options)led;

@end
