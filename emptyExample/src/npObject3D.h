//
//  npObject3D.h
//  emptyExample
//
//  Created by Kris Temmerman on 24/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef emptyExample_npObject3D_h
#define emptyExample_npObject3D_h
class npObject3D
{
    public:
    npObject3D(){};
    
    
    
    ofMatrix4x4 objectMatrix;
    ofMatrix4x4 normalMatrix;
    float x;
    float y;
    float z;
 
	

    void calculateNormalMatrix()
    {
	
        ofQuaternion q = objectMatrix.getRotate();
        q.inverse();
        normalMatrix.makeRotationMatrix(q);
		
        
    }
    void setPos(float _x, float _y,float _z)
    {
        x =_x;
        y =_y;
        z =_z;
        objectMatrix.makeTranslationMatrix(ofVec3f(x,y,z));
        calculateNormalMatrix();
    
    }

};


#endif
