#pragma once
#include "npIncludes.h"
#include "npDirectionalLight.h"
#include "npCamera.h"

class npDeferredShadowPass
{


public:
	npDeferredShadowPass(){};
		void setup(string shader);

	void draw(const npCamera &cam);

	float *dataFB;

	
	GLint uPerspectiveInvMatrix;
	GLint uLight1Matrix;




    GLint uNormalTexture;
    GLint uDepthTexture;
	GLint uShadowTexture1;
	GLint uAONoiseTexture;

    GLuint depthTexture;
    GLuint normalTexture;
	GLuint shadowTexture1;
	GLuint AONoiseTexture;

    GLuint program;
   
	enum {
    ATTRIB_VERTEX_FS,
    ATTRIB_UV_FS,
};

};

