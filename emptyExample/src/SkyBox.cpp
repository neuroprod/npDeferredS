#include "SkyBox.h"

void SkyBox::setup(){

colorBox.setup();

}

void SkyBox::update(){

	colorBox.update();
}

void SkyBox::draw(const GameCamera &camera){

	
	colorBox.draw(camera);
}