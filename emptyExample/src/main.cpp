
#include "testApp.h"
#include "ofMain.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){

    ofAppGlutWindow window;
  //  window.setGlutDisplayString("rgba double depth samples>=16");
	ofSetupOpenGL(&window, 1920,1080, OF_WINDOW);			// <-------- setup the GL context

	ofRunApp( new testApp());

}
