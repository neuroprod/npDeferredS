//
//  npSphere.h
//  emptyExample
//
//  Created by Kris Temmerman on 24/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef emptyExample_npSphere_h
#define emptyExample_npSphere_h
#include "npMesh.h"

class npSphere:public npMesh
{

    public : 
    
    npSphere(){};
    ~npSphere(){};
    
    void setup(npMaterial mat, float radius  =1.0f,int _segmentsW =16,int _segmentsH=12);


};


#endif
