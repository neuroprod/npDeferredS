#include "npMaterial.h" 
#include "GLErrorCheck.h" 

void npMaterial::loadDiffuse(string fileName,GLenum  type ,bool useMipMap )
{
	
	ofImage dif;
    dif.loadImage(fileName);
	hasUV =true;
	hasColor =false;
	
	
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glGenTextures(1,&diffuseTexture);
	glBindTexture(GL_TEXTURE_2D, diffuseTexture);
	// tod fix this of imgage crap
	
	if (!useMipMap)
	{
	glTexImage2D(GL_TEXTURE_2D, 0,  type, dif.width, dif.height, 0,type,GL_UNSIGNED_BYTE,dif.getPixels());
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	}else
	{
	
		gluBuild2DMipmaps(GL_TEXTURE_2D, type, dif.width, dif.height, type,GL_UNSIGNED_BYTE,   dif.getPixels());
		
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,  GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,   GL_LINEAR);
	}
	
	glFinish();
	glBindTexture(GL_TEXTURE_2D, 0);
		
};


void npMaterial::loadNormal(string fileName,GLenum  type ,bool useMipMap )
{

	ofImage dif;
    dif.loadImage(fileName);
	hasUV =true;
	hasColor =false;
	
	
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glGenTextures(1,&normalTexture);
	glBindTexture(GL_TEXTURE_2D, normalTexture);
	// tod fix this of imgage crap

	if (!useMipMap)
	{
	glTexImage2D(GL_TEXTURE_2D, 0,  type, dif.width, dif.height, 0,type,GL_UNSIGNED_BYTE,dif.getPixels());
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	}else
	{
	
		gluBuild2DMipmaps(GL_TEXTURE_2D, type, dif.width, dif.height, type,GL_UNSIGNED_BYTE,   dif.getPixels());
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,   GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,   GL_LINEAR);
	}
	glFinish();
	glBindTexture(GL_TEXTURE_2D, 0);
};
void npMaterial::loadTexture(string fileName,GLenum  type ,bool useMipMap )
{

	ofImage dif;
    dif.loadImage(fileName);
	hasUV =true;
	hasColor =false;
	
	
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glGenTextures(1,&diffuseTexture);
	glBindTexture(GL_TEXTURE_2D, diffuseTexture);
	// tod fix this of imgage crap

	if (!useMipMap)
	{
	glTexImage2D(GL_TEXTURE_2D, 0,  type, dif.width, dif.height, 0,type,GL_UNSIGNED_BYTE,dif.getPixels());
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	}else
	{
	
		gluBuild2DMipmaps(GL_TEXTURE_2D, type, dif.width, dif.height, type,GL_UNSIGNED_BYTE,   dif.getPixels());
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,  GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,   GL_LINEAR_MIPMAP_LINEAR);
	}
	glFinish();
	glBindTexture(GL_TEXTURE_2D, 0);
};