#pragma once


#include "npIncludes.h"
#include "npBoneMesh.h"
#include "npCamera.h"

class npBoneMeshRenderer
{
public:
	npBoneMeshRenderer(void);
	~npBoneMeshRenderer(void);

	 void setup();
    
    
    void start(npCamera *cam);
    void draw(const npBoneMesh *mesh);
    void stop();
    
   

    GLint program;
    GLint uNormalMatrix;
    // GLint uNormalWorldMatrix;
    GLint uPerspectiveMatrix;
    GLint uWorldMatrix;
    GLint uObjectMatrix;
     GLint  uBoneMatrixList;
    
    enum {
        ATTRIB_VERTEX,
        ATTRIB_NORMAL,
        ATTRIB_UV,
		ATTRIB_IDS,
		ATTRIB_WEIGHTS};
};

