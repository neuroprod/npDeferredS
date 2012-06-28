


attribute vec4 position;
attribute vec4 normal;
attribute vec3 color;


uniform mat4 objectMatrix ;
uniform mat4 normalMatrix ;
uniform mat4 worldMatrix ;
uniform mat4 normalWorldMatrix;
uniform mat4 perspectiveMatrix ;


varying vec3 normal_var;
varying vec3 color_var;


void main()
{

    vec4 localSpace = objectMatrix * position;
    vec4 worldSpace = worldMatrix *localSpace;
    gl_Position = perspectiveMatrix *worldSpace;

    
  
    vec4 normalLok = normalMatrix*normal;
    normal_var =(normalWorldMatrix* normalLok ).xyz; // normalWorldMatrix*
    color_var =color;





}