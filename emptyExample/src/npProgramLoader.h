//
//  npProgramLoader.h
//  displaylist
//
//  Created by Kris Temmerman on 02/10/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef displaylist_npProgramLoader_h
#define displaylist_npProgramLoader_h

#include "npIncludes.h"

#include "npTextFileLoader.h"

using namespace std;



class npProgramLoader
{
    
public:
    npProgramLoader();
    ~npProgramLoader();
    
    GLuint program;
    GLuint loadProgram(string shader);
    void linkProgram();
    
};

#endif
