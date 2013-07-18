//
//  FRGLProgram.m
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

#import "FRGLProgram.h"

@implementation FRGLProgram

-(GLuint)loadShader:(GLenum)type code:(const char *)code {
    NSString *desc = [NSString stringWithFormat:@"%@ shader %@", ((type == GL_VERTEX_SHADER)?@"Vertex":@"Fragment"), _name];
    GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, (const GLchar **)&code, NULL);
	glCompileShader(shader);
	
    GLint logLength;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
	if(logLength > 0) {
		GLchar *log = malloc(logLength);
		glGetShaderInfoLog(shader, logLength, &logLength, log);
		NSLog(@"%@ compile log:\n%s", desc, log);
		free(log);
	}
    
    GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if(status == 0)
		NSLog(@"Failed to compile desc: %@:\n %s", desc, code);
    
	return shader;
}

- (id)initWithName:(NSString*)name VS:(const char*)vs FS:(const char*)fs {
    if((self = [super init])) {
        _name = [name retain];
        
        NSString *desc = [NSString stringWithFormat:@"Program %@", _name];
        GLuint cvs = [self loadShader:GL_VERTEX_SHADER code:vs];
        GLuint cfs = [self loadShader:GL_FRAGMENT_SHADER code:fs];
        _id = glCreateProgram();
        glAttachShader(_id, cvs);
        glAttachShader(_id, cfs);
        glLinkProgram(_id);
        
        GLint logLength;
        glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &logLength);
        if(logLength > 0) {
            GLchar *log = malloc(logLength);
            glGetProgramInfoLog(_id, logLength, &logLength, log);
            NSLog(@"%@ link log:\n%s", desc, log);
            free(log);
        }
        
        GLint status;
        glGetProgramiv(_id, GL_LINK_STATUS, &status);
        if(status == 0) {
            NSLog(@"Failed to link %@", desc);
        }
        
        glDeleteShader(cvs);
        glDeleteShader(cfs);
    }
    return self;
}

- (void)dealloc {
    [_name release];
    glDeleteProgram(_id);
    [super dealloc];
}

- (NSString*)name { return _name; }

- (void)bind {
    glUseProgram(_id);
}

- (void)unbind {
    glUseProgram(0);
}

- (GLint)uniformLocation:(NSString*)name {
    GLint location = glGetUniformLocation(_id, [name UTF8String]);
    if(location < 0)  NSLog(@"No such uniform named %@ in %@\n", name, _name);
    return location;
}

- (void)setUniformInt:(int)i forName:(NSString*)name {
    glUniform1i([self uniformLocation:name], i);
}
- (void)setUniformFloat:(float)f forName:(NSString*)name {
    glUniform1f([self uniformLocation:name], f);
}

@end
