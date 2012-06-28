//
//  npProgramLoader.cpp
//  displaylist
//
//  Created by Kris Temmerman on 02/10/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//


#include "npProgramLoader.h"
npProgramLoader::npProgramLoader()
{
    
    
}
npProgramLoader::~npProgramLoader()
{
    
    
    
}
GLuint npProgramLoader::loadProgram(string  shader)
{
    
    GLuint vertShader, fragShader;
  
    GLint logLength;
    
    program = glCreateProgram();
    
      
    
    const GLchar *sourceV;
    sourceV=npTextFileLoader::loadChar  (shader,"vsh");
    
    vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &sourceV, NULL);
    glCompileShader(vertShader);
    

    
    
    
    glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 1)
    {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetShaderInfoLog(vertShader, logLength, &logLength, log);
        cout << "VertexShader compile log:"<<  log<< "\n";
        delete log;
    }
    
      const GLchar *sourceF;
    sourceF = npTextFileLoader::loadChar  (shader,"fsh");
    if (!sourceF)
    {
        cout << "fragment shader not found";
    }
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &sourceF, NULL);
    glCompileShader(fragShader);
    
        
    
    glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 1)
    {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetShaderInfoLog(fragShader, logLength, &logLength, log);
        cout << "FragmentShader compile log:"<<  log<< "\n";
        delete log;
    }
    
    glAttachShader(program, vertShader);
    
    glAttachShader(program, fragShader);
    
    
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    
    
  // delete [] sourceF;
  
   //  delete [] sourceV;
    
    return program;
    
}
void npProgramLoader::linkProgram()
{
    glLinkProgram(program);
    
    
    GLint logLength;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 1)
    {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(program, logLength, &logLength, log);
        cout << "Program link log:" << log<<"\n";
        free(log);
    }
    
    
    
    
}