#pragma once
#include "npIncludes.h"
#include "btBulletDynamicsCommon.h"
#include "GameCamera.h"
class PhysicsDebugDrawer: public btIDebugDraw
{
public :
	PhysicsDebugDrawer(){};

	void setup();
	void draw(const GameCamera & cam);
	vector <float > data;

	virtual void drawLine(const btVector3& from,const btVector3& to,const btVector3& color);

	virtual void	drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color){};

	virtual void	reportErrorWarning(const char* warningString) {};

	virtual void	draw3dText(const btVector3& location,const char* textString) {};
	
	virtual void	setDebugMode(int debugMode){};
	
	virtual  int		getDebugMode()const{return 1;} ;

	GLint program;

    GLint uPerspectiveMatrix;
    GLint uWorldMatrix;

	  enum {
        ATTRIB_VERTEX,
        ATTRIB_NORMAL,
        ATTRIB_COLOR,
    };
};