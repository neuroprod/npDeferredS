//
//  npCamera.h
//  emptyExample
//
//  Created by Kris Temmerman on 23/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef emptyExample_npCamera_h
#define emptyExample_npCamera_h

#include "npIncludes.h"


class npCamera
{

public:
    npCamera(){};
      ofMatrix4x4 perspectiveInvMatrix;
    ofMatrix4x4 worldMatrix;
    ofMatrix4x4 normalWorldMatrix;
    	ofMatrix4x4 worldInv;
    ofMatrix4x4 perspectiveMatrix;

		ofMatrix4x4 lightMatrix1;
		ofMatrix4x4 lightMatrix2;
		ofMatrix4x4 lightMatrix3;		
		ofMatrix4x4 lightMatrix4;
		
};

#endif
