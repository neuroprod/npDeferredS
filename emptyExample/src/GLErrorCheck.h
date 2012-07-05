//
//  OpenGLErrorChek.h
//  displaylist
//
//  Created by Kris Temmerman on 22/09/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef displaylist_GLErrorCheck_h
#define displaylist_GLErrorCheck_h

#ifdef IOS 

#include <iostream>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

#elseif

#include "ofMain.h

#endif
using namespace std;
class GLErrorCheck
{


public:
    
    static void  test(int pos =0) 
    {
      
        
        
        GLenum errCode;
        errCode = glGetError();
        if ((errCode ) != GL_NO_ERROR) {
            cout << "\n GL ERROR at: "<< pos;
            cout << " code: "<< errCode;
            if(errCode == GL_INVALID_ENUM)cout <<" GL_INVALID_ENUM";
            if(errCode == GL_INVALID_VALUE)cout <<"GL_INVALID_VALUE";
            if(errCode == GL_INVALID_OPERATION)cout <<"GL_INVALID_OPERATION";
            if(errCode == GL_OUT_OF_MEMORY)cout <<"GL_OUT_OF_MEMORY";
            cout <<"\n";
        }};






    static void test(string pos ="") 
    {
    


        GLenum errCode;
        errCode = glGetError();
        if ((errCode ) != GL_NO_ERROR) {
        cout << "\n GL ERROR at: "<< pos;
        cout << " code: "<< errCode;
        if(errCode == GL_INVALID_ENUM)cout <<" GL_INVALID_ENUM";
        if(errCode == GL_INVALID_VALUE)cout <<"GL_INVALID_VALUE";
        if(errCode == GL_INVALID_OPERATION)cout <<"GL_INVALID_OPERATION";
        if(errCode == GL_OUT_OF_MEMORY)cout <<"GL_OUT_OF_MEMORY";
        cout <<"\n";
        }
    };




};

#endif
