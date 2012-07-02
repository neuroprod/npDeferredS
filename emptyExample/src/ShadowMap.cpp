#include "ShadowMap.h"


void ShadowMap::setup()
{

fbo1.setup(1024,1024);


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