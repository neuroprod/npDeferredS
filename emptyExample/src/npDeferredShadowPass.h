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
	GLint uLight2Matrix;



    GLint uNormalTexture;
    GLint uDepthTexture;
	GLint uShadowTexture1;
	GLint uShadowTexture2;
	GLint uAONoiseTexture;

    GLuint depthTexture;
    GLuint normalTexture;
	GLuint shadowTexture1;
	GLuint shadowTexture2;
	GLuint AONoiseTexture;

    GLuint program;
   
	GLuint shadowTexture;
  GLuint fboMain;
  GLuint fboBlur;


	enum {
    ATTRIB_VERTEX_FS,
    ATTRIB_UV_FS,
};

};

