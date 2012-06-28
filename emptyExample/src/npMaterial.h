//
//  npMaterial.h
//  emptyExample
//
//  Created by Kris Temmerman on 24/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef emptyExample_npMaterial_h
#define emptyExample_npMaterial_h
#include "npIncludes.h" 
class npMaterial
{

public: 
    npMaterial(){};
    
    bool hasColor;
     bool hasUV;
    float r;
    float g;
    float b;
    
    
    float specular;
    float shininess;

    GLuint diffuseTexture;
    

};

#endif
