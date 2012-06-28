#include "testApp.h"
#include "GLErrorCheck.h"
#include "npAssimpLoader.h"
//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(60);
    
   srand(3);

	aLoader.load(ofToDataPath("vrouwAnimeTest2.dae"));
	girl  = aLoader.boneMeshes[0];
	girl->setPos(0,0,0);
	girl->material.loadDiffuse("3DAssets/vrouwFinal.png");
	ofBackground(0, 0, 0);
    
    npMaterial m;
    m.hasColor =true;
    m.hasUV =false;
    m.r =0.9f;
    m.g =0.9f;
    m.b =0.9;
    for (int i=0;i<30;i++)
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
		
		p->setup(5,(float) rand()/RAND_MAX,(float) rand()/RAND_MAX ,(float) rand()/RAND_MAX ,0.5);
		}
	



      p->setPos (((float) rand()/RAND_MAX -0.5)*20, ((float) rand()/RAND_MAX -0.5)*20, ((float) rand()/RAND_MAX -0.5)*20);
         //p->setPos (0,0,0);
        pLights.push_back(p );
    
    
    }
    
    
   camera.perspectiveMatrix.makePerspectiveMatrix(60, (float)ofGetScreenWidth()/(float)ofGetScreenHeight(), 1, 200);
 
    camera.perspectiveInvMatrix.makeInvertOf(camera.perspectiveMatrix);
  
    
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
	dirLight.pos.set(100,100,0);
	dirLight.update();
	deferredFinal.dirLight =&dirLight;
}



//--------------------------------------------------------------
void testApp::update(){
	//
	girl->update();



    // cam update;
    camera.worldMatrix.makeLookAtViewMatrix(ofVec3f(0,0,20), ofVec3f(0,0,0), ofVec3f (0,1,0));
	camera.worldMatrix.glRotate((float)ofGetFrameNum()/2,0,1,0);
    ofQuaternion q = camera.worldMatrix.getRotate();
   q.inverse();
    camera.normalWorldMatrix.makeRotationMatrix(q);
	//camera.normalWorldMatrix.postMultTranslate( camera.worldMatrix.getTranslation());

	//camera.normalWorldMatrix.makeInvertOf(camera.normalWorldMatrix);
	//scene update

	
	//light update


    // main draw;
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
	glClearColor(0.5,0.5,0.5,1.0);
    deferredBuffer.start();
		rendererColor.start(&camera);
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
			boneMeshRenderer.draw(girl);
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

		case 'a': // up key
          		
        case 'z':
           
            break;
        case'e':
          
            break;
        case 'f':
            if(ofGetWindowMode() == 0){
                ofSetFullscreen(true);
            }else{ 
                ofSetFullscreen(false);
        }
            
    }
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
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
