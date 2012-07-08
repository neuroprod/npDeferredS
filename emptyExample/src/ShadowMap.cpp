#include "ShadowMap.h"


void ShadowMap::setup()
{

fbo1.setup(2048,2048);


shadowTexture1 =fbo1.texture;

fbo2.setup(2048,2048);


shadowTexture2 =fbo2.texture;

fbo3.setup(2048,2048);


shadowTexture3 =fbo3.texture;

};
void ShadowMap::start1( )
{


	fbo1.start();
};





void ShadowMap::stop1()
{

	fbo1.stop();
};

void ShadowMap::start2( )
{


	fbo2.start();
};





void ShadowMap::stop2()
{

	fbo2.stop();
};

void ShadowMap::start3( )
{


	fbo3.start();
};





void ShadowMap::stop3()
{

	fbo3.stop();
};