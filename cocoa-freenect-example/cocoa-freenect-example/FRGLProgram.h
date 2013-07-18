//
//  FRGLProgram.h
//  cocoa-freenect-example
//
//  Created by James Reuss on 18/07/2013.
//  Copyright (c) 2013 James Reuss. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <OpenGL/OpenGL.h>
#import <OpenGL/gl.h>

@interface FRGLProgram : NSObject {
	GLuint _id;
    NSString *_name;
}

- (id)initWithName:(NSString*)name VS:(const char*)vs FS:(const char*)fs;

- (NSString*)name;

- (void)bind;
- (void)unbind;

- (void)setUniformInt:(int)i forName:(NSString*)name;
- (void)setUniformFloat:(float)f forName:(NSString*)name;

@end
