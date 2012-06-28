#include "npDirectionalLight.h"


npDirectionalLight::npDirectionalLight(void)
{
}


npDirectionalLight::~npDirectionalLight(void)
{
}

void npDirectionalLight::update()
{
	dir = lookAt -pos;
	dir.normalize();


}