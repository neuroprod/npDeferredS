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
    npObject3D(){isMultiObject =false;detailLevel=1;};
    
    
    
    ofMatrix4x4 objectMatrix;
    ofMatrix4x4 normalMatrix;
    float x;
    float y;
    float z;
    bool isMultiObject;
    int detailLevel ;
	vector<ofMatrix4x4 > objectMatrices;
	
	vector<ofMatrix4x4 > normalMatrices;

    void calculateNormalMatrix()
    {
		normalMatrices.clear();
		if (isMultiObject)
		{
			for(int i=0;i< objectMatrices.size();i++)
			{
				ofQuaternion q = objectMatrices[i].getRotate();
				q.inverse();
				normalMatrix.makeRotationMatrix(q);
				normalMatrices.push_back( normalMatrix);
			}
		}else{

        ofQuaternion q = objectMatrix.getRotate();
        q.inverse();
        normalMatrix.makeRotationMatrix(q);
		}
        
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
