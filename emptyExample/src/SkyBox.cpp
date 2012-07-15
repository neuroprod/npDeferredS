#include "SkyBox.h"

void SkyBox::setup(){

colorBox.setup();
elementBox.setup();

}

void SkyBox::update(){

	elementBox.update();
	colorBox.update();
}

void SkyBox::draw(const GameCamera &camera){

	colorBox.draw(camera);
	
	elementBox.draw(camera);
}