//
//  npSphere.cpp
//  emptyExample
//
//  Created by Kris Temmerman on 24/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "npSphere.h"


void npSphere::setup(npMaterial mat, float _radius  ,int _segmentsW ,int _segmentsH)
{



 
    material = mat;
    bool hasColor = false;
     bool hasUV = false;
    float r;
    float g;
    float b;
    stride  =6;
    if (material.hasColor)
    {
    
        hasColor  =true;
        r =material.r;
        g =material.g;
        b =material.b;
        stride +=3;
    
    }if (material.hasUV)    {
    
        hasUV  =true;
        stride  +=2;
    }
        
    
    
    
    numVertices  =(_segmentsH + 1) * (_segmentsW + 1);
    vertices  = new float[numVertices*stride ]; 
    numIndices =(_segmentsH - 1) * _segmentsW * 6;
    indices  =new unsigned int [numIndices ];
    int triIndex =0;
    int vertcount =0;
    
    
    
    for (int j = 0; j <= _segmentsH; ++j) {
        float  horangle  = 3.1415 * j / _segmentsH;
        float z  = -_radius * cos(horangle);
        float  ringradius  = _radius * sin(horangle);
        
        for (int i = 0; i <= _segmentsW; ++i) {
            float verangle  = 2 * 3.1415* i / _segmentsW;
            float  x  = ringradius * cos(verangle);
            float y  = ringradius * sin(verangle);
            float  normLen  = 1 / sqrt(x * x + y * y + z * z);
            
            
            vertices[vertcount++] =  x ;
            vertices[vertcount++] =  y ;
            vertices[vertcount++] =  z;
            
            
            
            vertices[vertcount++] =  x*normLen;
            vertices[vertcount++] =  y*normLen;
            vertices[vertcount++] =  z*normLen;
            
            if (hasColor)
            {
                vertices[vertcount++] =  r;
                vertices[vertcount++] =  g;
                vertices[vertcount++] =  b;
            
            
            }
            
            
            
            if (hasUV)
            {
                cout << "implement UV Sphere ";
            
                vertices[vertcount++] =  0;
                vertices[vertcount++] =  0;
            }
            
            
            
            if (i > 0 && j > 0) {
                int  a = (_segmentsW + 1) * j + i;
                int  b  = (_segmentsW + 1) * j + i - 1;
                int  c = (_segmentsW + 1) * (j - 1) + i - 1;
                int  d  = (_segmentsW + 1) * (j - 1) + i;
                
                if (j == _segmentsH) {
                    indices[triIndex++] = a;
                    indices[triIndex++] = c;
                    indices[triIndex++] = d;
                }
                else if (j == 1) {
                    indices[triIndex++] = a;
                    indices[triIndex++] = b;
                    indices[triIndex++] = c;
                }
                else {
                    indices[triIndex++] = a;
                    indices[triIndex++] = b;
                    indices[triIndex++] = c;
                    indices[triIndex++] = a;
                    indices[triIndex++] = c;
                    indices[triIndex++] = d;
                }
            }
            
            
            
        }
        
        
        
    }
    
    
    
  
  
    
  
    
    
    
    
    
    createBuffers();
	delete [ ] indices;
	indices =NULL;

	delete []vertices;
	vertices =NULL;




}