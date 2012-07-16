#include "SkyBox.h"

void SkyBox::setup(){

colorBox.setup();
elementBox.setup();
elementBox.light =light;

}

void SkyBox::update(){

	elementBox.update();
	colorBox.update();

}

void SkyBox::draw(const GameCamera &camera,const float &time){

	colorBox.draw(camera,time);
	
	elementBox.draw(camera);
}