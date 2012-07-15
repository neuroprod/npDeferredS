


attribute vec4 position;

uniform mat4 perspectiveMatrix ;

varying vec2 uv_var;

void main()
{

  
    gl_Position = perspectiveMatrix * position;

    
  
  
  

	uv_var  =vec2(0.1,(position.y*0.5 +0.5)*-0.9);



}