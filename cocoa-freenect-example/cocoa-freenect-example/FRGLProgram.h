//
//  FRGLProgram.h
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
