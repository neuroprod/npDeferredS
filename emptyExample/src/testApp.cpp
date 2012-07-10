#include "testApp.h"
#include "GLErrorCheck.h"

//--------------------------------------------------------------
void testApp::setup(){

	/*int units;
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,  &units);
	cout <<"maxTexture units " <<units<< endl;

	*/
	ofSetFrameRate(60);
    

	terrainFunctions.setup();
	chunkHandler.terrainFunctions =&terrainFunctions;
	chunkHandler.setup();
	


	girl.setup();
	girl.terrainFunctions =  &terrainFunctions;

	camera.setup();
	camera.mainCharacter =&girl;
	camera.terrainFunctions  =   &terrainFunctions;
	ofBackground(0, 0, 0);
   

    
  
		
  
    
	boneMeshRenderer.setup();

    rendererColor.setup();

	renderTexture.setup();
	
	terrainRenderer.setup();
	terrainRenderer.vegMapTexture=chunkHandler.terrainFBO.texture;
	
    deferredBuffer.setup(SCREEN_W,SCREEN_H);
    
  
    plRenderer.setup(SCREEN_W,SCREEN_H);
    plRenderer.depthTexture =deferredBuffer.depthTexture;
    plRenderer.normalTexture=deferredBuffer.normalTexture;
    
   

    deferredFinal.depthTexture =deferredBuffer.depthTexture;
    deferredFinal.normalTexture =deferredBuffer.normalTexture;
    deferredFinal.colorTexture =deferredBuffer.colorTexture;
    deferredFinal.pointLightTexture = plRenderer.pointLightTexture;
    deferredFinal.setup("DeferredShaderFinal");
    
 
   
	dirLight.lookAt.set(0,0,0);
	dirLight.pos.set(750,750,0);

	deferredFinal.dirLight =&dirLight;
	

	shadowMap.setup();

	 shadowPass.setup("DeferredShaderShadowPass");
    
	shadowPass.depthTexture =deferredBuffer.depthTexture;
	shadowPass.normalTexture =deferredBuffer.normalTexture;
	shadowPass.shadowTexture1 =shadowMap.shadowTexture1;
	shadowPass.shadowTexture2 =shadowMap.shadowTexture2;
	shadowPass.shadowTexture3 =shadowMap.shadowTexture3;

	deferredFinal.shadowTexture =shadowPass.shadowTexture;
	shadowMeshRenderer.setup();
	shadowBoneRenderer.setup();
	previousTime=ofGetElapsedTimeMicros();
	currentTime =ofGetElapsedTimeMicros();


	GLErrorCheck::test("setup end");
	cout << "setupDone"<< endl;
}



