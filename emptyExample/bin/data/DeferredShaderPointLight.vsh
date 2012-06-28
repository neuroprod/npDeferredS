




attribute vec4 position;
attribute vec4 normal;
attribute vec3 color;


uniform mat4 objectMatrix ;
uniform mat4 normalMatrix ;
uniform mat4 worldMatrix ;
uniform mat4 perspectiveMatrix ;

uniform vec3 center;


varying vec3 center_var;
varying vec3 color_var;
varying vec4 persPos_var;
varying vec4 worldPos_var;
varying vec3 normal_var;
void main()
{

    vec4 localSpace = objectMatrix * position;
    vec4 worldSpace =worldMatrix *localSpace;
    gl_Position = perspectiveMatrix *worldSpace;

    center_var =  (worldMatrix*vec4(center,1.0)).xyz;
  normal_var = (normalMatrix*normal).xyz;
  
    color_var =color;

    worldPos_var =worldSpace ;
    persPos_var = gl_Position  ;



}