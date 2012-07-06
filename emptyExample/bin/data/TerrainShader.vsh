


attribute vec2 position;
attribute vec3 color;
attribute vec2 uv;


varying vec2 uv_var;
varying vec3 color_var;


void main()
{

 
    gl_Position = vec4(position,0.0,1.0);

    
  
 
   uv_var =uv;
    color_var =color;





}