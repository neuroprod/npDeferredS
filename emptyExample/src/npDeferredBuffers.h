//
//  npDeferredBuffers.h
//  emptyExample
//
//  Created by Kris Temmerman on 23/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef emptyExample_npDeferredBuffers_h
#define emptyExample_npDeferredBuffers_h
#include "npIncludes.h"
class npDeferredBuffers
{


public:
    npDeferredBuffers(){};
    
    void setup(int w,int h );
    
    void  start();
    void stop();
    
    
    int width;
    int height;
    
    GLuint fbo;	
    
    GLuint depthBuffer;
    
    GLuint depthTexture;
    GLuint colorTexture;	
    GLuint normalTexture;
    
    vector<GLenum> attachments;

};

#endif
