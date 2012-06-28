#pragma once


#include "ofMain.h"



#include "npCamera.h"
#include "npMeshRendererColor.h"
#include "npDeferredBuffers.h"
#include "npPointLightRenderer.h"


#include "npDeferredFinal.h"
#include "npSphere.h"
#include "npPointLight.h"
#include "npDirectionalLight.h"

#include "npBoneMeshRenderer.h"
#include "npBoneMesh.h"
#include "npAssimpLoader.h"

class testApp : public ofBaseApp{
	
public:
	
	void setup();
	void update();
	void draw();
	
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	
    vector <npMesh *> spheres;
    vector <npPointLight *> pLights;
	npAssimpLoader aLoader;
	npBoneMesh * girl;
    
    npCamera camera;
    npMeshRendererColor rendererColor;
    npBoneMeshRenderer boneMeshRenderer;


	
	npDeferredBuffers deferredBuffer;
    npDeferredFinal deferredFinal;
    
    npPointLightRenderer plRenderer;
	npDirectionalLight dirLight;
};