//--------------------------------------------------------------
void testApp::update(){
	 
	currentTime =ofGetElapsedTimeMicros();
	 timeStep =currentTime -previousTime;   
	previousTime  = currentTime;
	
	float cycleTime =  (currentTime/1000)%60000;
	dayTime = cycleTime/60000 ;
	dayTime -=0.5;
	dayTime *=2;
	if (dayTime<0)dayTime *=-1;
	//dayTime =0;
	//cout <<dayTime<<endl;
	//
	// PRE RENDER UPDATE
	//
	//
	girl.update(timeStep);
	dirLight.update();

	camera.lightDir = dirLight.dir;
	camera.setMouse(mouseIsDown,vecMouseMove.x,vecMouseMove.y);
	camera.update(timeStep);
	chunkHandler.update(camera.lookAtPos,camera.camPos);
	
	//
	//
	// FRAME  BUFFERS
	//
	//
	
	//
    // SHADOW MAP DRAW;
	//
	 glEnable(GL_DEPTH_TEST);
	glPolygonOffset(4.2f,1.2f);
	glEnable(GL_POLYGON_OFFSET_FILL);
	
	glEnable(GL_ALPHA_TEST);
	
			glAlphaFunc(GL_GREATER,0.5f);

//MAP 1
		shadowMap.start1();
		shadowMeshRenderer.start(camera,1);
			for (int i=0;i< chunkHandler.chunks.size();i++)
			{
				 if(chunkHandler.chunks[i]->detailLevel==1)
				{
			
			
					shadowMeshRenderer.draw( chunkHandler.chunks[i]->terrain);
					for (int j=0;j< chunkHandler.chunks[i]->detail1Objects.size();j++)
					{
				
				
						shadowMeshRenderer.draw(	chunkHandler.chunks[i]->detail1Objects[j]);
					}
			
				 }
				 
		}
		shadowMeshRenderer.stop();
			glDisable(GL_ALPHA_TEST);
		shadowBoneRenderer.start(camera);
		shadowBoneRenderer.draw(&girl.charMesh);
		shadowBoneRenderer.stop();
			
	glEnable(GL_ALPHA_TEST);
	shadowMap.stop1();
//MAP 2
	shadowMap.start2();
		shadowMeshRenderer.start(camera,2);
			for (int i=0;i< chunkHandler.chunks.size();i++)
			{
				 if(chunkHandler.chunks[i]->detailLevel==1 || chunkHandler.chunks[i]->detailLevel==2)
				{
			
			
					shadowMeshRenderer.draw( chunkHandler.chunks[i]->terrain);
					for (int j=0;j< chunkHandler.chunks[i]->detail1Objects.size();j++)
					{
				
				
						shadowMeshRenderer.draw(	chunkHandler.chunks[i]->detail1Objects[j]);
					}
					for (int j=0;j< chunkHandler.chunks[i]->detail2Objects.size();j++)
					{
				
				
						shadowMeshRenderer.draw(	chunkHandler.chunks[i]->detail2Objects[j]);
					}
				 }
				 
		}
		shadowMeshRenderer.stop();
			
		
	shadowMap.stop2();
//MAP 3
		shadowMap.start3();
		shadowMeshRenderer.start(camera,3);
			for (int i=0;i< chunkHandler.chunks.size();i++)
			{
				 if(chunkHandler.chunks[i]->detailLevel>0)
				{
			
			
					shadowMeshRenderer.draw( chunkHandler.chunks[i]->terrain);
					for (int j=0;j< chunkHandler.chunks[i]->detail3Objects.size();j++)
					{
				
				
					shadowMeshRenderer.draw(	chunkHandler.chunks[i]->detail3Objects[j]);
					}
					for (int j=0;j< chunkHandler.chunks[i]->detail2Objects.size();j++)
					{
				
				
						shadowMeshRenderer.draw(	chunkHandler.chunks[i]->detail2Objects[j]);
					}
					for (int j=0;j< chunkHandler.chunks[i]->detail1Objects.size();j++)
					{
				
				
						shadowMeshRenderer.draw(	chunkHandler.chunks[i]->detail1Objects[j]);
					}
				 }
				 
		}
		shadowMeshRenderer.stop();
		
		
	shadowMap.stop3();

	glDisable(GL_ALPHA_TEST);
	glViewport(0,0 , SCREEN_W,SCREEN_H);
	glDisable(GL_POLYGON_OFFSET_FILL);
	//
    // MAIN DRAW;
	//
   
   
	glClearColor(0.8f*(1.0-dayTime*0.8 ),0.8f*(1.0-dayTime*0.8),1.0f*(1.0-dayTime*0.8),1.0f);
    deferredBuffer.start();
	
		terrainRenderer.start(camera);
			for (int i=0;i< chunkHandler.chunks.size();i++)
			{
				
				if (chunkHandler.chunks[i]->detailLevel!=0)
				{
					terrainRenderer.draw( chunkHandler.chunks[i]->terrain,chunkHandler.chunks[i]->detailLevel);
				}
				
			}
		terrainRenderer.stop();
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER,0.5f);
		
			renderTexture.start(camera);
			for (int i=0;i< chunkHandler.chunks.size();i++)
			{
				 if(chunkHandler.chunks[i]->detailLevel>0)
				{
				
					if(chunkHandler.chunks[i]->detailLevel==1)
					{
						for (int j=0;j< chunkHandler.chunks[i]->detail1Objects.size();j++)
						{
				
					
							renderTexture.draw(	chunkHandler.chunks[i]->detail1Objects[j]);
						}
					}
					if(chunkHandler.chunks[i]->detailLevel==2)
					{
						for (int j=0;j< chunkHandler.chunks[i]->detail2Objects.size();j++)
						{
				
					
							renderTexture.draw(	chunkHandler.chunks[i]->detail2Objects[j]);
						}
					}	
				
					if(chunkHandler.chunks[i]->detailLevel==3)
					{
						for (int j=0;j< chunkHandler.chunks[i]->detail3Objects.size();j++)
						{
							renderTexture.draw(	chunkHandler.chunks[i]->detail3Objects[j]);
						}
					}
				 }
			}
			renderTexture.stop();
		glDisable(GL_ALPHA_TEST);
	
	/*	rendererColor.start(camera);
	
		

	for (int i=0;i< chunkHandler.chunks.size();i++)
		{
				 if(chunkHandler.chunks[i]->detailLevel>0)
				{
				
					for (int j=0;j< chunkHandler.chunks[i]->objects.size();j++)
					{
					
						rendererColor.draw(chunkHandler.chunks[i]->objects[j]);
					}
				 }
	
		}
		rendererColor.stop();
		*/

		
		boneMeshRenderer.start(camera);
			boneMeshRenderer.draw(&girl.charMesh);
		boneMeshRenderer.stop();
    deferredBuffer.stop();
 
   
	//
    // POINTLIGHT DRAW;
	//
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);
	glCullFace(GL_FRONT);
	glEnable(GL_CULL_FACE);
	plRenderer.start(camera);
		for (int i=0;i< chunkHandler.chunks.size();i++)
		{
			if(chunkHandler.chunks[i]->detailLevel==1 || chunkHandler.chunks[i]->detailLevel==2)
			{
				for (int j=0;j< chunkHandler.chunks[i]->pLights.size();j++)
				{	
					plRenderer.draw(chunkHandler.chunks[i]->pLights[j] );
				}
			}
		}
	plRenderer.stop();
	glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);
    glDisable (GL_BLEND);
    

	 shadowPass.draw(camera );
	
	GLErrorCheck::test("update end");
 
}

