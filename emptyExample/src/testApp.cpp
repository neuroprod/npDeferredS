#include "testApp.h"
#include "GLErrorCheck.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(60);
    
	srand(3);

	terain.setup(ofToDataPath("3DAssets/Terain.png"));


	girl.setup();
	girl.terain =  &terain;
	
	camera.setup();
	camera.mainCharacter =&girl;

	ofBackground(0, 0, 0);
    
    npMaterial m;
    m.hasColor =true;
    m.hasUV =false;
    m.r =0.9f;
    m.g =0.9f;
    m.b =0.9f;
    for (int i=0;i<80;i++)
    {
        npSphere *t =new npSphere();
        t->setup(m,(float) rand()/RAND_MAX*1.0+0.5);
        t->setPos (((float) rand()/RAND_MAX -0.5)*20, ((float) rand()/RAND_MAX -0.5)*20, ((float) rand()/RAND_MAX -0.5)*20);
        spheres.push_back((npMesh *)t);
    
    }
    for (int i=0;i<40;i++)
    {
    
        npPointLight *p = new npPointLight();
        
		if (i==0)
		{
		
		p->setup(20,(float) rand()/RAND_MAX,(float) rand()/RAND_MAX ,(float) rand()/RAND_MAX ,1);
		}
		else
		{
		
		p->setup(5,(float) rand()/RAND_MAX,(float) rand()/RAND_MAX ,(float) rand()/RAND_MAX ,0.2f);
		}
	



      p->setPos (((float) rand()/RAND_MAX -0.5)*20, ((float) rand()/RAND_MAX -0.5)*20, ((float) rand()/RAND_MAX -0.5)*20);
         //p->setPos (0,0,0);
        pLights.push_back(p );
    
    
    }
    
    
	

  
    
	boneMeshRenderer.setup();
    rendererColor.setup();

    deferredBuffer.setup(ofGetScreenWidth(),ofGetScreenHeight());
    
  
    plRenderer.setup(ofGetScreenWidth(),ofGetScreenHeight());
    plRenderer.depthTexture =deferredBuffer.depthTexture;
    plRenderer.normalTexture=deferredBuffer.normalTexture;
    
    
    
    deferredFinal.depthTexture =deferredBuffer.depthTexture;
    deferredFinal.normalTexture =deferredBuffer.normalTexture;
    deferredFinal.colorTexture =deferredBuffer.colorTexture;
    deferredFinal.pointLightTexture = plRenderer.pointLightTexture;
   
    
    
    
    
    deferredFinal.setup("DeferredShaderFinal");
    
    GLErrorCheck::test("setup end");
   
	dirLight.lookAt.set(0,0,0);
	dirLight.pos.set(100,200,0);
	dirLight.update();
	deferredFinal.dirLight =&dirLight;



	previousTime=ofGetElapsedTimeMicros();
	currentTime =ofGetElapsedTimeMicros();
}



//--------------------------------------------------------------
void testApp::update(){
	
	currentTime =ofGetElapsedTimeMicros();
	unsigned long timeStep =currentTime -previousTime;   
	previousTime  = currentTime;
	//
	girl.update(timeStep);

	camera.update();


	
	//light update


    // main draw;
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
	glClearColor(0.2f,0.2f,0.2f,1.0f);
    deferredBuffer.start();
		rendererColor.start(&camera);

		for (int i=0;i< terain.terrainLowRes.size();i++)
			{
			rendererColor.draw( terain.terrainLowRes[i]);
			}

			for (int i=0;i< spheres.size();i++)
			{
				rendererColor.draw( spheres[i]);
			}
			for (int i=0;i< pLights.size();i++)
			{
				rendererColor.draw( &pLights[i]->drawSphere);
			}
    
		rendererColor.stop();

		boneMeshRenderer.start(&camera);
			boneMeshRenderer.draw(&girl.charMesh);
		boneMeshRenderer.stop();
    deferredBuffer.stop();
 
   
	//pointlights draw
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);
	glCullFace(GL_FRONT);
	plRenderer.draw(pLights ,camera);
	glCullFace(GL_BACK);
    glDisable (GL_BLEND);
    
	
	GLErrorCheck::test("update end");
   
}

//--------------------------------------------------------------
void testApp::draw(){
	
 
   deferredFinal.draw(&camera);

   GLErrorCheck::test("draw end");
 // cout << ofGetFrameRate()<<endl ;
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
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}
