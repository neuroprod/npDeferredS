#include "PhysicsDebugDrawer.h"
#include "npProgramLoader.h"
void PhysicsDebugDrawer::setup()
{
	 npProgramLoader pl;
    program = pl.loadProgram ("DebugShader");

    glBindAttribLocation(program,ATTRIB_VERTEX,"position");

    pl.linkProgram();
    glUseProgram(program);
    
  
    uWorldMatrix = glGetUniformLocation(program,"worldMatrix");
    uPerspectiveMatrix = glGetUniformLocation(program,"perspectiveMatrix");

    glUseProgram(0);

}

void PhysicsDebugDrawer::drawLine(const btVector3& from,const btVector3& to,const btVector3& color)
{

	
	data.push_back( from.x());
	data.push_back( from.y());
	data.push_back( from.z());

	data.push_back( to.x());
	data.push_back( to.y());
	data.push_back( to.z());
}
void  PhysicsDebugDrawer::draw(const GameCamera & cam)
{
	 glUseProgram(program);
    glUniformMatrix4fv(uWorldMatrix, 1, 0,  cam.worldMatrix.getPtr());
    glUniformMatrix4fv(uPerspectiveMatrix, 1, 0,   cam.perspectiveMatrix.getPtr());
   
    glEnableVertexAttribArray(ATTRIB_VERTEX);
	glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, 0, 3*sizeof(GLfloat), data.data());

  

    glDrawArrays(GL_LINES, 0,  data.size()/3);

	//cout << data.size()<<endl;
	data.clear();


	    glDisableVertexAttribArray(ATTRIB_VERTEX);
  //  glDisableVertexAttribArray(ATTRIB_NORMAL);
   //  glDisableVertexAttribArray(ATTRIB_COLOR);

}