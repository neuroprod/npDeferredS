#pragma once


#include "ofMain.h"



#include "GameCamera.h"
#include "npMeshRendererColor.h"
#include "npDeferredBuffers.h"
#include "npPointLightRenderer.h"


#include "npDeferredFinal.h"
#include "npSphere.h"
#include "npPointLight.h"
#include "npDirectionalLight.h"

#include "npBoneMeshRenderer.h"
#include "MainCharacter.h"
#include "npAssimpLoader.h"

#include "Terrain.h"


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
	

	Terrain terain;

    vector <npMesh *> spheres;
    vector <npPointLight *> pLights;
	

    MainCharacter girl;
    GameCamera camera;
    npMeshRendererColor rendererColor;
    npBoneMeshRenderer boneMeshRenderer;


	
	npDeferredBuffers deferredBuffer;
    npDeferredFinal deferredFinal;
    
    npPointLightRenderer plRenderer;
	npDirectionalLight dirLight;


	unsigned long previousTime;
	unsigned long currentTime;
};



