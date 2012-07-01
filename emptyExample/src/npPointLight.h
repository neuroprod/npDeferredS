//
//  npPointLight.h
//  emptyExample
//
//  Created by Kris Temmerman on 23/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef emptyExample_npPointLight_h
#define emptyExample_npPointLight_h

#include "npMesh.h"
#include "npSphere.h"
class npPointLight{
public:
    npPointLight(){};
    ~npPointLight(){};
    void setup(float radius,float  r,float g,float b, float radiusDraw =0);
    void setPos(float _x,float _y,float _z);

	
    npSphere drawSphere;
    npSphere rangeSphere;
	float lightSize;
};

#endif
