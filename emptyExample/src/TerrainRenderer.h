
#ifndef emptyExample_TerrainRenderer_h
#define emptyExample_TerrainRenderer_h

#include "npIncludes.h"
#include "npMesh.h"
#include "npCamera.h"

class TerrainRenderer
{
public:
    TerrainRenderer(){};
    ~TerrainRenderer(){};
    
     
    
    void setup();
    
    
    void start(const npCamera &cam);
    void draw(const npMesh *mesh,int detailLevel);
    void stop();
    
   

    GLint program;
    GLint uNormalMatrix;
    GLint uNormalWorldMatrix;
    GLint uPerspectiveMatrix;
    GLint uWorldMatrix;
    GLint uObjectMatrix;
    
	GLint uVegMapTexture;
	GLint uGrassTexture;
	GLint uDirtTexture;
	GLint uForestTexture;


    GLuint vegMapTexture;
	GLuint dirtTexture;
	GLuint grassTexture;
	GLuint forestTexture;
    enum {
        ATTRIB_VERTEX,
        ATTRIB_NORMAL,
        ATTRIB_UV,
    };
    
};

#endif