//--------------------------------------------------------------
void testApp::draw(){
	
	//deferredFinal.shadowTexture =shadowMap.fbo1.colorTexture;

deferredFinal.draw(camera, dayTime);//dayTime

   GLErrorCheck::test("draw end");

}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
	switch (key) {
		case OF_KEY_UP: 
			girl.setKey(MainCharacter::FORWARD_DOWN);
		
        break;
		case OF_KEY_LEFT: 
		
		girl.setKey(MainCharacter::LEFT_DOWN);
        break;
		case OF_KEY_RIGHT: 
			girl.setKey(MainCharacter::RIGHT_DOWN);
		
        break;
    }
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

	switch (key) {
	case OF_KEY_UP: 

			girl.setKey(MainCharacter::FORWARD_UP);
        break;
		case OF_KEY_LEFT: 
		girl.setKey(MainCharacter::LEFT_UP);
        break;
		case OF_KEY_RIGHT: 
			girl.setKey(MainCharacter::RIGHT_UP);
		
          break;
     
        }
          
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
		
		if ( button ==0)
		{
			vecMouseMove.set(x -vecMouseStart.x,y -vecMouseStart.y);
		}
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
	if ( button ==0)
	{
		vecMouseStart.set(x,y);
		mouseIsDown = true;
	}
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	if ( button ==0)
	{
		mouseIsDown = false;
	}
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}
