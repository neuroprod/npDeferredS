


attribute vec4 position;
attribute vec2 uv;

uniform mat4 perspectiveMatrix ;
uniform mat4 objectMatrix ;

varying vec2 uv_var;

void main()
{

  vec4 objectSpace = objectMatrix* vec4(position.x,position.y,position.z,1.0);
    gl_Position = perspectiveMatrix * objectSpace;

    
  
  
  

	uv_var  =uv;



}