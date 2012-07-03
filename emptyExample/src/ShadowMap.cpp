#include "ShadowMap.h"


void ShadowMap::setup()
{

fbo1.setup(2048,2048);


shadowTexture1 =fbo1.texture;

};
void ShadowMap::start( )
{


	fbo1.start();
};





void ShadowMap::stop()
{

	fbo1.stop();
};