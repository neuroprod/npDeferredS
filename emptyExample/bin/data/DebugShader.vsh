


attribute vec4 position;
//attribute vec4 normal;
//attribute vec3 color;



uniform mat4 worldMatrix ;

uniform mat4 perspectiveMatrix ;





void main()
{

 
    vec4 worldSpace = worldMatrix *position;
    gl_Position = perspectiveMatrix *worldSpace;

    
  






}