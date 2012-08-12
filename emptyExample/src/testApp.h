#pragma once


#include "ofMain.h"



#include "GameCamera.h"
#include "npMeshRendererColor.h"
#include "npMeshRendererText.h"

#include "npDeferredBuffers.h"
#include "npPointLightRenderer.h"


#include "npDeferredFinal.h"
#include "npSphere.h"
#include "npPointLight.h"
#include "npDirectionalLight.h"

#include "npBoneMeshRenderer.h"
#include "MainCharacter.h"
#include "npAssimpLoader.h"

#include "TerrainFunctions.h"
#include "ChunkHandler.h"
#include "Chunk.h"
#include "TerrainRenderer.h"

#include "ShadowMap.h"
#include "npShadowMapMeshRenderer.h"
#include "npShadowMapBoneRenderer.h"
#include "npDeferredShadowPass.h"

#include "PhysicsHandler.h"
#include "SkyBox.h"

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
	

	TerrainFunctions terrainFunctions;

    vector <npMesh *> spheres;
  
	

    MainCharacter girl;
    GameCamera camera;
    npMeshRendererColor rendererColor;
	npMeshRendererText renderTexture;
    npBoneMeshRenderer boneMeshRenderer;
	TerrainRenderer terrainRenderer;
	ChunkHandler chunkHandler;
	
	npDeferredBuffers deferredBuffer;
    npDeferredFinal deferredFinal;
    
    npPointLightRenderer plRenderer;
	npDirectionalLight dirLight;

	ShadowMap shadowMap;
	npShadowMapMeshRenderer shadowMeshRenderer;
	npShadowMapBoneRenderer shadowBoneRenderer;

	unsigned long previousTime;
	unsigned long currentTime;
	unsigned long timeStep;

	float dayTime;
	float colorFactor;

	ofVec2f vecMouseStart;
	ofVec2f vecMouseMove;
	bool mouseIsDown;

	npDeferredShadowPass shadowPass;


	SkyBox skyBox;

	PhysicsHandler *physicsHandler;

	unsigned int frameCount;
 };



