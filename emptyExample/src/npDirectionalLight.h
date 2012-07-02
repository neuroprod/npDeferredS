#pragma once

#include "npIncludes.h"

class npDirectionalLight
{
public:
	npDirectionalLight(void);
	~npDirectionalLight(void);
	

	void update();
	
	ofVec3f pos;
	ofVec3f lookAt;

	ofVec3f dir;





};

