



attribute vec4 position;
attribute vec4 normal;
attribute vec4 tangent;
attribute vec2 uv;


uniform mat4 objectMatrix ;
uniform mat4 normalMatrix ;
uniform mat4 worldMatrix ;
uniform mat4 normalWorldMatrix;
uniform mat4 perspectiveMatrix ;


varying vec3 normal_var;
varying vec3 tangent_var;
varying vec3 bitangent_var;
varying vec2 uv_var;


void main()
{

    vec4 localSpace = objectMatrix * position;
    vec4 worldSpace = worldMatrix *localSpace;
    gl_Position = perspectiveMatrix *worldSpace;

    
  
    vec4 normalLok = normalMatrix*normal;
    normal_var =(normalWorldMatrix* normalLok ).xyz; // normalWorldMatrix*


	 vec4 tangentLok = normalMatrix*tangent;
    tangent_var =(normalWorldMatrix* tangentLok ).xyz;
	bitangent_var =cross(normal_var,tangent_var);
	normalize(bitangent_var);
    uv_var =uv;





}