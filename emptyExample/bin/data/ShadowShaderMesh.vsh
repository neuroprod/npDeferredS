



attribute vec4 position;
attribute vec2 uv;


uniform mat4 objectMatrix ;
uniform mat4 worldMatrix ;
uniform mat4 lightProjectionMatrix ;

varying vec2 uv_var;


void main()
{

    vec4 localSpace = objectMatrix * position;
	vec4 worldSpace   =   worldMatrix *localSpace;
    gl_Position = lightProjectionMatrix* worldSpace ;

    
	uv_var =uv;





}