//
//  npTimer.h
//  displaylist
//
//  Created by Kris Temmerman on 20/09/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef displaylist_npTimer_h
#define displaylist_npTimer_h

#include  "ofMain.h"


class npTimer
{
public: 
    npTimer(){ } 
    
    ~npTimer(){} 
    
    static int getCurrentTime() 
    {
      
        return ofGetElapsedTimeMillis(); 
    }
   

};


#endif
